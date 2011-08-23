#include <sys/types.h>
#include "gte2.h"

void GTEWriteData (int id, u_long value)
{
    switch (id)
    {
        case 0: GTEWriteData0 (value); break;
        case 1: GTEWriteData1 (value); break;
        case 2: GTEWriteData2 (value); break;
        case 3: GTEWriteData3 (value); break;
        case 4: GTEWriteData4 (value); break;
        case 5: GTEWriteData5 (value); break;
        case 6: GTEWriteData6 (value); break;
        case 7: GTEWriteData7 (value); break;
        case 8: GTEWriteData8 (value); break;
        case 9: GTEWriteData9 (value); break;
        case 10: GTEWriteData10 (value); break;
        case 11: GTEWriteData11 (value); break;
        case 12: GTEWriteData12 (value); break;
        case 13: GTEWriteData13 (value); break;
        case 14: GTEWriteData14 (value); break;
        case 15: GTEWriteData15 (value); break;
        case 16: GTEWriteData16 (value); break;
        case 17: GTEWriteData17 (value); break;
        case 18: GTEWriteData18 (value); break;
        case 19: GTEWriteData19 (value); break;
        case 20: GTEWriteData20 (value); break;
        case 21: GTEWriteData21 (value); break;
        case 22: GTEWriteData22 (value); break;
        case 23: GTEWriteData23 (value); break;
        case 24: GTEWriteData24 (value); break;
        case 25: GTEWriteData25 (value); break;
        case 26: GTEWriteData26 (value); break;
        case 27: GTEWriteData27 (value); break;
        case 28: GTEWriteData28 (value); break;
        case 29: GTEWriteData29 (value); break;
        case 30: GTEWriteData30 (value); break;
        case 31: GTEWriteData31 (value); break;
    }
}

u_long GTEReadData (int id)
{
    switch (id)
    {
        case 0: return GTEReadData0 ();
        case 1: return GTEReadData1 ();
        case 2: return GTEReadData2 ();
        case 3: return GTEReadData3 ();
        case 4: return GTEReadData4 ();
        case 5: return GTEReadData5 ();
        case 6: return GTEReadData6 ();
        case 7: return GTEReadData7 ();
        case 8: return GTEReadData8 ();
        case 9: return GTEReadData9 ();
        case 10: return GTEReadData10 ();
        case 11: return GTEReadData11 ();
        case 12: return GTEReadData12 ();
        case 13: return GTEReadData13 ();
        case 14: return GTEReadData14 ();
        case 15: return GTEReadData15 ();
        case 16: return GTEReadData16 ();
        case 17: return GTEReadData17 ();
        case 18: return GTEReadData18 ();
        case 19: return GTEReadData19 ();
        case 20: return GTEReadData20 ();
        case 21: return GTEReadData21 ();
        case 22: return GTEReadData22 ();
        case 23: return GTEReadData23 ();
        case 24: return GTEReadData24 ();
        case 25: return GTEReadData25 ();
        case 26: return GTEReadData26 ();
        case 27: return GTEReadData27 ();
        case 28: return GTEReadData28 ();
        case 29: return GTEReadData29 ();
        case 30: return GTEReadData30 ();
        case 31: return GTEReadData31 ();
    }
}

void GTEWriteCtrl (int id, u_long value)
{
    switch (id)
    {
        case 0: GTEWriteCtrl0 (value); break;
        case 1: GTEWriteCtrl1 (value); break;
        case 2: GTEWriteCtrl2 (value); break;
        case 3: GTEWriteCtrl3 (value); break;
        case 4: GTEWriteCtrl4 (value); break;
        case 5: GTEWriteCtrl5 (value); break;
        case 6: GTEWriteCtrl6 (value); break;
        case 7: GTEWriteCtrl7 (value); break;
        case 8: GTEWriteCtrl8 (value); break;
        case 9: GTEWriteCtrl9 (value); break;
        case 10: GTEWriteCtrl10 (value); break;
        case 11: GTEWriteCtrl11 (value); break;
        case 12: GTEWriteCtrl12 (value); break;
        case 13: GTEWriteCtrl13 (value); break;
        case 14: GTEWriteCtrl14 (value); break;
        case 15: GTEWriteCtrl15 (value); break;
        case 16: GTEWriteCtrl16 (value); break;
        case 17: GTEWriteCtrl17 (value); break;
        case 18: GTEWriteCtrl18 (value); break;
        case 19: GTEWriteCtrl19 (value); break;
        case 20: GTEWriteCtrl20 (value); break;
        case 21: GTEWriteCtrl21 (value); break;
        case 22: GTEWriteCtrl22 (value); break;
        case 23: GTEWriteCtrl23 (value); break;
        case 24: GTEWriteCtrl24 (value); break;
        case 25: GTEWriteCtrl25 (value); break;
        case 26: GTEWriteCtrl26 (value); break;
        case 27: GTEWriteCtrl27 (value); break;
        case 28: GTEWriteCtrl28 (value); break;
        case 29: GTEWriteCtrl29 (value); break;
        case 30: GTEWriteCtrl30 (value); break;
        case 31: GTEWriteCtrl31 (value); break;
    }
}

u_long GTEReadCtrl (int id)
{
    switch (id)
    {
        case 0: return GTEReadCtrl0 ();
        case 1: return GTEReadCtrl1 ();
        case 2: return GTEReadCtrl2 ();
        case 3: return GTEReadCtrl3 ();
        case 4: return GTEReadCtrl4 ();
        case 5: return GTEReadCtrl5 ();
        case 6: return GTEReadCtrl6 ();
        case 7: return GTEReadCtrl7 ();
        case 8: return GTEReadCtrl8 ();
        case 9: return GTEReadCtrl9 ();
        case 10: return GTEReadCtrl10 ();
        case 11: return GTEReadCtrl11 ();
        case 12: return GTEReadCtrl12 ();
        case 13: return GTEReadCtrl13 ();
        case 14: return GTEReadCtrl14 ();
        case 15: return GTEReadCtrl15 ();
        case 16: return GTEReadCtrl16 ();
        case 17: return GTEReadCtrl17 ();
        case 18: return GTEReadCtrl18 ();
        case 19: return GTEReadCtrl19 ();
        case 20: return GTEReadCtrl20 ();
        case 21: return GTEReadCtrl21 ();
        case 22: return GTEReadCtrl22 ();
        case 23: return GTEReadCtrl23 ();
        case 24: return GTEReadCtrl24 ();
        case 25: return GTEReadCtrl25 ();
        case 26: return GTEReadCtrl26 ();
        case 27: return GTEReadCtrl27 ();
        case 28: return GTEReadCtrl28 ();
        case 29: return GTEReadCtrl29 ();
        case 30: return GTEReadCtrl30 ();
        case 31: return GTEReadCtrl31 ();
    }
}
