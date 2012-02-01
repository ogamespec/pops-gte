#include <stdio.h>
#include "gte_divider2.h"

typedef signed   char       s8;
typedef signed   short      s16;
typedef signed   long       s32;
typedef signed   __int64    s64;
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef unsigned long       u32;
typedef unsigned __int64    u64;

main ()
{

    u16 n = 0xA0;
    u16 d = 0x200;

    u32 result = DIVIDE ( n, d );

    printf ( "%04X / %04X = %08X\n", n, d, result );
}