
/*
        This is small proggy to test GTE instructions.
       
        Made by org, 2007.
        Modified by edgbla, 2011.
*/

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
#include "disasm.h"

/**************************************************************************/

#define PIH     (320)
#define PIV     (240)
#define OTLEN   (16)

/**************************************************************************/

static int side = 0;
static long ot[2][OTLEN];
DRAWENV     draw[2];
DISPENV     disp[2];
//int         current;
int         fnt;
u_long      PadData;
u_long      oldPadData = 0;

/* GTE Registers. */
u_long      GTEData[32], GTECtrl[32];

static char *CP2D_Name[32] = {
 "VXY0", "VZ0", "VXY1", "VZ1", "VXY2", "VX2", "RGB", "OTZ",
 "IR0", "IR1", "IR2", "IR3", "SXY0", "SXY1", "SXY2", "SXYP",
 "SZ0", "SZ1", "SZ2", "SZ3", "RGB0", "RGB1", "RGB2", "R23",
 "MAC0", "MAC1", "MAC2", "MAC3", "IRGB", "ORGB", "LZCS", "LZCR"
};

static char *CP2C_Name[32] = {
 "R11R12", "R13R21", "R22R23", "R31R32", "R33", "TRX", "TRY", "TRZ",
 "L11L12", "L13L21", "L22L23", "L31L32", "L33", "RBK", "GBK", "BBK",
 "LR1LR2", "LR3LG1", "LG2LG3", "LB1LB2", "LB3", "RFC", "GFC", "BFC",
 "OFX", "OFY", "H", "DQA", "DQB", "ZSF3", "ZSF4", "FLAG"
};

enum
{
    REGMODE_C2D = 0,
    REGMODE_C2C,

    REGMODE_MAX
};

static int  RegMode = REGMODE_C2D;
static u_long Instr = 0x12345678;       // Instruction to execute.

#define JR_RA       0x03E00008
#define NOP         0x00000000
#define RTPS        0x4A180001

static u_long Code[32];                 // JIT-compiled instructions to execute.
static int GteCycles = 0;               // used to measure GTE instruction cycles

// For editing
static int  RegCursor = 0;
static int  RegNibble = 0;
static int  InstrNibble = 0;

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

static void PrintGTEData (void)
{
    int i = 0;
    char str[256];

    for (i=0; i<16; i++)
    {
        if ( i == RegCursor )
        {
            sprintf ( str, "%-8s>%08X  %-8s %08X \n",
                      CP2D_Name[i], GTEData[i],
                      CP2D_Name[i+16], GTEData[i+16] );
        }
        else if ( (i + 16) == RegCursor )
        {
            sprintf ( str, "%-8s %08X  %-8s>%08X \n",
                      CP2D_Name[i], GTEData[i],
                      CP2D_Name[i+16], GTEData[i+16] );
        }
        else
        {
            sprintf ( str, "%-8s %08X  %-8s %08X \n",
                      CP2D_Name[i], GTEData[i],
                      CP2D_Name[i+16], GTEData[i+16] );
        }
        FntPrint (fnt, str);
    }
}

static void PrintGTECtrl (void)
{
    int i = 0;
    char str[256];

    for (i=0; i<16; i++)
    {
        if ( i == RegCursor )
        {
            sprintf ( str, "%-8s>%08X  %-8s %08X \n",
                      CP2C_Name[i], GTECtrl[i],
                      CP2C_Name[i+16], GTECtrl[i+16] );
        }
        else if ( (i + 16) == RegCursor )
        {
            sprintf ( str, "%-8s %08X  %-8s>%08X \n",
                      CP2C_Name[i], GTECtrl[i],
                      CP2C_Name[i+16], GTECtrl[i+16] );
        }
        else
        {
            sprintf ( str, "%-8s %08X  %-8s %08X \n",
                      CP2C_Name[i], GTECtrl[i],
                      CP2C_Name[i+16], GTECtrl[i+16] );
        }
        FntPrint (fnt, str);
    }
}

static int ExecuteInstr (void)
{
    DisasmData dis;
    void (*code)(void);
    long before, after;

    dis.instr = Instr;
    dis.pc = 0x80000000;
    PSXDisasm (&dis);
    if ( (dis.type & DISA_TYPE_COP2) == 0 ) return;

    Code [0] = NOP;
    Code [1] = NOP;
    Code [2] = Instr;
    Code [3] = NOP;
    Code [4] = NOP;
    Code [5] = JR_RA;
    Code [6] = NOP;

    code = (void *)Code;

    EnterCriticalSection();
    FlushCache ();
    ExitCriticalSection();

    WritebackGTERegs ();
    SetRCnt (RCntCNT1, 0xffff, RCntMdNOINTR );
    StartRCnt (RCntCNT1);
    before = GetRCnt (RCntCNT1);
    code ();
    after = GetRCnt (RCntCNT1);
    StopRCnt (RCntCNT1);
    DumpGTERegs ();
    return after - before;
}

main ()
{
    char txt[256];
    DisasmData dis;
    u_long pc0 = (u_long)(void *)Code;
    int nibble;
    u_long reg;

    SetDispMask( 0 );
    ResetGraph( 0 );
    SetGraphDebug( 0 );
    ResetCallback();
    PadInit( 0 );
    ExitCriticalSection();
   
    Instr = RTPS;
   
    PadData = 0;

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
/*
    SetDefDrawEnv (&draw[0], 0, 0, 320, 256);
    SetDefDrawEnv (&draw[1], 0, 256, 320, 256);
    SetDefDispEnv (&disp[0], 0, 0, 320, 256);
    SetDefDispEnv (&disp[1], 0, 256, 320, 256);

    PutDrawEnv (&draw[current]);
    PutDispEnv (&disp[current]);
    SetDispMask (1);

    FntLoad (640, 0);
    fnt = FntOpen (0, 0, 320, 256, 1, 1024);
*/

    /* Initialize onscreen font and text output system */
    FntLoad(960, 256);
    SetDumpFnt(FntOpen(16, 16, 368, 480, 0, 1024));
   
    VSync(0);           /* Wait for VBLANK */
    SetDispMask(1);     /* Turn on the display */

    GTEEnable (0, 0);
    ClearGTERegs ();
    WritebackGTERegs ();

    while (1)
    {
        ClearOTag( ot[side], OTLEN );
        DrawSync( 0 );
        side ^= 1;
        PutDispEnv( &disp[side] );
        PutDrawEnv( &draw[side] );
        DrawOTag( ot[side/*^1*/] );
       
        PadData = PadRead (0);
       
        // Editing
        if ( (PadData & _PAD(0, PADLleft)) && !(oldPadData & _PAD(0, PADLleft)))
        {
            RegNibble = (RegNibble - 1) & 7;
        }
        if ( (PadData & _PAD(0, PADLright)) && !(oldPadData & _PAD(0, PADLright)))
        {
            RegNibble = (RegNibble + 1) & 7;
        }
        if ( (PadData & _PAD(0, PADLup)) && !(oldPadData & _PAD(0, PADLup)))
        {
            RegCursor = (RegCursor - 1) & 0x1F;
        }
        if ( (PadData & _PAD(0, PADLdown)) && !(oldPadData & _PAD(0, PADLdown)))
        {
            RegCursor = (RegCursor + 1) & 0x1F;
        }

        if ( (PadData & _PAD(0, PADR1)) && !(oldPadData & _PAD(0, PADR1)))
        {
            InstrNibble = (InstrNibble - 1) & 7;
        }
        if ( (PadData & _PAD(0, PADR2)) && !(oldPadData & _PAD(0, PADR2)))
        {
            InstrNibble = (InstrNibble + 1) & 7;
        }

        if ( (PadData & _PAD(0, PADL1)) && !(oldPadData & _PAD(0, PADL1)))
        {
            switch (RegMode)
            {
                case REGMODE_C2D:
                    reg = GTEData[RegCursor];
                    break;
                case REGMODE_C2C:
                    reg = GTECtrl[RegCursor];                    
                    break;
            }

            nibble = (reg >> (4 * (7 - RegNibble))) & 0xF;
            nibble = (nibble + 1) & 0xF;
            reg &= ~(0xf << (4 * (7 - RegNibble)));
            reg |= (nibble << (4 * (7 - RegNibble)));

            switch (RegMode)
            {
                case REGMODE_C2D:
                    GTEData[RegCursor] = reg;
                    break;
                case REGMODE_C2C:
                    GTECtrl[RegCursor] = reg;
                    break;
            }
        }

        if ( (PadData & _PAD(0, PADL2)) && !(oldPadData & _PAD(0, PADL2)))
        {
            reg = Instr;

            nibble = (reg >> (4 * (7 - InstrNibble))) & 0xF;
            nibble = (nibble + 1) & 0xF;
            reg &= ~(0xf << (4 * (7 - InstrNibble)));
            reg |= (nibble << (4 * (7 - InstrNibble)));

            Instr = reg;
        }
       
        if ( (PadData & _PAD(0, PADstart)) && !(oldPadData & _PAD(0, PADstart)))
        {
            GteCycles = ExecuteInstr ();
        }
       
        if ( (PadData & _PAD(0, PADselect)) && !(oldPadData & _PAD(0, PADselect)))
        {
            RegMode = (RegMode + 1) % REGMODE_MAX;
        }          
       
        oldPadData = PadData;
       
        switch (RegMode)
        {
            case REGMODE_C2D:
                PrintGTEData ();
                break;
            case REGMODE_C2C:
                PrintGTECtrl ();
                break;
        }

        dis.instr = Instr;
        dis.pc = pc0;
        dis.simplify = 1;

        PSXDisasm (&dis);
        sprintf (txt, "\nPC: %08X\n%08X %-8s%-10s\nReg: %i, Nibble: %i, Instr nibble: %i\n", pc0, dis.instr, dis.mnem, dis.operands, RegCursor, RegNibble, InstrNibble);
        FntPrint (fnt, txt);
        sprintf (txt, "\ncycles (with decorating code): %i", GteCycles );
        FntPrint (fnt, txt);
               
        FntFlush (fnt);
        //DrawSync (0);

        VSync (0);

       /* current ^= 1;
        PutDrawEnv (&draw[current]);
        PutDispEnv (&disp[current]); */      
    }
}
