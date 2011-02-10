// GTE Engine based on Pops reverse engineering.
// (c) org 2011.

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Gte.h"
#include "R3000A.h"

#define SUM_FLAG if(gteFLAG & 0x7F87E000) gteFLAG |= 0x80000000;

#ifdef _MSC_VER_
#pragma warning(disable:4244)
#pragma warning(disable:4761)
#endif

#define gteVX0     ((s16*)psxRegs.CP2D.r)[0]
#define gteVY0     ((s16*)psxRegs.CP2D.r)[1]
#define gteVZ0     ((s16*)psxRegs.CP2D.r)[2]
#define gteVX1     ((s16*)psxRegs.CP2D.r)[4]
#define gteVY1     ((s16*)psxRegs.CP2D.r)[5]
#define gteVZ1     ((s16*)psxRegs.CP2D.r)[6]
#define gteVX2     ((s16*)psxRegs.CP2D.r)[8]
#define gteVY2     ((s16*)psxRegs.CP2D.r)[9]
#define gteVZ2     ((s16*)psxRegs.CP2D.r)[10]
#define gteRGB     psxRegs.CP2D.r[6]
#define gteOTZ     ((s16*)psxRegs.CP2D.r)[7*2]
#define gteIR0     ((s32*)psxRegs.CP2D.r)[8]
#define gteIR1     ((s32*)psxRegs.CP2D.r)[9]
#define gteIR2     ((s32*)psxRegs.CP2D.r)[10]
#define gteIR3     ((s32*)psxRegs.CP2D.r)[11]
#define gteSXY0    ((s32*)psxRegs.CP2D.r)[12]
#define gteSXY1    ((s32*)psxRegs.CP2D.r)[13]
#define gteSXY2    ((s32*)psxRegs.CP2D.r)[14]
#define gteSXYP    ((s32*)psxRegs.CP2D.r)[15]
#define gteSX0     ((s16*)psxRegs.CP2D.r)[12*2]
#define gteSY0     ((s16*)psxRegs.CP2D.r)[12*2+1]
#define gteSX1     ((s16*)psxRegs.CP2D.r)[13*2]
#define gteSY1     ((s16*)psxRegs.CP2D.r)[13*2+1]
#define gteSX2     ((s16*)psxRegs.CP2D.r)[14*2]
#define gteSY2     ((s16*)psxRegs.CP2D.r)[14*2+1]
#define gteSXP     ((s16*)psxRegs.CP2D.r)[15*2]
#define gteSYP     ((s16*)psxRegs.CP2D.r)[15*2+1]
#define gteSZ0     ((u16*)psxRegs.CP2D.r)[16*2]
#define gteSZ1     ((u16*)psxRegs.CP2D.r)[17*2]
#define gteSZ2     ((u16*)psxRegs.CP2D.r)[18*2]
#define gteSZ3     ((u16*)psxRegs.CP2D.r)[19*2]
#define gteRGB0    psxRegs.CP2D.r[20]
#define gteRGB1    psxRegs.CP2D.r[21]
#define gteRGB2    psxRegs.CP2D.r[22]
#define gteMAC0    psxRegs.CP2D.r[24]
#define gteMAC1    ((s32*)psxRegs.CP2D.r)[25]
#define gteMAC2    ((s32*)psxRegs.CP2D.r)[26]
#define gteMAC3    ((s32*)psxRegs.CP2D.r)[27]
#define gteIRGB    psxRegs.CP2D.r[28]
#define gteORGB    psxRegs.CP2D.r[29]
#define gteLZCS    psxRegs.CP2D.r[30]
#define gteLZCR    psxRegs.CP2D.r[31]

#define gteR       ((u8 *)psxRegs.CP2D.r)[6*4]
#define gteG       ((u8 *)psxRegs.CP2D.r)[6*4+1]
#define gteB       ((u8 *)psxRegs.CP2D.r)[6*4+2]
#define gteCODE    ((u8 *)psxRegs.CP2D.r)[6*4+3]
#define gteC       gteCODE

#define gteR0      ((u8 *)psxRegs.CP2D.r)[20*4]
#define gteG0      ((u8 *)psxRegs.CP2D.r)[20*4+1]
#define gteB0      ((u8 *)psxRegs.CP2D.r)[20*4+2]
#define gteCODE0   ((u8 *)psxRegs.CP2D.r)[20*4+3]
#define gteC0      gteCODE0

#define gteR1      ((u8 *)psxRegs.CP2D.r)[21*4]
#define gteG1      ((u8 *)psxRegs.CP2D.r)[21*4+1]
#define gteB1      ((u8 *)psxRegs.CP2D.r)[21*4+2]
#define gteCODE1   ((u8 *)psxRegs.CP2D.r)[21*4+3]
#define gteC1      gteCODE1

#define gteR2      ((u8 *)psxRegs.CP2D.r)[22*4]
#define gteG2      ((u8 *)psxRegs.CP2D.r)[22*4+1]
#define gteB2      ((u8 *)psxRegs.CP2D.r)[22*4+2]
#define gteCODE2   ((u8 *)psxRegs.CP2D.r)[22*4+3]
#define gteC2      gteCODE2



#define gteR11  ((s16*)psxRegs.CP2C.r)[0]
#define gteR12  ((s16*)psxRegs.CP2C.r)[1]
#define gteR13  ((s16*)psxRegs.CP2C.r)[2]
#define gteR21  ((s16*)psxRegs.CP2C.r)[3]
#define gteR22  ((s16*)psxRegs.CP2C.r)[4]
#define gteR23  ((s16*)psxRegs.CP2C.r)[5]
#define gteR31  ((s16*)psxRegs.CP2C.r)[6]
#define gteR32  ((s16*)psxRegs.CP2C.r)[7]
#define gteR33  ((s16*)psxRegs.CP2C.r)[8]
#define gteTRX  ((s32*)psxRegs.CP2C.r)[5]
#define gteTRY  ((s32*)psxRegs.CP2C.r)[6]
#define gteTRZ  ((s32*)psxRegs.CP2C.r)[7]
#define gteL11  ((s16*)psxRegs.CP2C.r)[16]
#define gteL12  ((s16*)psxRegs.CP2C.r)[17]
#define gteL13  ((s16*)psxRegs.CP2C.r)[18]
#define gteL21  ((s16*)psxRegs.CP2C.r)[19]
#define gteL22  ((s16*)psxRegs.CP2C.r)[20]
#define gteL23  ((s16*)psxRegs.CP2C.r)[21]
#define gteL31  ((s16*)psxRegs.CP2C.r)[22]
#define gteL32  ((s16*)psxRegs.CP2C.r)[23]
#define gteL33  ((s16*)psxRegs.CP2C.r)[24]
#define gteRBK  ((s32*)psxRegs.CP2C.r)[13]
#define gteGBK  ((s32*)psxRegs.CP2C.r)[14]
#define gteBBK  ((s32*)psxRegs.CP2C.r)[15]
#define gteLR1  ((s16*)psxRegs.CP2C.r)[32]
#define gteLR2  ((s16*)psxRegs.CP2C.r)[33]
#define gteLR3  ((s16*)psxRegs.CP2C.r)[34]
#define gteLG1  ((s16*)psxRegs.CP2C.r)[35]
#define gteLG2  ((s16*)psxRegs.CP2C.r)[36]
#define gteLG3  ((s16*)psxRegs.CP2C.r)[37]
#define gteLB1  ((s16*)psxRegs.CP2C.r)[38]
#define gteLB2  ((s16*)psxRegs.CP2C.r)[39]
#define gteLB3  ((s16*)psxRegs.CP2C.r)[40]
#define gteRFC  ((s32*)psxRegs.CP2C.r)[21]
#define gteGFC  ((s32*)psxRegs.CP2C.r)[22]
#define gteBFC  ((s32*)psxRegs.CP2C.r)[23]
#define gteOFX  ((s32*)psxRegs.CP2C.r)[24]
#define gteOFY  ((s32*)psxRegs.CP2C.r)[25]
#define gteH    ((u16*)psxRegs.CP2C.r)[52]
#define gteDQA  ((s16*)psxRegs.CP2C.r)[54]
#define gteDQB  ((s32*)psxRegs.CP2C.r)[28]
#define gteZSF3 ((s16*)psxRegs.CP2C.r)[58]
#define gteZSF4 ((s16*)psxRegs.CP2C.r)[60]
#define gteFLAG psxRegs.CP2C.r[31]

#define	gteD1	(*(short *)&gteR11)
#define	gteD2	(*(short *)&gteR22)
#define	gteD3	(*(short *)&gteR33)

#define VX(n) (n < 3 ? psxRegs.CP2D.p[n << 1].sw.l : psxRegs.CP2D.p[9].sw.l)
#define VY(n) (n < 3 ? psxRegs.CP2D.p[n << 1].sw.h : psxRegs.CP2D.p[10].sw.l)
#define VZ(n) (n < 3 ? psxRegs.CP2D.p[(n << 1) + 1].sw.l : psxRegs.CP2D.p[11].sw.l)
#define MX11(n) (n < 3 ? psxRegs.CP2C.p[(n << 3)].sw.l : 0)
#define MX12(n) (n < 3 ? psxRegs.CP2C.p[(n << 3)].sw.h : 0)
#define MX13(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 1].sw.l : 0)
#define MX21(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 1].sw.h : 0)
#define MX22(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 2].sw.l : 0)
#define MX23(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 2].sw.h : 0)
#define MX31(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 3].sw.l : 0)
#define MX32(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 3].sw.h : 0)
#define MX33(n) (n < 3 ? psxRegs.CP2C.p[(n << 3) + 4].sw.l : 0)
#define CV1(n) (n < 3 ? (s32)psxRegs.CP2C.r[(n << 3) + 5] : 0)
#define CV2(n) (n < 3 ? (s32)psxRegs.CP2C.r[(n << 3) + 6] : 0)
#define CV3(n) (n < 3 ? (s32)psxRegs.CP2C.r[(n << 3) + 7] : 0)

__inline unsigned long MFC2(int reg) {
	switch(reg) {
		case 29:
			gteORGB = (((gteIR1 >> 7) & 0x1f)) |
					  (((gteIR2 >> 7) & 0x1f)<<5) |
					  (((gteIR3 >> 7) & 0x1f)<<10);
//			gteORGB = (gteIR1      ) | 
//					  (gteIR2 <<  5) | 
//					  (gteIR3 << 10);
//			gteORGB = ((gteIR1 & 0xf80)>>7) | 
//					  ((gteIR2 & 0xf80)>>2) | 
//					  ((gteIR3 & 0xf80)<<3);
			return gteORGB;

		default:
			return psxRegs.CP2D.r[reg];
	}
}

__inline void MTC2(unsigned long value, int reg) {
	int a;

	switch(reg) {
		case 8: case 9: case 10: case 11:
			psxRegs.CP2D.r[reg] = (short)value;
			break;

		case 15:
			gteSXY0 = gteSXY1;
			gteSXY1 = gteSXY2;
			gteSXY2 = value;
			gteSXYP = value;
			break;

		case 16: case 17: case 18: case 19:
			psxRegs.CP2D.r[reg] = (value & 0xffff);
			break;

		case 28:
			psxRegs.CP2D.r[28] = value;
			gteIR1 = ((value      ) & 0x1f) << 7;
			gteIR2 = ((value >>  5) & 0x1f) << 7;
			gteIR3 = ((value >> 10) & 0x1f) << 7;
//			gteIR1 = (value      ) & 0x1f;
//			gteIR2 = (value >>  5) & 0x1f;
//			gteIR3 = (value >> 10) & 0x1f;
//			gteIR1 = ((value      ) & 0x1f) << 4;
//			gteIR2 = ((value >>  5) & 0x1f) << 4;
//			gteIR3 = ((value >> 10) & 0x1f) << 4;
			break;

		case 30:
			psxRegs.CP2D.r[30] = value;

			a = psxRegs.CP2D.r[30];
#if defined(_MSC_VER_)
			if (a > 0) {
				__asm {
					mov eax, a;
					bsr eax, eax;
					mov a, eax;
				}
				psxRegs.CP2D.r[31] = 31 - a;
			} else if (a < 0) {
				__asm {
					mov eax, a;
					xor eax, 0xffffffff;
					bsr eax, eax;
					mov a, eax;
				}
				psxRegs.CP2D.r[31] = 31 - a;
			} else {
				psxRegs.CP2D.r[31] = 32;
			}
#elif defined(__LINUX__) || defined(__MINGW32__)
			if (a > 0) {
				__asm__ ("bsrl %1, %0\n" : "=r"(a) : "r"(a) );
				psxRegs.CP2D.r[31] = 31 - a;
			} else if (a < 0) {
				a^= 0xffffffff;
				__asm__ ("bsrl %1, %0\n" : "=r"(a) : "r"(a) );
				psxRegs.CP2D.r[31] = 31 - a;
			} else {
				psxRegs.CP2D.r[31] = 32;
			}
#else
			if (a > 0) {
				int i;
				for (i=31; (a & (1 << i)) == 0 && i >= 0; i--);
				psxRegs.CP2D.r[31] = 31 - i;
			} else if (a < 0) {
				int i;
				a^= 0xffffffff;
				for (i=31; (a & (1 << i)) == 0 && i >= 0; i--);
				psxRegs.CP2D.r[31] = 31 - i;
			} else {
				psxRegs.CP2D.r[31] = 32;
			}
#endif
			break;
		
		default:
			psxRegs.CP2D.r[reg] = value;
	}
}

void gteMFC2() {
	if (!_Rt_) return;
	psxRegs.GPR.r[_Rt_] = MFC2(_Rd_);
}

void gteCFC2() {
	if (!_Rt_) return;
	psxRegs.GPR.r[_Rt_] = psxRegs.CP2C.r[_Rd_];
}

void gteMTC2() {
	MTC2(psxRegs.GPR.r[_Rt_], _Rd_);
}

void gteCTC2() {
	psxRegs.CP2C.r[_Rd_] = psxRegs.GPR.r[_Rt_];
}

#define _oB_ (psxRegs.GPR.r[_Rs_] + _Imm_)

void gteLWC2() {
	MTC2(psxMemRead32(_oB_), _Rt_);
}

void gteSWC2() {
	psxMemWrite32(_oB_, MFC2(_Rt_));
}

/////LIMITATIONS AND OTHER STUFF************************************


__inline double NC_OVERFLOW1(double x) {
	if (x<-2147483648.0) {gteFLAG |= 1<<29;}	
	else if (x> 2147483647.0) {gteFLAG |= 1<<26;}

	return x;
}

__inline double NC_OVERFLOW2(double x) {
	if (x<-2147483648.0) {gteFLAG |= 1<<28;}	
	else if (x> 2147483647.0) {gteFLAG |= 1<<25;}
	
	return x;
}

__inline double NC_OVERFLOW3(double x) {
	if (x<-2147483648.0) {gteFLAG |= 1<<27;}	
	else if (x> 2147483647.0) {gteFLAG |= 1<<24;}
	
	return x;
}

__inline double NC_OVERFLOW4(double x) {
	if (x<-2147483648.0) {gteFLAG |= 1<<16;}	
	else if (x> 2147483647.0) {gteFLAG |= 1<<15;}
	
	return x;
}

__inline s32 FNC_OVERFLOW1(s64 x) {
	if (x< (s64)0xffffffff80000000) {gteFLAG |= 1<<29;}	
	else if (x> 2147483647) {gteFLAG |= 1<<26;}

	return (s32)x;
}

__inline s32 FNC_OVERFLOW2(s64 x) {
	if (x< (s64)0xffffffff80000000) {gteFLAG |= 1<<28;}	
	else if (x> 2147483647) {gteFLAG |= 1<<25;}
	
	return (s32)x;
}

__inline s32 FNC_OVERFLOW3(s64 x) {
	if (x< (s64)0xffffffff80000000) {gteFLAG |= 1<<27;}	
	else if (x> 2147483647) {gteFLAG |= 1<<24;}
	
	return (s32)x;
}

__inline s32 FNC_OVERFLOW4(s64 x) {
	if (x< (s64)0xffffffff80000000) {gteFLAG |= 1<<16;}	
	else if (x> 2147483647) {gteFLAG |= 1<<15;}
	
	return (s32)x;
}

#define _LIMX(negv, posv, flagb) { \
	if (x < (negv)) { x = (negv); gteFLAG |= (1<<flagb); } else \
	if (x > (posv)) { x = (posv); gteFLAG |= (1<<flagb); } return (x); \
}

__inline double limA1S(double x) { _LIMX(-32768.0, 32767.0, 24); }
__inline double limA2S(double x) { _LIMX(-32768.0, 32767.0, 23); }
__inline double limA3S(double x) { _LIMX(-32768.0, 32767.0, 22); }
__inline double limA1U(double x) { _LIMX(0.0, 32767.0, 24); }
__inline double limA2U(double x) { _LIMX(0.0, 32767.0, 23); }
__inline double limA3U(double x) { _LIMX(0.0, 32767.0, 22); }
__inline double limB1 (double x) { _LIMX(0.0, 255.0, 21); }
__inline double limB2 (double x) { _LIMX(0.0, 255.0, 20); }
__inline double limB3 (double x) { _LIMX(0.0, 255.0, 19); }
__inline double limC  (double x) { _LIMX(0.0, 65535.0, 18); }
__inline double limD1 (double x) { _LIMX(-1024.0, 1023.0, 14); }
__inline double limD2 (double x) { _LIMX(-1024.0, 1023.0, 13); }
__inline double limE  (double x) { _LIMX(0.0, 4095.0, 12); }

__inline double limG1(double x) {
	if (x > 2147483647.0) { gteFLAG |= (1<<16); } else
	if (x <-2147483648.0) { gteFLAG |= (1<<15); }

	if (x >       1023.0) { x =  1023.0; gteFLAG |= (1<<14); } else
	if (x <      -1024.0) { x = -1024.0; gteFLAG |= (1<<14); } return (x);
}

__inline double limG2(double x) {
	if (x > 2147483647.0) { gteFLAG |= (1<<16); } else
	if (x <-2147483648.0) { gteFLAG |= (1<<15); }

	if (x >       1023.0) { x =  1023.0; gteFLAG |= (1<<13); } else
	if (x <      -1024.0) { x = -1024.0; gteFLAG |= (1<<13); } return (x);
}

__inline s32 F12limA1S(s64 x) { _LIMX(-32768<<12, 32767<<12, 24); }
__inline s32 F12limA2S(s64 x) { _LIMX(-32768<<12, 32767<<12, 23); }
__inline s32 F12limA3S(s64 x) { _LIMX(-32768<<12, 32767<<12, 22); }
__inline s32 F12limA1U(s64 x) { _LIMX(0, 32767<<12, 24); }
__inline s32 F12limA2U(s64 x) { _LIMX(0, 32767<<12, 23); }
__inline s32 F12limA3U(s64 x) { _LIMX(0, 32767<<12, 22); }

__inline s16 FlimA1S(s32 x) { _LIMX(-32768, 32767, 24); }
__inline s16 FlimA2S(s32 x) { _LIMX(-32768, 32767, 23); }
__inline s16 FlimA3S(s32 x) { _LIMX(-32768, 32767, 22); }
__inline s16 FlimA1U(s32 x) { _LIMX(0, 32767, 24); }
__inline s16 FlimA2U(s32 x) { _LIMX(0, 32767, 23); }
__inline s16 FlimA3U(s32 x) { _LIMX(0, 32767, 22); }
__inline u8  FlimB1 (s32 x) { _LIMX(0, 255, 21); }
__inline u8  FlimB2 (s32 x) { _LIMX(0, 255, 20); }
__inline u8  FlimB3 (s32 x) { _LIMX(0, 255, 19); }
__inline u16 FlimC  (s32 x) { _LIMX(0, 65535, 18); }
__inline s32 FlimD1 (s32 x) { _LIMX(-1024, 1023, 14); }
__inline s32 FlimD2 (s32 x) { _LIMX(-1024, 1023, 13); }
__inline s32 FlimE  (s32 x) { _LIMX(0, 65535, 12); }
//__inline s32 FlimE  (s32 x) { _LIMX(0, 4095, 12); }

__inline s32 FlimG1(s64 x) {
	if (x > 2147483647) { gteFLAG |= (1<<16); } else
	if (x < (s64)0xffffffff80000000) { gteFLAG |= (1<<15); }

	if (x >       1023) { x =  1023; gteFLAG |= (1<<14); } else
	if (x <      -1024) { x = -1024; gteFLAG |= (1<<14); } return (x);
}

__inline s32 FlimG2(s64 x) {
	if (x > 2147483647) { gteFLAG |= (1<<16); } else
	if (x < (s64)0xffffffff80000000) { gteFLAG |= (1<<15); }

	if (x >       1023) { x =  1023; gteFLAG |= (1<<13); } else
	if (x <      -1024) { x = -1024; gteFLAG |= (1<<13); } return (x);
}

#define MAC2IR() { \
	if (gteMAC1 < (long)(-32768)) { gteIR1=(long)(-32768); gteFLAG|=1<<24;} \
	else \
	if (gteMAC1 > (long)( 32767)) { gteIR1=(long)( 32767); gteFLAG|=1<<24;} \
	else gteIR1=(long)gteMAC1; \
	if (gteMAC2 < (long)(-32768)) { gteIR2=(long)(-32768); gteFLAG|=1<<23;} \
	else \
	if (gteMAC2 > (long)( 32767)) { gteIR2=(long)( 32767); gteFLAG|=1<<23;} \
	else gteIR2=(long)gteMAC2; \
	if (gteMAC3 < (long)(-32768)) { gteIR3=(long)(-32768); gteFLAG|=1<<22;} \
	else \
	if (gteMAC3 > (long)( 32767)) { gteIR3=(long)( 32767); gteFLAG|=1<<22;} \
	else gteIR3=(long)gteMAC3; \
}


#define MAC2IR1() {           \
	if (gteMAC1 < (long)0) { gteIR1=(long)0; gteFLAG|=1<<24;}  \
	else if (gteMAC1 > (long)(32767)) { gteIR1=(long)(32767); gteFLAG|=1<<24;} \
	else gteIR1=(long)gteMAC1;                                                         \
	if (gteMAC2 < (long)0) { gteIR2=(long)0; gteFLAG|=1<<23;}      \
	else if (gteMAC2 > (long)(32767)) { gteIR2=(long)(32767); gteFLAG|=1<<23;}    \
	else gteIR2=(long)gteMAC2;                                                            \
	if (gteMAC3 < (long)0) { gteIR3=(long)0; gteFLAG|=1<<22;}         \
	else if (gteMAC3 > (long)(32767)) { gteIR3=(long)(32767); gteFLAG|=1<<22;}       \
	else gteIR3=(long)gteMAC3; \
}

//********END OF LIMITATIONS**********************************/

#define GTE_RTPS1(vn) { \
	gteMAC1 = FNC_OVERFLOW1(((signed long)(gteR11*gteVX##vn + gteR12*gteVY##vn + gteR13*gteVZ##vn)>>12) + gteTRX); \
	gteMAC2 = FNC_OVERFLOW2(((signed long)(gteR21*gteVX##vn + gteR22*gteVY##vn + gteR23*gteVZ##vn)>>12) + gteTRY); \
	gteMAC3 = FNC_OVERFLOW3(((signed long)(gteR31*gteVX##vn + gteR32*gteVY##vn + gteR33*gteVZ##vn)>>12) + gteTRZ); \
}

#define GTE_RTPS2(vn, vm) { \
	if (gteSZ##vn == 0) { \
		FDSZ = 2 << 16; gteFLAG |= 1<<17; \
	} else { \
		FDSZ = ((u64)gteH << 32) / ((u64)gteSZ##vn << 16); \
		if ((u64)FDSZ > (2 << 16)) { FDSZ = 2 << 16; gteFLAG |= 1<<17; } \
	} \
 \
	gteSX##vm = FlimG1((gteOFX + (((s64)((s64)gteIR1 << 16) * FDSZ) >> 16)) >> 16); \
	gteSY##vm = FlimG2((gteOFY + (((s64)((s64)gteIR2 << 16) * FDSZ) >> 16)) >> 16); \
}

#define GTE_RTPS3() { \
	FDSZ = (s64)((s64)gteDQB + (((s64)((s64)gteDQA << 8) * FDSZ) >> 8)); \
	gteMAC0 = FDSZ; \
	gteIR0  = FlimE(FDSZ >> 12); \
}

void gteRTPS() {
	s64 FDSZ;

	gteFLAG = 0;

	GTE_RTPS1(0);

	MAC2IR();

	gteSZ0 = gteSZ1;
	gteSZ1 = gteSZ2;
	gteSZ2 = gteSZ3;
	gteSZ3 = FlimC(gteMAC3);
	
    gteSXY0 = gteSXY1;
	gteSXY1 = gteSXY2;

	GTE_RTPS2(3, 2);
	gteSXYP = gteSXY2;

	GTE_RTPS3();

	SUM_FLAG;
}

void gteRTPT() {
	s64 FDSZ;

	gteFLAG = 0;

	gteSZ0 = gteSZ3;

	GTE_RTPS1(0);	

	gteSZ1 = FlimC(gteMAC3);

	gteIR1 = FlimA1S(gteMAC1);
	gteIR2 = FlimA2S(gteMAC2);
	GTE_RTPS2(1, 0);

	GTE_RTPS1(1);	

	gteSZ2 = FlimC(gteMAC3);

	gteIR1 = FlimA1S(gteMAC1);
	gteIR2 = FlimA2S(gteMAC2);
	GTE_RTPS2(2, 1);
	
	GTE_RTPS1(2);

	MAC2IR();

	gteSZ3 = FlimC(gteMAC3);

	GTE_RTPS2(3, 2);
	gteSXYP = gteSXY2;

	GTE_RTPS3();

	SUM_FLAG;

}

void gteMVMVA()
{
	int mx = (psxRegs.code >> 17) & 3;
	int v = (psxRegs.code >> 15) & 3;
	int cv = (psxRegs.code >> 13) & 3;
	s32 v1 = VX(v);
	s32 v2 = VY(v);
	s32 v3 = VZ(v);
	s64 mac[4];
	s32 limit = ((psxRegs.code >> 10) & 1) ? 0 : -32768;
	int shift = ((psxRegs.code >> 19) & 1) * 12;
	gteFLAG = 0;

    mac[1] = MX11(mx) * v1 + MX12(mx) * v2 + MX13(mx) * v3 + ((s64)CV1(cv) << 12);
	mac[2] = MX21(mx) * v1 + MX22(mx) * v2 + MX23(mx) * v3 + ((s64)CV2(cv) << 12);
	mac[3] = MX31(mx) * v1 + MX32(mx) * v2 + MX33(mx) * v3 + ((s64)CV3(cv) << 12);

	gteMAC1 = mac[1] >> shift;
	gteMAC2 = mac[2] >> shift;
	gteMAC3 = mac[3] >> shift;

	gteIR1 = min (32767, max (gteMAC1, limit) );
	gteIR2 = min (32767, max (gteMAC2, limit) );
	gteIR3 = min (32767, max (gteMAC3, limit) );

    if (cv != 3) {
		gteFLAG |= (((mac[1] >> 32) > 2047) << 30) | (((mac[1] >> 32) < -2048) << 27);
		gteFLAG |= (((mac[2] >> 32) > 2047) << 29) | (((mac[2] >> 32) < -2048) << 26);
		gteFLAG |= (((mac[3] >> 32) > 2047) << 28) | (((mac[3] >> 32) < -2048) << 25);
    }

    gteFLAG |= (gteMAC1 != gteIR1) << 24;
	gteFLAG |= (gteMAC2 != gteIR2) << 23;
	gteFLAG |= (gteMAC3 != gteIR3) << 22;

	SUM_FLAG
}

void gteNCLIP()
{
	gteMAC0 = (gteSX1 - gteSX0) * (gteSY2 - gteSY0) - (gteSX2 - gteSX0) * (gteSY1 - gteSY0);
	gteFLAG = 0;
}

void gteAVSZ3()
{
	gteMAC0 = (gteSZ1 + gteSZ2 + gteSZ3) * gteZSF3;
	gteFLAG = ((gteMAC0 >> 12) > 0xffff) << 18;
	gteOTZ = min (0xffff, max (0, gteMAC0 >> 12) );
	SUM_FLAG
}

void gteAVSZ4()
{
	gteMAC0 = (gteSZ1 + gteSZ2 + gteSZ3 + gteSZ0) * gteZSF4;
	gteFLAG = ((gteMAC0 >> 12) > 0xffff) << 18;
	gteOTZ = min (0xffff, max (0, gteMAC0 >> 12) );
	SUM_FLAG
}

void gteSQR()
{
	int shift = ((psxRegs.code >> 19) & 1) * 12;
    gteFLAG = 0;

	gteMAC1 = (gteIR1 * gteIR1) >> shift;
	gteMAC2 = (gteIR2 * gteIR2) >> shift;
	gteMAC3 = (gteIR3 * gteIR3) >> shift;

	gteFLAG |= ((u32)gteMAC1 > 32767) << 24;
	gteIR1 = min (32767, (u32)gteMAC1);
	gteFLAG |= ((u32)gteMAC2 > 32767) << 23;
	gteIR2 = min (32767, (u32)gteMAC2);
	gteFLAG |= ((u32)gteMAC3 > 32767) << 22;
	gteIR3 = min (32767, (u32)gteMAC3);

	SUM_FLAG
}

#define GTE_NCCS(vn) \
	gte_LL1 = F12limA1U((gteL11*gteVX##vn + gteL12*gteVY##vn + gteL13*gteVZ##vn) >> 12); \
	gte_LL2 = F12limA2U((gteL21*gteVX##vn + gteL22*gteVY##vn + gteL23*gteVZ##vn) >> 12); \
	gte_LL3 = F12limA3U((gteL31*gteVX##vn + gteL32*gteVY##vn + gteL33*gteVZ##vn) >> 12); \
	gte_RRLT= F12limA1U(gteRBK + ((gteLR1*gte_LL1 + gteLR2*gte_LL2 + gteLR3*gte_LL3) >> 12)); \
	gte_GGLT= F12limA2U(gteGBK + ((gteLG1*gte_LL1 + gteLG2*gte_LL2 + gteLG3*gte_LL3) >> 12)); \
	gte_BBLT= F12limA3U(gteBBK + ((gteLB1*gte_LL1 + gteLB2*gte_LL2 + gteLB3*gte_LL3) >> 12)); \
 \
	gteMAC1 = (long)(((s64)((u32)gteR<<12)*gte_RRLT) >> 20);\
	gteMAC2 = (long)(((s64)((u32)gteG<<12)*gte_GGLT) >> 20);\
	gteMAC3 = (long)(((s64)((u32)gteB<<12)*gte_BBLT) >> 20);


void gteNCCS()  {
	s32 gte_LL1, gte_LL2, gte_LL3;
	s32 gte_RRLT, gte_GGLT, gte_BBLT;

	gteFLAG = 0;

	GTE_NCCS(0);

	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	gteR2 = FlimB1(gteMAC1>>4);
	gteG2 = FlimB2(gteMAC2>>4);
	gteB2 = FlimB3(gteMAC3>>4); gteCODE2 = gteCODE;

	MAC2IR1();

	SUM_FLAG
}

void gteNCCT() {
	s32 gte_LL1, gte_LL2, gte_LL3;
	s32 gte_RRLT, gte_GGLT, gte_BBLT;

    gteFLAG = 0;

	GTE_NCCS(0);

	gteR0 = FlimB1(gteMAC1>>4);
	gteG0 = FlimB2(gteMAC2>>4);
	gteB0 = FlimB3(gteMAC3>>4); gteCODE0 = gteCODE;

	GTE_NCCS(1);

	gteR1 = FlimB1(gteMAC1>>4);
	gteG1 = FlimB2(gteMAC2>>4);
	gteB1 = FlimB3(gteMAC3>>4); gteCODE1 = gteCODE;

	GTE_NCCS(2);

	gteR2 = FlimB1(gteMAC1>>4);
	gteG2 = FlimB2(gteMAC2>>4);
	gteB2 = FlimB3(gteMAC3>>4); gteCODE2 = gteCODE;

	MAC2IR1();

	SUM_FLAG
}

#define GTE_NCDS(vn) \
	gte_LL1 = F12limA1U((gteL11*gteVX##vn + gteL12*gteVY##vn + gteL13*gteVZ##vn) >> 12); \
	gte_LL2 = F12limA2U((gteL21*gteVX##vn + gteL22*gteVY##vn + gteL23*gteVZ##vn) >> 12); \
	gte_LL3 = F12limA3U((gteL31*gteVX##vn + gteL32*gteVY##vn + gteL33*gteVZ##vn) >> 12); \
	gte_RRLT= F12limA1U(gteRBK + ((gteLR1*gte_LL1 + gteLR2*gte_LL2 + gteLR3*gte_LL3) >> 12)); \
	gte_GGLT= F12limA2U(gteGBK + ((gteLG1*gte_LL1 + gteLG2*gte_LL2 + gteLG3*gte_LL3) >> 12)); \
	gte_BBLT= F12limA3U(gteBBK + ((gteLB1*gte_LL1 + gteLB2*gte_LL2 + gteLB3*gte_LL3) >> 12)); \
 \
	gte_RR0 = (long)(((s64)((u32)gteR<<12)*gte_RRLT) >> 12);\
	gte_GG0 = (long)(((s64)((u32)gteG<<12)*gte_GGLT) >> 12);\
	gte_BB0 = (long)(((s64)((u32)gteB<<12)*gte_BBLT) >> 12);\
	gteMAC1 = (long)((gte_RR0 + (((s64)gteIR0 * F12limA1S((s64)(gteRFC << 8) - gte_RR0)) >> 12)) >> 8);\
	gteMAC2 = (long)((gte_GG0 + (((s64)gteIR0 * F12limA2S((s64)(gteGFC << 8) - gte_GG0)) >> 12)) >> 8);\
	gteMAC3 = (long)((gte_BB0 + (((s64)gteIR0 * F12limA3S((s64)(gteBFC << 8) - gte_BB0)) >> 12)) >> 8);

void gteNCDS() {
	s32 gte_LL1, gte_LL2, gte_LL3;
	s32 gte_RRLT, gte_GGLT, gte_BBLT;
	s32 gte_RR0, gte_GG0, gte_BB0;

    gteFLAG = 0;
    GTE_NCDS(0);

	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	MAC2IR1();

	SUM_FLAG;
}

void gteNCDT() {
	s32 gte_LL1, gte_LL2, gte_LL3;
	s32 gte_RRLT, gte_GGLT, gte_BBLT;
	s32 gte_RR0, gte_GG0, gte_BB0;

    gteFLAG = 0;
    GTE_NCDS(0);

	gteR0 = FlimB1(gteMAC1 >> 4);
	gteG0 = FlimB2(gteMAC2 >> 4);
	gteB0 = FlimB3(gteMAC3 >> 4); gteCODE0 = gteCODE;

    GTE_NCDS(1);

	gteR1 = FlimB1(gteMAC1 >> 4);
	gteG1 = FlimB2(gteMAC2 >> 4);
	gteB1 = FlimB3(gteMAC3 >> 4); gteCODE1 = gteCODE;

    GTE_NCDS(2);

	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	MAC2IR1();

	SUM_FLAG;
} 

void gteOP()
{
	int shift = ((psxRegs.code >> 19) & 1) * 12;
    gteFLAG = 0;

    gteMAC1 = (gteD2 * gteIR3 - gteD3 * gteIR2) >> shift;
    gteMAC2 = (gteD3 * gteIR1 - gteD1 * gteIR3) >> shift;
    gteMAC3 = (gteD1 * gteIR2 - gteD2 * gteIR1) >> shift;

	gteIR1 = min ( max (gteMAC1, -32768), 32767 );
	gteFLAG |= ( gteMAC1 != gteIR1 ) << 24;
    gteIR2 = min ( max (gteMAC2, -32768), 32767 );
	gteFLAG |= ( gteMAC2 != gteIR2 ) << 23;
	gteIR3 = min ( max (gteMAC3, -32768), 32767 );
	gteFLAG |= ( gteMAC3 != gteIR3 ) << 22;

	SUM_FLAG
}

void gteDCPL() {

	gteMAC1 = ( (signed long)(gteR)*gteIR1 + (gteIR0*(signed short)FlimA1S(gteRFC - ((gteR*gteIR1)>>12) )) ) >>8;
	gteMAC2 = ( (signed long)(gteG)*gteIR2 + (gteIR0*(signed short)FlimA2S(gteGFC - ((gteG*gteIR2)>>12) )) ) >>8;
	gteMAC3 = ( (signed long)(gteB)*gteIR3 + (gteIR0*(signed short)FlimA3S(gteBFC - ((gteB*gteIR3)>>12) )) ) >>8;

	gteFLAG=0;
	MAC2IR();
 
	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;

	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	SUM_FLAG
}

void gteGPF()
{
	u32 rgb = gteRGB;
	int shift = ((psxRegs.code >> 19) & 1) * 12, color;
    gteFLAG = 0;

	gteMAC1 = (gteIR1 * gteIR0) >> shift;
	gteMAC2 = (gteIR2 * gteIR0) >> shift;
	gteMAC3 = (gteIR3 * gteIR0) >> shift;

	gteIR1 = min ( max (gteMAC1, -32768), 32767 );
	gteFLAG |= (gteMAC1 != gteIR1) << 24;
	gteIR2 = min ( max (gteMAC2, -32768), 32767 );
	gteFLAG |= (gteMAC2 != gteIR2) << 23;
	gteIR3 = min ( max (gteMAC3, -32768), 32767 );
	gteFLAG |= (gteMAC3 != gteIR3) << 22;

	gteFLAG |= ((u32)(gteIR1 >> 4) > 255) << 21;
	color = min ( 255, max (0, gteIR1 >> 4) );
	rgb = (rgb & ~0xff) | (color & 0xff);		// Red
	gteFLAG |= ((u32)(gteIR2 >> 4) > 255) << 20;
	color = min ( 255, max (0, gteIR2 >> 4) );
	rgb = (rgb & ~0xff00) | ((color & 0xff) << 8);	// Green
	gteFLAG |= ((u32)(gteIR3 >> 4) > 255) << 19;
	color = min ( 255, max (0, gteIR3 >> 4) );
	rgb = (rgb & ~0xff0000) | ((color & 0xff) << 16);  // Blue

	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	gteRGB2 = rgb;

	SUM_FLAG
}

void gteGPL()
{
	u32 rgb = gteRGB;
	int shift = ((psxRegs.code >> 19) & 1) * 12, color;
    gteFLAG = 0;

	gteMAC1 += (gteIR1 * gteIR0) >> shift;
	gteMAC2 += (gteIR2 * gteIR0) >> shift;
	gteMAC3 += (gteIR3 * gteIR0) >> shift;

	gteIR1 = min ( max (gteMAC1, -32768), 32767 );
	gteFLAG |= (gteMAC1 != gteIR1) << 24;
	gteFLAG |= ((u32)(gteIR1 >> 4) > 255) << 21;
	color = min ( 255, max (0, gteIR1 >> 4) );
	rgb = (rgb & ~0xff) | (color & 0xff);		// Red

	gteIR2 = min ( max (gteMAC2, -32768), 32767 );
	gteFLAG |= (gteMAC2 != gteIR2) << 23;
	gteFLAG |= ((u32)(gteIR2 >> 4) > 255) << 20;
	color = min ( 255, max (0, gteIR2 >> 4) );
	rgb = (rgb & ~0xff00) | ((color & 0xff) << 8);	// Green

	gteIR3 = min ( max (gteMAC3, -32768), 32767 );
	gteFLAG |= (gteMAC3 != gteIR3) << 22;
	gteFLAG |= ((u32)(gteIR3 >> 4) > 255) << 19;
	color = min ( 255, max (0, gteIR3 >> 4) );
	rgb = (rgb & ~0xff0000) | ((color & 0xff) << 16);	// Blue

	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	gteRGB2 = rgb;

	SUM_FLAG
}

void gteDPCS() {

	gteMAC1 = (gteR<<4) + ( (gteIR0*(signed short)FlimA1S(gteRFC-(gteR<<4)) ) >>12);
	gteMAC2 = (gteG<<4) + ( (gteIR0*(signed short)FlimA2S(gteGFC-(gteG<<4)) ) >>12);
	gteMAC3 = (gteB<<4) + ( (gteIR0*(signed short)FlimA3S(gteBFC-(gteB<<4)) ) >>12);

	gteFLAG = 0;
	MAC2IR();
	
	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	SUM_FLAG
}

void gteDPCT() {

	gteMAC1 = (gteR0<<4) + ( (gteIR0*(signed short)FlimA1S(gteRFC-(gteR0<<4)) ) >>12);
	gteMAC2 = (gteG0<<4) + ( (gteIR0*(signed short)FlimA2S(gteGFC-(gteG0<<4)) ) >>12);
	gteMAC3 = (gteB0<<4) + ( (gteIR0*(signed short)FlimA3S(gteBFC-(gteB0<<4)) ) >>12);
	
	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	gteMAC1 = (gteR0<<4) + ( (gteIR0*(signed short)FlimA1S(gteRFC-(gteR0<<4)) ) >>12);
	gteMAC2 = (gteG0<<4) + ( (gteIR0*(signed short)FlimA2S(gteGFC-(gteG0<<4)) ) >>12);
	gteMAC3 = (gteB0<<4) + ( (gteIR0*(signed short)FlimA3S(gteBFC-(gteB0<<4)) ) >>12);
//	MAC2IR();
    gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	gteMAC1 = (gteR0<<4) + ( (gteIR0*(signed short)FlimA1S(gteRFC-(gteR0<<4)) ) >>12);
	gteMAC2 = (gteG0<<4) + ( (gteIR0*(signed short)FlimA2S(gteGFC-(gteG0<<4)) ) >>12);
	gteMAC3 = (gteB0<<4) + ( (gteIR0*(signed short)FlimA3S(gteBFC-(gteB0<<4)) ) >>12);
	gteFLAG = 0;
	MAC2IR();
    gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	SUM_FLAG
}

#define LOW(a) (((a) < 0) ? 0 : (a))

#define	GTE_NCS(vn)  \
	gte_LL1 = F12limA1U((gteL11*gteVX##vn + gteL12*gteVY##vn + gteL13*gteVZ##vn) >> 12); \
	gte_LL2 = F12limA2U((gteL21*gteVX##vn + gteL22*gteVY##vn + gteL23*gteVZ##vn) >> 12); \
	gte_LL3 = F12limA3U((gteL31*gteVX##vn + gteL32*gteVY##vn + gteL33*gteVZ##vn) >> 12); \
	gteMAC1 = F12limA1U(gteRBK + ((gteLR1*gte_LL1 + gteLR2*gte_LL2 + gteLR3*gte_LL3) >> 12)); \
	gteMAC2 = F12limA2U(gteGBK + ((gteLG1*gte_LL1 + gteLG2*gte_LL2 + gteLG3*gte_LL3) >> 12)); \
	gteMAC3 = F12limA3U(gteBBK + ((gteLB1*gte_LL1 + gteLB2*gte_LL2 + gteLB3*gte_LL3) >> 12));

void gteNCS()
{
    u32 rgb = gteRGB;
    int color;

    s32 LL1 = ((gteL11 * gteVX0 + gteL12 * gteVY0 + gteL13 * gteVZ0) >> 12);
    s32 LL2 = ((gteL21 * gteVX0 + gteL22 * gteVY0 + gteL23 * gteVZ0) >> 12);
    s32 LL3 = ((gteL31 * gteVX0 + gteL32 * gteVY0 + gteL33 * gteVZ0) >> 12);

    s32 C_LL1 = min ( max (LL1, 0), 32767 );
    s32 C_LL2 = min ( max (LL2, 0), 32767 );
    s32 C_LL3 = min ( max (LL3, 0), 32767 );

    gteFLAG  = ( LL1 != C_LL1 ) << 24;
    gteFLAG |= ( LL2 != C_LL2 ) << 23;
    gteFLAG |= ( LL3 != C_LL3 ) << 22;

    gteMAC1 = ((gteLR1 * C_LL1 + gteLR2 * C_LL2 + gteLR3 * C_LL3) >> 12) + gteRBK;
    gteMAC2 = ((gteLG1 * C_LL1 + gteLG2 * C_LL2 + gteLG3 * C_LL3) >> 12) + gteGBK;
    gteMAC3 = ((gteLB1 * C_LL1 + gteLB2 * C_LL2 + gteLB3 * C_LL3) >> 12) + gteBBK;

    gteIR1 = min ( max (gteMAC1, 0), 32767 );
	gteIR2 = min ( max (gteMAC2, 0), 32767 );
	gteIR3 = min ( max (gteMAC3, 0), 32767 );

	gteFLAG |= ( gteMAC1 != gteIR1 ) << 24;
	gteFLAG |= ( gteMAC2 != gteIR2 ) << 23;
	gteFLAG |= ( gteMAC3 != gteIR3 ) << 22;

	color = min ( max (0, gteMAC1 >> 4), 255 );
    gteFLAG |= ( color != (gteMAC1 >> 4) ) << 21;
	rgb = (rgb & ~0xff) | ( (gteMAC1 >> 4) & 0xff);		// Red

	color = min ( max (0, gteMAC2 >> 4), 255 );
    gteFLAG |= ( color != (gteMAC2 >> 4) ) << 20;
	rgb = (rgb & ~0xff00) | (( (gteMAC2 >> 4) & 0xff) << 8);	// Green

	color = min ( max (0, gteMAC3 >> 4), 255 );
    gteFLAG |= ( color != (gteMAC3 >> 4) ) << 19;
	rgb = (rgb & ~0xff0000) | (( (gteMAC3 >> 4) & 0xff) << 16);	// Blue

	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	gteRGB2 = rgb;

    SUM_FLAG
}

void gteNCT() {
	s32 gte_LL1,gte_LL2,gte_LL3;

	gteFLAG = 0;
	
	GTE_NCS(0);

	gteR0 = FlimB1(gteMAC1 >> 4);
	gteG0 = FlimB2(gteMAC2 >> 4);
	gteB0 = FlimB3(gteMAC3 >> 4); gteCODE0 = gteCODE;

	GTE_NCS(1);
	gteR1 = FlimB1(gteMAC1 >> 4);
	gteG1 = FlimB2(gteMAC2 >> 4);
	gteB1 = FlimB3(gteMAC3 >> 4); gteCODE1 = gteCODE;

	GTE_NCS(2);
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	MAC2IR1();

	SUM_FLAG
}

void gteCC() {
	s32 RR0,GG0,BB0;

	gteFLAG = 0;
	
	RR0 = FNC_OVERFLOW1(gteRBK + ((gteLR1*gteIR1 + gteLR2*gteIR2 + gteLR3*gteIR3) >> 12));
	GG0 = FNC_OVERFLOW2(gteGBK + ((gteLG1*gteIR1 + gteLG2*gteIR2 + gteLG3*gteIR3) >> 12));
	BB0 = FNC_OVERFLOW3(gteBBK + ((gteLB1*gteIR1 + gteLB2*gteIR2 + gteLB3*gteIR3) >> 12));

	gteMAC1 = (gteR * RR0) >> 8;
	gteMAC2 = (gteG * GG0) >> 8;
	gteMAC3 = (gteB * BB0) >> 8;
	
	MAC2IR1();
	
	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;

	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	SUM_FLAG
}

void gteINTPL()
{
	u32 rgb = gteRGB;
	int color;

	gteFLAG = 0;

	gteMAC1 = min ( max(gteRFC-gteIR1, -32768), 32767);
    gteFLAG |=  (  gteMAC1 != (gteRFC-gteIR1) ) << 24;
	gteMAC1	= (( gteIR0 * gteMAC1) >> 12) + gteIR1;

	gteMAC2 = min ( max(gteGFC-gteIR2, -32768), 32767);
    gteFLAG |=  (  gteMAC2 != (gteGFC-gteIR2) ) << 23;
	gteMAC2	= (( gteIR0 * gteMAC2) >> 12) + gteIR2;

	gteMAC3 = min ( max(gteBFC-gteIR3, -32768), 32767);
    gteFLAG |=  (  gteMAC3 != (gteBFC-gteIR3) ) << 22;
	gteMAC3	= (( gteIR0 * gteMAC3) >> 12) + gteIR3;

	gteIR1 = min (max (gteMAC1, -32768), 32767);
	gteFLAG |= ( gteMAC1 != gteIR1 ) << 24;
	gteIR2 = min (max (gteMAC2, -32768), 32767);
	gteFLAG |= ( gteMAC2 != gteIR2 ) << 23;
	gteIR3 = min (max (gteMAC3, -32768), 32767);
	gteFLAG |= ( gteMAC3 != gteIR3 ) << 22;

	gteFLAG |= ((u32)(gteIR1 >> 4) > 255) << 21;
	color = min ( 255, max (0, gteIR1 >> 4) );
	rgb = (rgb & ~0xff) | (color & 0xff);		// Red
	gteFLAG |= ((u32)(gteIR2 >> 4) > 255) << 20;
	color = min ( 255, max (0, gteIR2 >> 4) );
	rgb = (rgb & ~0xff00) | ((color & 0xff) << 8);	// Green
	gteFLAG |= ((u32)(gteIR3 >> 4) > 255) << 19;
	color = min ( 255, max (0, gteIR3 >> 4) );
	rgb = (rgb & ~0xff0000) | ((color & 0xff) << 16);	// Blue

	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	gteRGB2 = rgb;

    SUM_FLAG
}

void gteCDP() { //test opcode
	double RR0,GG0,BB0;

	gteFLAG = 0;

	RR0 = NC_OVERFLOW1(gteRBK + (gteLR1*gteIR1 +gteLR2*gteIR2 + gteLR3*gteIR3));
	GG0 = NC_OVERFLOW2(gteGBK + (gteLG1*gteIR1 +gteLG2*gteIR2 + gteLG3*gteIR3));
	BB0 = NC_OVERFLOW3(gteBBK + (gteLB1*gteIR1 +gteLB2*gteIR2 + gteLB3*gteIR3));
	gteMAC1 = gteR*RR0 + gteIR0*limA1S(gteRFC-gteR*RR0);
	gteMAC2 = gteG*GG0 + gteIR0*limA2S(gteGFC-gteG*GG0);
	gteMAC3 = gteB*BB0 + gteIR0*limA3S(gteBFC-gteB*BB0);

	MAC2IR1();
	gteRGB0 = gteRGB1;
	gteRGB1 = gteRGB2;
	
	gteR2 = FlimB1(gteMAC1 >> 4);
	gteG2 = FlimB2(gteMAC2 >> 4);
	gteB2 = FlimB3(gteMAC3 >> 4); gteCODE2 = gteCODE;

	SUM_FLAG
}
