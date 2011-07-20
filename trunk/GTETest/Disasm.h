// Project VisualStation: PSX Disassembler.

// Instruction types.
#define DISA_TYPE_ITYPE     0x80000000
#define DISA_TYPE_JTYPE     0x40000000
#define DISA_TYPE_RTYPE     0x20000000

#define DISA_TYPE_LDST      0x00000001
#define DISA_TYPE_ALU       0x00000002
#define DISA_TYPE_ALU3      0x00000004
#define DISA_TYPE_SHIFT     0x00000008
#define DISA_TYPE_MULDIV    0x00000010
#define DISA_TYPE_JUMP      0x00000020
#define DISA_TYPE_BRANCH    0x00000040
#define DISA_TYPE_SPECIAL   0x00000080
#define DISA_TYPE_COP0      0x00000100
#define DISA_TYPE_COP1      0x00000200
#define DISA_TYPE_COP2      0x00000400
#define DISA_TYPE_COP3      0x00000800
#define DISA_TYPE_NOP       0x00001000

#define DISA_TYPE_SIMPLE    0x10000000

typedef struct DisasmData
{
    /*
     * Input parameters.
    */ 

    u_long  instr;          // Instruction to disassemble
    u_long  pc;             // Program Counter

    int     simplify;       // Use simplified notation

    /*
     * Output parameters.
    */

    char    mnem[16];
    char    operands[64];
    u_long  type;
} DisasmData;

void    PSXDisasm (DisasmData *disa);
