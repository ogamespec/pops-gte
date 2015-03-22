# Introduction #

Pcsx GTE instruction table:

```
void (*psxCP2[64])() = {
    psxBASIC, gteRTPS , psxNULL , psxNULL, psxNULL, psxNULL , gteNCLIP, psxNULL, // 00
    psxNULL , psxNULL , psxNULL , psxNULL, gteOP  , psxNULL , psxNULL , psxNULL, // 08
    gteDPCS , gteINTPL, gteMVMVA, gteNCDS, gteCDP , psxNULL , gteNCDT , psxNULL, // 10
    psxNULL , psxNULL , psxNULL , gteNCCS, gteCC  , psxNULL , gteNCS  , psxNULL, // 18

    gteNCT  , psxNULL , psxNULL , psxNULL, psxNULL, psxNULL , psxNULL , psxNULL, // 20
    gteSQR  , gteDPCL , gteDPCT , psxNULL, psxNULL, gteAVSZ3, gteAVSZ4, psxNULL, // 28 
    gteRTPT , psxNULL , psxNULL , psxNULL, psxNULL, psxNULL , psxNULL , psxNULL, // 30
    psxNULL , psxNULL , psxNULL , psxNULL, psxNULL, gteGPF  , gteGPL  , gteNCCT  // 38
};
```

Pops GTE instruction table:

```
GTEInstructions: (0x0002CBD8):
    ---   RTPS  ---   ---   ---   ---   NCLIP ---   
    ---   ---   ---   ---   OP    ---   ---   ---   
    DPCS  INTPL MVMVA NCDS  DPCL  ---   NCDT  ---   
    ---   ---   ---   NCCS  CC    ---   NCS   ---   

    NCT   ---   ---   ---   ---   ---   ---   ---   
    SQR   CDP   DPCT  ---   ---   AVSZ3 AVSZ4 ---   
    RTPT  ---   ---   ---   ---   ---   ---   ---   
    ---   ---   ---   ---   ---   GPF   GPL   NCCT
```

I do not why, but DPCL and CDP are located in wrong places...

Same mixed order also present in "clock table", thats why clock timing of CDP/DPCL is not match with Doomed gpu.txt


Need to investigate on real hardware.

EDIT: Investigated. **Pops is buggy shit.**