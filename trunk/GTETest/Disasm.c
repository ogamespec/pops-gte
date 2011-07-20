// Project VisualStation: Disassembler for PSX CPU Module instruction set architecture.
// Based on IDT79R3041 manual. Some instructions may be missed in PSX CPU, but I added them anyway.
// GTE instructions are included.
#include <sys/types.h>
#include <libapi.h>
#include "disasm.h"

//#define UPPERCASE
#define COP_UPPERCASE

typedef             char    s8;
typedef             short   s16;
typedef             long    s32;
typedef unsigned    char    u8;
typedef unsigned    short   u16;
typedef unsigned    long    u32;

#ifndef __cplusplus
typedef enum { false = 0, true } bool;
#endif

static  DisasmData *dis;        // Current disassembler context.

/* Mnemonics */
static char *Mnem[] = {
#ifdef UPPERCASE
 "J", "JAL", "BEQ", "BNE", "BLEZ", "BGTZ",
 "ADDI", "ADDIU", "SLTI", "SLTIU", "ANDI", "ORI", "XORI", "LUI",
 "LB", "LH", "LWL", "LW", "LBU", "LHU", "LWR",
 "SB", "SH", "SWL", "SW", "SWR",
 "LWC0", "LWC1", "LWC2", "LWC3",
 "SWC0", "SWC1", "SWC2", "SWC3",

 "SLL", "SRL", "SRA", "SLLV", "SRLV", "SRAV",
 "JR", "JALR", "SYSCALL", "BREAK",
 "MFHI", "MTHI", "MFLO", "MTLO",
 "MULT", "MULTU", "DIV", "DIVU",
 "ADD", "ADDU", "SUB", "SUBU", "AND", "OR", "XOR", "NOR",
 "SLT", "SLTU",

 "BLTZ", "BGEZ", "BLTZAL", "BGEZAL",

 "MFC0", "CFC0", "MTC0", "CTC0", "BC0F", "BC0T",
 "MFC1", "CFC1", "MTC1", "CTC1", "BC1F", "BC1T",
 "MFC2", "CFC2", "MTC2", "CTC2", "BC2F", "BC2T",
 "MFC3", "CFC3", "MTC3", "CTC3", "BC3F", "BC3T",

 "TLBR", "TLBWI", "TLBWR", "TLBP", "RFE",

 "COP0", "COP1", "COP2", "COP3",

 /* GTE */
 "RTPS", "RTPT", "DCPL", "DPCS", "DPCT", "INTPL", "NCS", "NCT",
 "NCDS", "NCDT", "NCCS", "NCCT", "CDP", "CC", "NCLIP", "AVSZ3",
 "AVSZ4", "MVMVA", "SQR", "OP", "GPF", "GPL",

 /* Simplified */
 "B", "LI", "NOP", "MOVE", "BEQZ", "BNEZ",
#else
 "j", "jal", "beq", "bne", "blez", "bgtz",
 "addi", "addiu", "slti", "sltiu", "andi", "ori", "xori", "lui",
 "lb", "lh", "lwl", "lw", "lbu", "lhu", "lwr",
 "sb", "sh", "swl", "sw", "swr",
 "lwc0", "lwc1", "lwc2", "lwc3",
 "swc0", "swc1", "swc2", "swc3",

 "sll", "srl", "sra", "sllv", "srlv", "srav",
 "jr", "jalr", "syscall", "break",
 "mfhi", "mthi", "mflo", "mtlo",
 "mult", "multu", "div", "divu",
 "add", "addu", "sub", "subu", "and", "or", "xor", "nor",
 "slt", "sltu",

 "bltz", "bgez", "bltzal", "bgezal",

 "mfc0", "cfc0", "mtc0", "ctc0", "bc0f", "bc0t",
 "mfc1", "cfc1", "mtc1", "ctc1", "bc1f", "bc1t",
 "mfc2", "cfc2", "mtc2", "ctc2", "bc2f", "bc2t",
 "mfc3", "cfc3", "mtc3", "ctc3", "bc3f", "bc3t",

 "tlbr", "tlbwi", "tlbwr", "tlbp", "rfe",

 "cop0", "cop1", "cop2", "cop3",

 /* GTE */
 "rtps", "rtpt", "dcpl", "dpcs", "dpct", "intpl", "ncs", "nct",
 "ncds", "ncdt", "nccs", "ncct", "cdp", "cc", "nclip", "avsz3",
 "avsz4", "mvmva", "sqr", "op", "gpf", "gpl",

 /* Simplified */
 "b", "li", "nop", "move", "beqz", "bnez",
#endif
};

enum {
 I_J=0, I_JAL, I_BEQ, I_BNE, I_BLEZ, I_BGTZ,
 I_ADDI, I_ADDIU, I_SLTI, I_SLTIU, I_ANDI, I_ORI, I_XORI, I_LUI,
 I_LB, I_LH, I_LWL, I_LW, I_LBU, I_LHU, I_LWR,
 I_SB, I_SH, I_SWL, I_SW, I_SWR,
 I_LWC0, I_LWC1, I_LWC2, I_LWC3,
 I_SWC0, I_SWC1, I_SWC2, I_SWC3,

 I_SLL, I_SRL, I_SRA, I_SLLV, I_SRLV, I_SRAV,
 I_JR, I_JALR, I_SYSCALL, I_BREAK,
 I_MFHI, I_MTHI, I_MFLO, I_MTLO,
 I_MULT, I_MULTU, I_DIV, I_DIVU,
 I_ADD, I_ADDU, I_SUB, I_SUBU, I_AND, I_OR, I_XOR, I_NOR,
 I_SLT, I_SLTU,

 I_BLTZ, I_BGEZ, I_BLTZAL, I_BGEZAL,

 I_MFC0, I_CFC0, I_MTC0, I_CTC0, I_BC0F, I_BC0T,
 I_MFC1, I_CFC1, I_MTC1, I_CTC1, I_BC1F, I_BC1T,
 I_MFC2, I_CFC2, I_MTC2, I_CTC2, I_BC2F, I_BC2T,
 I_MFC3, I_CFC3, I_MTC3, I_CTC3, I_BC3F, I_BC3T,

 I_TLBR, I_TLBWI, I_TLBWR, I_TLBP, I_RFE,

 I_COP0, I_COP1, I_COP2, I_COP3,

 I_RTPS, I_RTPT, I_DCPL, I_DPCS, I_DPCT, I_INTPL, I_NCS, I_NCT,
 I_NCDS, I_NCDT, I_NCCS, I_NCCT, I_CDP, I_CC, I_NCLIP, I_AVSZ3,
 I_AVSZ4, I_MVMVA, I_SQR, I_OP, I_GPF, I_GPL,

 I_B, I_LI, I_NOP, I_MOVE, I_BEQZ, I_BNEZ,

};

/* Register names. */
static char *gprname[32] = {
#ifdef UPPERCASE
 "ZR", "AT", "V0", "V1", "A0", "A1", "A2", "A3", 
 "T0", "T1", "T2", "T3", "T4", "T5", "T6", "T7",
 "S0", "S1", "S2", "S3", "S4", "S5", "S6", "S7",
 "T8", "T9", "K0", "K1", "GP", "SP", "FP", "RA"
#else
 "zr", "at", "v0", "v1", "a0", "a1", "a2", "a3", 
 "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
 "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
 "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"
#endif
};

static char *cp0name[32] = {
#if defined(COP_UPPERCASE) || defined(UPPERCASE)
 "INX", "RAND", "TLBLO", "R3", "CTXT", "R5", "R6", "R7", 
 "BADVADDR", "R9", "TLBHI", "R11", "SR", "CAUSE", "EPC", "PRID", 
 "R16", "R17", "R18", "R19", "R20", "R21", "R22", "R23", 
 "R24", "R25", "R26", "R27", "R28", "R29", "R30", "R31"
#else
 "inx", "rand", "tlblo", "r3", "ctxt", "r5", "r6", "r7", 
 "badvaddr", "r9", "tlbhi", "r11", "sr", "cause", "epc", "prid", 
 "r16", "r17", "r18", "r19", "r20", "r21", "r22", "r23", 
 "r24", "r25", "r26", "r27", "r28", "r29", "r30", "r31"
#endif
};

static char *gtedata[32] = {
#if defined(COP_UPPERCASE) || defined(UPPERCASE)
 "VXY0", "VZ0", "VXY1", "VZ1", "VXY2", "VX2", "RGB", "OTZ",
 "IR0", "IR1", "IR2", "IR3", "SXY0", "SXY1", "SXY2", "SXYP",
 "SZ0", "SZ1", "SZ2", "SZ3", "RGB0", "RGB1", "RGB2", "R23",
 "MAC0", "MAC1", "MAC2", "MAC3", "IRGB", "ORGB", "LZCS", "LZCR"
#else
 "vxy0", "vz0", "vxy1", "vz1", "vxy2", "vz2", "rgb", "otz",
 "ir0", "ir1", "ir2", "ir3", "sxy0", "sxy1", "sxy2", "sxyp",
 "sz0", "sz1", "sz2", "sz3", "rgb0", "rgb1", "rgb2", "r23",
 "mac0", "mac1", "mac2", "mac3", "irgb", "orgb", "lzcs", "lzcr"
#endif
};

static char *gtectrl[32] = {
#if defined(COP_UPPERCASE) || defined(UPPERCASE)
 "R11R12", "R13R21", "R22R23", "R31R32", "R33", "TRX", "TRY", "TRZ",
 "L11L12", "L13L21", "L22L23", "Ll31L32", "L33", "RBK", "GBK", "BBK",
 "LR1LR2", "LR3LG1", "LG2LG3", "LB1LB2", "LB3", "RFC", "GFC", "BFC",
 "OFX", "OFY", "H", "DQA", "DQB", "ZSF3", "ZSF4", "FLAG"
#else
 "r11r12", "r13r21", "r22r23", "r31r32", "r33", "trx", "try", "trz",
 "l11l12", "113l21", "l22l23", "l31l32", "l33", "rbk", "gbk", "bbk",
 "lr1lr2", "lr3lg1", "lg2lg3", "lb1lb2", "lb3", "rfc", "gfc", "bfc",
 "ofx", "ofy", "h", "dqa", "dqb", "zsf3", "zsf4", "flag"
#endif
};

#define COMMA   ", "
#define LPAREN  " ("
#define RPAREN  ")"
#define HEX1    "0x"
#define HEX2    ""

/* Quick decoder */
#define DIS_OP  (dis->instr >> 26)
#define DIS_OP2 (dis->instr & 0x3f)
#define DIS_RS  ((dis->instr >> 21) & 0x1f)
#define DIS_RT  ((dis->instr >> 16) & 0x1f)
#define DIS_RD  ((dis->instr >> 11) & 0x1f)
#define DIS_SA  ((dis->instr >> 6) & 0x1f)
#define DIS_IMM (dis->instr & 0xffff)
#define DIS_OFS ( (dis->instr & 0x8000) ? (((dis->instr & 0xFFFF) << 2) | 0xFFFC0000) : ((dis->instr & 0xFFFF) << 2) )

// Smart SIMM formatting (if hex=1, then force HEX; if s=1, use sign)
static char * simm(int val, int hex, int s)
{
    static char out[16];
    if (val & 0x8000) val |= 0xFFFF0000;
    if( ((val >= -128) && (val <= 128)) && !hex) sprintf(out, "%i", val);
    else
    {
        u16 hexval = (u16)val;
        if((hexval & 0x8000) && s) sprintf(out, "-" HEX1 "%04X" HEX2, ((~hexval) & 0xffff) + 1);
        else sprintf(out, HEX1 "%04X" HEX2, hexval);
    }
    return out;
}

static void name (int id)
{
    strncpy (dis->mnem, Mnem[id], sizeof dis->mnem);
}

static void type (u32 types)
{
    dis->type |= types;
}

static void rt_ofs_base (int cop)
{
    if (cop == -1) sprintf (dis->operands, "%s" COMMA "%s" LPAREN "%s" RPAREN, gprname[DIS_RT], simm(DIS_IMM, 0, 1), gprname[DIS_RS]);
    else switch (cop)
    {
        case 0: sprintf (dis->operands, "%s" COMMA "%s" LPAREN "%s" RPAREN, cp0name[DIS_RT], simm(DIS_IMM, 0, 1), gprname[DIS_RS]); break;
        case 2: sprintf (dis->operands, "%s" COMMA "%s" LPAREN "%s" RPAREN, gtedata[DIS_RT], simm(DIS_IMM, 0, 1), gprname[DIS_RS]); break;
        default:
            sprintf (dis->operands,
#if defined(COP_UPPERCASE) || defined(UPPERCASE)
                "r"
#else
                "R"
#endif
                "%i" COMMA "%s" LPAREN "%s" RPAREN, DIS_RT, simm(DIS_IMM, 0, 1), gprname[DIS_RS]);
    }
}

static void rt_rs_imm(bool hex)
{
    sprintf (dis->operands, "%s" COMMA "%s" COMMA "%s", gprname[DIS_RT], gprname[DIS_RS], simm(DIS_IMM, hex, hex?0:1));
}

static void rt_imm(bool hex)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RT], simm(DIS_IMM, hex, hex?0:1));
}

static void rd_rs_rt(void)
{
    sprintf (dis->operands, "%s" COMMA "%s" COMMA "%s", gprname[DIS_RD], gprname[DIS_RS], gprname[DIS_RT]);
}

static void rd_rs(void)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RD], gprname[DIS_RS]);
}

static void rd_rt_sa(void)
{
    sprintf (dis->operands, "%s" COMMA "%s" COMMA "%i", gprname[DIS_RD], gprname[DIS_RT], DIS_SA);
}

static void rd_rt_rs(void)
{
    sprintf (dis->operands, "%s" COMMA "%s" COMMA "%s", gprname[DIS_RD], gprname[DIS_RT], gprname[DIS_RS]);
}

static void rs_rt(void)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RS], gprname[DIS_RT]);
}

static void rs_rd(void)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RS], gprname[DIS_RD]);
}

static void rt_cop0(void)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RT], cp0name[DIS_RD]);
}

static void rt_cp2d(void)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RT], gtedata[DIS_RD]);
}

static void rt_cp2c(void)
{
    sprintf (dis->operands, "%s" COMMA "%s", gprname[DIS_RT], gtectrl[DIS_RD]);
}

static void rs(void)
{
    sprintf (dis->operands, "%s", gprname[DIS_RS]);
}

static void rd(void)
{
    sprintf (dis->operands, "%s", gprname[DIS_RD]);
}

static void branch_rs_rt(void)
{
    sprintf ( dis->operands, "%s" COMMA "%s" COMMA HEX1 "%08X" HEX2,
              gprname[DIS_RS], gprname[DIS_RT],
              dis->pc + DIS_OFS + 4);
}

static void branch_rs(void)
{
    sprintf ( dis->operands, "%s" COMMA HEX1 "%08X" HEX2,
              gprname[DIS_RS],
              dis->pc + DIS_OFS + 4);
}

static void branch(void)
{
    sprintf ( dis->operands, HEX1 "%08X" HEX2, dis->pc + DIS_OFS + 4);
}

static void gteops(void)
{
/*
     -----------------------------------------------------------------------------------------------
    |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|
    |-----------------------------------------------------------------------------------------------|
    | 0  1  0  0  1  0|       OP2       |SF| MX  |  V  | CV  |  LM    | 0  0  0  0|      OP1        |
     -----------------------------------------------------------------------------------------------
*/
    u32 i = dis->instr;
    sprintf ( dis->operands, "%i" COMMA "%i" COMMA "%i" COMMA "%i" COMMA "%i", 
              (i >> 19) & 1, 
              (i >> 17) & 3, 
              (i >> 15) & 3, 
              (i >> 13) & 3, 
              (i >> 10) & 7 );
}

// Reserved Instruction.
static void trap (void)
{
}

void PSXDisasm(DisasmData *disa)
{
    dis = disa;

    dis->mnem[0] = dis->operands[0] = 0;
    dis->type = 0;

    if (dis->instr == 0 && dis->simplify)
    {
        name (I_NOP);
        dis->type = DISA_TYPE_NOP | DISA_TYPE_SIMPLE | DISA_TYPE_RTYPE;
        return;
    }

    switch (DIS_OP)
    {
        case 000:
    switch (DIS_OP2)
    {
        case 000: name(I_SLL); rd_rt_sa(); type (DISA_TYPE_SHIFT|DISA_TYPE_RTYPE); break;   /* Shift */
        case 002: name(I_SRL); rd_rt_sa(); type (DISA_TYPE_SHIFT|DISA_TYPE_RTYPE); break;
        case 003: name(I_SRA); rd_rt_sa(); type (DISA_TYPE_SHIFT|DISA_TYPE_RTYPE); break;
        case 004: name(I_SLLV); rd_rt_rs(); type (DISA_TYPE_SHIFT|DISA_TYPE_RTYPE); break;
        case 006: name(I_SRLV); rd_rt_rs(); type (DISA_TYPE_SHIFT|DISA_TYPE_RTYPE); break;
        case 007: name(I_SRAV); rd_rt_rs(); type (DISA_TYPE_SHIFT|DISA_TYPE_RTYPE); break;

        case 010: name(I_JR); rs();  type (DISA_TYPE_JUMP|DISA_TYPE_RTYPE); break;  /* Jumps */
        case 011: name(I_JALR); rs_rd();  type (DISA_TYPE_JUMP|DISA_TYPE_RTYPE); break;

        // Syscall and Break operands are appeared later.
        case 014: name(I_SYSCALL); /* sprintf (dis->operands, HEX1 "%05X" HEX2, (dis->instr >> 6) & 0xFFFFF);*/ type (DISA_TYPE_SPECIAL|DISA_TYPE_RTYPE); break;
        case 015: name(I_BREAK); /* sprintf (dis->operands, HEX1 "%05X" HEX2, (dis->instr >> 6) & 0xFFFFF);*/ type (DISA_TYPE_SPECIAL|DISA_TYPE_RTYPE); break;

        case 020: name(I_MFHI); rd(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;   /* Mul/Div */
        case 021: name(I_MTHI); rd(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;
        case 022: name(I_MFLO); rd(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;
        case 023: name(I_MTLO); rd(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;
        case 030: name(I_MULT); rs_rt(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;
        case 031: name(I_MULTU); rs_rt(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;
        case 032: name(I_DIV); rs_rt(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;
        case 033: name(I_DIVU); rs_rt(); type (DISA_TYPE_MULDIV|DISA_TYPE_RTYPE); break;

        case 040: name(I_ADD); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;    /* ALU 3-op */
        case 041: if (DIS_RT || !dis->simplify) { name(I_ADDU); rd_rs_rt(); }
                  else { name(I_MOVE); rd_rs(); }
                  type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 042: name(I_SUB); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 043: name(I_SUBU); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 044: name(I_AND); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 045: name(I_OR); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 046: name(I_XOR); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 047: name(I_NOR); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 052: name(I_SLT); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;
        case 053: name(I_SLTU); rd_rs_rt(); type (DISA_TYPE_ALU3|DISA_TYPE_RTYPE); break;

        default: trap(); break;
    }
        break;

        case 001:
    switch (DIS_RT)
    {
        case 000: name(I_BLTZ); branch_rs(); type (DISA_TYPE_BRANCH|DISA_TYPE_RTYPE);  break; /* Branch */
        case 001: name(I_BGEZ); branch_rs(); type (DISA_TYPE_BRANCH|DISA_TYPE_RTYPE); break;
        case 020: name(I_BLTZAL); branch_rs(); type (DISA_TYPE_BRANCH|DISA_TYPE_RTYPE); break;
        case 021: name(I_BGEZAL); branch_rs(); type (DISA_TYPE_BRANCH|DISA_TYPE_RTYPE); break;

        default: trap(); break;
    }
        break;

        case 020:                                                                       /* COP0 */
            switch (DIS_RS)
            {
                case 000: name(I_MFC0); rt_cop0(); type (DISA_TYPE_COP0|DISA_TYPE_RTYPE); break;
                case 004: name(I_MTC0); rt_cop0(); type (DISA_TYPE_COP0|DISA_TYPE_RTYPE); break;
                case 010:
                    switch (DIS_RT)
                    {
                        case 000: name(I_BC0F); branch(); type(DISA_TYPE_BRANCH|DISA_TYPE_COP0|DISA_TYPE_ITYPE); break;
                        case 001: name(I_BC0T); branch(); type(DISA_TYPE_BRANCH|DISA_TYPE_COP0|DISA_TYPE_ITYPE); break;
                        default: trap(); break;
                    }
                    break;
                case 020:
                    switch (dis->instr & 0x1f)
                    {
                        case 001: name(I_TLBR); type (DISA_TYPE_COP0); break;
                        case 002: name(I_TLBWI); type (DISA_TYPE_COP0); break;
                        case 006: name(I_TLBWR); type (DISA_TYPE_COP0); break;
                        case 010: name(I_TLBP); type (DISA_TYPE_COP0); break;
                        case 020: name(I_RFE); type (DISA_TYPE_COP0); break;
                        default: trap(); break;
                    }
                    break;
                default: name(I_COP0); sprintf(dis->operands, HEX1 "%08X" HEX2, dis->instr & 0x03FFFFFF); type (DISA_TYPE_COP0); break;
            }
            break;

/*
     -----------------------------------------------------------------------------------------------
    |31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00|
    |-----------------------------------------------------------------------------------------------|
    | 0  1  0  0  1  0|       OP2       |SF| MX  |  V  | CV  |  LM    | 0  0  0  0|      OP1        |
     -----------------------------------------------------------------------------------------------

    Sorted by OP1:
                                                      
    RTPS    cop2 0x180001 = 0100.10 10.0001. 1000.0000.00 00.00 00.0001     01
    NCLIP  cop2 0x1400006 = 0100.10 11.0100. 0000.0000.00 00.00 00.0110     06
    OP     cop2 0x170000c = 0100.10 11.0111. 0000.0000.00 00.00 00.1100     14
    DPCS    cop2 0x780010 = 0100.10 10.0111. 1000.0000.00 00.00 01.0000     20
    INTPL   cop2 0x980011 = 0100.10 10.1001. 1000.0000.00 00.00 01.0001     21
    MVMVA   cop2 0x400012 = 0100.10 10.0100. 0000.0000.00 00.00 01.0010     22
    NCDS    cop2 0xe80413 = 0100.10 10.1110. 1000.0000.01 00.00 01.0011     23
    CDP    op2 0x1280414  = 0100.10 11.0010. 1000.0000.01 00.00 01.0100     24
    NCDT    cop2 0xf80416 = 0100.10 10.1111. 1000.0000.01 00.00 01.0110     26
    NCCS   cop2 0x108041b = 0100.10 11.0000. 1000.0000.01 00.00 01.1011     33
    CC     cop2 0x138041c = 0100.10 11.0011. 1000.0000.01 00.00 01.1100     34
    NCS     cop2 0xc8041e = 0100.10 10.1100. 1000.0000.01 00.00 01.1110     36
    NCT     cop2 0xd80420 = 0100.10 10.1101. 1000.0000.01 00.00 10.0000     40
    SQR     cop2 0xa00428 = 0100.10 10.1010. 0000.0000.01 00.00 10.1000     50
    DCPL    cop2 0x680029 = 0100.10 10.0110. 1000.0000.00 00.00 10.1001     51
    DPCT    cop2 0xf8002a = 0100.10 10.1111. 1000.0000.00 00.00 10.1010     52
    AVSZ3  cop2 0x158002d = 0100.10 11.0101. 1000.0000.00 00.00 10.1101     55
    AVSZ4  cop2 0x168002e = 0100.10 11.0110. 1000.0000.00 00.00 10.1110     56
    RTPT    cop2 0x280030 = 0100.10 10.0010. 1000.0000.00 00.00 11.0000     60
    GPF    cop2 0x190003d = 0100.10 11.1001. 0000.0000.00 00.00 11.1101     75
    GPL    cop2 0x1a0003e = 0100.10 11.1010. 0000.0000.00 00.00 11.1110     76
    NCCT   cop2 0x118043f = 0100.10 11.0001. 1000.0000.01 00.00 11.1111     77
*/

        case 022:                                                                       /* GTE */
            switch (DIS_OP2)
            {
                case 000:
                    switch (DIS_RS)
                    {
                        case 000: name(I_MFC2); rt_cp2d(); type (DISA_TYPE_COP2|DISA_TYPE_RTYPE); break;
                        case 002: name(I_CFC2); rt_cp2c(); type (DISA_TYPE_COP2|DISA_TYPE_RTYPE); break;
                        case 004: name(I_MTC2); rt_cp2d(); type (DISA_TYPE_COP2|DISA_TYPE_RTYPE); break;
                        case 006: name(I_CTC2); rt_cp2c(); type (DISA_TYPE_COP2|DISA_TYPE_RTYPE); break;
                        default: trap(); break;
                    }
                    break;
                case 001: name(I_RTPS); gteops(); type(DISA_TYPE_COP2); break;
                case 006: name(I_NCLIP); gteops(); type(DISA_TYPE_COP2); break;
                case 014: name(I_OP); gteops(); type(DISA_TYPE_COP2); break;
                case 020: name(I_DPCS); gteops(); type(DISA_TYPE_COP2); break;
                case 021: name(I_INTPL); gteops(); type(DISA_TYPE_COP2); break;
                case 022: name(I_MVMVA); gteops(); type(DISA_TYPE_COP2); break;
                case 023: name(I_NCDS); gteops(); type(DISA_TYPE_COP2); break;
                case 024: name(I_CDP); gteops(); type(DISA_TYPE_COP2); break;
                case 026: name(I_NCDT); gteops(); type(DISA_TYPE_COP2); break;
                case 033: name(I_NCCS); gteops(); type(DISA_TYPE_COP2); break;
                case 034: name(I_CC); gteops(); type(DISA_TYPE_COP2); break;
                case 036: name(I_NCS); gteops(); type(DISA_TYPE_COP2); break;
                case 040: name(I_NCT); gteops(); type(DISA_TYPE_COP2); break;
                case 050: name(I_SQR); gteops(); type(DISA_TYPE_COP2); break;
                case 051: name(I_DCPL); gteops(); type(DISA_TYPE_COP2); break;
                case 052: name(I_DPCT); gteops(); type(DISA_TYPE_COP2); break;
                case 055: name(I_AVSZ3); gteops(); type(DISA_TYPE_COP2); break;
                case 056: name(I_AVSZ4); gteops(); type(DISA_TYPE_COP2); break;
                case 060: name(I_RTPT); gteops(); type(DISA_TYPE_COP2); break;
                case 075: name(I_GPF); gteops(); type(DISA_TYPE_COP2); break;
                case 076: name(I_GPL); gteops(); type(DISA_TYPE_COP2); break;
                case 077: name(I_NCCT); gteops(); type(DISA_TYPE_COP2); break;
                default: name(I_COP2); sprintf(dis->operands, HEX1 "%08X" HEX2, dis->instr & 0x03FFFFFF); type (DISA_TYPE_COP2); break;
            }
            break;

        case 002: name(I_J); sprintf (dis->operands, HEX1 "%08X" HEX2, (dis->pc & 0xF0000000) | ((dis->instr & 0x03FFFFFF) << 2)); type (DISA_TYPE_JUMP|DISA_TYPE_JTYPE); break;
        case 003: name(I_JAL); sprintf (dis->operands, HEX1 "%08X" HEX2, (dis->pc & 0xF0000000) | ((dis->instr & 0x03FFFFFF) << 2)); type (DISA_TYPE_JUMP|DISA_TYPE_JTYPE);  break;
        case 004: if ( (DIS_RS + DIS_RT) == 0 || !dis->simplify )
                  {
                    name(I_B); branch();
                  }
                  else
                  {
                    if (DIS_RT || !dis->simplify) { name(I_BEQ); branch_rs_rt(); }
                    else { name(I_BEQZ); branch_rs(); }
                  }
                  type (DISA_TYPE_BRANCH|DISA_TYPE_ITYPE); break;
        case 005: if (DIS_RT || !dis->simplify) { name(I_BNE); branch_rs_rt(); }
                  else { name(I_BNEZ); branch_rs(); }
                  type (DISA_TYPE_BRANCH|DISA_TYPE_ITYPE); break;
        case 006: name(I_BLEZ); branch_rs(); type (DISA_TYPE_BRANCH|DISA_TYPE_ITYPE); break;
        case 007: name(I_BGTZ); branch_rs(); type (DISA_TYPE_BRANCH|DISA_TYPE_ITYPE); break;

        case 010: name(I_ADDI); rt_rs_imm(0); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE); break;  /* ALU */
        case 011: if (DIS_RS || !dis->simplify) { name(I_ADDIU); rt_rs_imm(0); }
                  else { name(I_LI); rt_imm(0); }
                  type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;
        case 012: name(I_SLTI); rt_rs_imm(0); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;
        case 013: name(I_SLTIU); rt_rs_imm(0); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;
        case 014: name(I_ANDI); rt_rs_imm(1); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;
        case 015: name(I_ORI); rt_rs_imm(1); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;
        case 016: name(I_XORI); rt_rs_imm(1); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;
        case 017: name(I_LUI); rt_imm(1); type (DISA_TYPE_ALU|DISA_TYPE_ITYPE);  break;

        case 040: name (I_LB); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;  /* Load/Store */
        case 041: name (I_LH); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 042: name (I_LWL); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 043: name (I_LW); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 044: name (I_LBU); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 045: name (I_LHU); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 046: name (I_LWR); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 050: name (I_SB); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 051: name (I_SH); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 052: name (I_SWL); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 053: name (I_SW); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        case 056: name (I_SWR); rt_ofs_base (-1); type (DISA_TYPE_LDST|DISA_TYPE_ITYPE);  break;
        
        case 060: name (I_LWC0); rt_ofs_base (0); type (DISA_TYPE_COP0|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;  /* COP Load/Store */
        case 061: name (I_LWC1); rt_ofs_base (1); type (DISA_TYPE_COP1|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;
        case 062: name (I_LWC2); rt_ofs_base (2); type (DISA_TYPE_COP2|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;
        case 063: name (I_LWC3); rt_ofs_base (3); type (DISA_TYPE_COP3|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;
        case 070: name (I_SWC0); rt_ofs_base (0); type (DISA_TYPE_COP0|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;
        case 071: name (I_SWC1); rt_ofs_base (1); type (DISA_TYPE_COP1|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;
        case 072: name (I_SWC2); rt_ofs_base (2); type (DISA_TYPE_COP2|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;
        case 073: name (I_SWC3); rt_ofs_base (3); type (DISA_TYPE_COP3|DISA_TYPE_LDST|DISA_TYPE_ITYPE); break;

        default: trap(); break;
    }
}
