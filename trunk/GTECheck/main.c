// Bruteforce all GTE instructions and compare output with standard gauge values.
// (c) org 2011.

#include <stdio.h>
#include <sys/types.h>
#include <sys/file.h>
#include <libapi.h>
#include <libetc.h>
#include <libgte.h>
#include <libgpu.h>
#include <libgs.h>
#include <libsn.h>

#include "gte.h"
#include "gte2.h"
#include "gteregs.h"

/**************************************************************************/

#define PIH     (320)
#define PIV     (240)
#define OTLEN   (16)

static int side = 0;
static long ot[2][OTLEN];
DRAWENV     draw[2];
DISPENV     disp[2];
//int         current;
int         fnt;

/**************************************************************************/

/* GTE Registers. */
u_long      GTEData[32], GTECtrl[32];

static void ClearGTERegs (void)
{
    int i;

    for (i=0; i<=31; i++)
    {
        GTEData[i] = GTECtrl[i] = 0;
    }
}

static void DumpGTERegs (void)
{
    int i;

    for (i=0; i<=31; i++)
    {
        GTEData[i] = GTEReadData (i);
        GTECtrl[i] = GTEReadCtrl (i);
    }
}

static void WritebackGTERegs (void)
{
    int i;

    for (i=0; i<=31; i++)
    {
        GTEWriteData (i, GTEData[i]);
        GTEWriteCtrl (i, GTECtrl[i]);
    }
}

static u_long GTERegsChecksum (void)
{
    int i;
    u_long sum = 0;
    for (i=0; i<=31; i++)
    {
        sum += GTEData[i];
        sum += GTECtrl[i];
    }
    return sum;
}

/**************************************************************************/

typedef struct RunFlow {    // value = [from ... to] with step.
    u_long  from;
    u_long  to;
    u_long  step;           // if ( value += step > to ) value = to.
} RunFlow;

typedef struct RegFlow {
    int     index;          // reg. index
    int     datactrl;       // 0 - Data reg, 1 - ctrl reg;
    u_long  value;          // current value
    RunFlow *run;           // runflow control
} RegFlow;

#define DATA    0
#define CTRL    1

static void Test_AVSZ3 (char *info, u_long sz1, u_long sz2, u_long sz3, u_long zsf3)
{
    char txt[256];
    u_long otz, mac0, flag;

    ClearGTERegs ();
    GTEData [C2_SZ1] = sz1 ;
    GTEData [C2_SZ2] = sz2 ;
    GTEData [C2_SZ3] = sz3 ;
    GTECtrl [C2_ZSF3] = zsf3 ;
    WritebackGTERegs ();
    GTE_AVSZ3 ();
    DumpGTERegs ();
    otz = GTEData [C2_OTZ];
    mac0 = GTEData [C2_MAC0];
    flag = GTECtrl [C2_FLAG];
    sprintf (txt, "\n%s\n(%04X+%04X+%04X)*%04X\nOTZ=%08X\nMAC0=%08X\nFLAG=%08X\n", info, sz1, sz2, sz3, zsf3, otz, mac0, flag );
    FntPrint (fnt, txt);    
}

/**************************************************************************/

main ()
{
    char txt[256];

    SetDispMask( 0 );
    ResetGraph( 0 );
    SetGraphDebug( 0 );
    ResetCallback();
    PadInit( 0 );
    ExitCriticalSection();

   // current = 0;

    /* Initialize drawing environment & screen double buffer */
    SetDefDrawEnv( &draw[0], 0,   0, PIH, PIV );
    SetDefDrawEnv( &draw[1], 0, PIV, PIH, PIV );
    SetDefDispEnv( &disp[0], 0, PIV, PIH, PIV );
    SetDefDispEnv( &disp[1], 0,   0, PIH, PIV );
    draw[0].isbg = draw[1].isbg = 1;
    setRGB0( &draw[0], 0, 0, 64 );
    setRGB0( &draw[1], 0, 0, 64 );
    PutDispEnv( &disp[0] );
    PutDrawEnv( &draw[0] );

    /* Initialize onscreen font and text output system */
    FntLoad(960, 256);
    SetDumpFnt(FntOpen(16, 16, 368, 480, 0, 1024));
   
    VSync(0);           /* Wait for VBLANK */
    SetDispMask(1);     /* Turn on the display */

    GTEEnable (0, 0);

    while (1)
    {
        ClearOTag( ot[side], OTLEN );
        DrawSync( 0 );
        side ^= 1;
        PutDispEnv( &disp[side] );
        PutDrawEnv( &draw[side] );
        DrawOTag( ot[side/*^1*/] );

        sprintf (txt, "AVSZ3 Test\n" );
        FntPrint (fnt, txt);    
        Test_AVSZ3 ("Normal calc", 1, 2, 3, 0x0556 );
        Test_AVSZ3 ("Limit C", 0x1C72, 0x1C72, 0x1C72, 0x3000 );
        Test_AVSZ3 ("Overflow", 0xFFFF, 0xFFFF, 0xFFFF, 0x7FFF );
        Test_AVSZ3 ("Underflow", 0xFFFF, 0xFFFF, 0xFFFF, 0x8001 );
             
        FntFlush (fnt);
        //DrawSync (0);

        VSync (0);

       /* current ^= 1;
        PutDrawEnv (&draw[current]);
        PutDispEnv (&disp[current]); */      
    }
}
