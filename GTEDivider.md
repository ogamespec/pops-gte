# Introduction #

```
If a program contains too much division, the programmer's an idiot
```
(c) Professor.

GTE has integrated divider, based on Unsigned Newton-Raphson (UNR) algorithm. If you're smart enough, you can read this m$ paper: <br>
<a href='http://research.microsoft.com/apps/pubs/default.aspx?id=70645'>Software Integer Division</a><br>
I didn't managed to understand it :=)<br>
<br>
It seems GTE also has hardwired 256-entry UNR table on chip:<br>

<table><thead><th>FF </th><th>FD </th><th>FB </th><th>F9 </th><th>F7 </th><th>F5 </th><th>F3 </th><th>F1 </th><th>EF </th><th>EE </th><th>EC </th><th>EA </th><th>E8 </th><th>E6 </th><th>E4 </th><th>E3</th></thead><tbody>
<tr><td>E1 </td><td>DF </td><td>DD </td><td>DC </td><td>DA </td><td>D8 </td><td>D6 </td><td>D5 </td><td>D3 </td><td>D1 </td><td>D0 </td><td>CE </td><td>CD </td><td>CB </td><td>C9 </td><td>C8</td></tr>
<tr><td>C6 </td><td>C5 </td><td>C3 </td><td>C1 </td><td>C0 </td><td>BE </td><td>BD </td><td>BB </td><td>BA </td><td>B8 </td><td>B7 </td><td>B5 </td><td>B4 </td><td>B2 </td><td>B1 </td><td>B0</td></tr>
<tr><td>AE </td><td>AD </td><td>AB </td><td>AA </td><td>A9 </td><td>A7 </td><td>A6 </td><td>A4 </td><td>A3 </td><td>A2 </td><td>A0 </td><td>9F </td><td>9E </td><td>9C </td><td>9B </td><td>9A</td></tr>
<tr><td>99 </td><td>97 </td><td>96 </td><td>95 </td><td>94 </td><td>92 </td><td>91 </td><td>90 </td><td>8F </td><td>8D </td><td>8C </td><td>8B </td><td>8A </td><td>89 </td><td>87 </td><td>86</td></tr>
<tr><td>85 </td><td>84 </td><td>83 </td><td>82 </td><td>81 </td><td>7F </td><td>7E </td><td>7D </td><td>7C </td><td>7B </td><td>7A </td><td>79 </td><td>78 </td><td>77 </td><td>75 </td><td>74</td></tr>
<tr><td>73 </td><td>72 </td><td>71 </td><td>70 </td><td>6F </td><td>6E </td><td>6D </td><td>6C </td><td>6B </td><td>6A </td><td>69 </td><td>68 </td><td>67 </td><td>66 </td><td>65 </td><td>64</td></tr>
<tr><td>63 </td><td>62 </td><td>61 </td><td>60 </td><td>5F </td><td>5E </td><td>5D </td><td>5D </td><td>5C </td><td>5B </td><td>5A </td><td>59 </td><td>58 </td><td>57 </td><td>56 </td><td>55</td></tr>
<tr><td>54 </td><td>53 </td><td>53 </td><td>52 </td><td>51 </td><td>50 </td><td>4F </td><td>4E </td><td>4D </td><td>4D </td><td>4C </td><td>4B </td><td>4A </td><td>49 </td><td>48 </td><td>48</td></tr>
<tr><td>47 </td><td>46 </td><td>45 </td><td>44 </td><td>43 </td><td>43 </td><td>42 </td><td>41 </td><td>40 </td><td>3F </td><td>3F </td><td>3E </td><td>3D </td><td>3C </td><td>3C </td><td>3B</td></tr>
<tr><td>3A </td><td>39 </td><td>39 </td><td>38 </td><td>37 </td><td>36 </td><td>36 </td><td>35 </td><td>34 </td><td>33 </td><td>33 </td><td>32 </td><td>31 </td><td>31 </td><td>30 </td><td>2F</td></tr>
<tr><td>2E </td><td>2E </td><td>2D </td><td>2C </td><td>2C </td><td>2B </td><td>2A </td><td>2A </td><td>29 </td><td>28 </td><td>28 </td><td>27 </td><td>26 </td><td>26 </td><td>25 </td><td>24</td></tr>
<tr><td>24 </td><td>23 </td><td>22 </td><td>22 </td><td>21 </td><td>20 </td><td>20 </td><td>1F </td><td>1E </td><td>1E </td><td>1D </td><td>1D </td><td>1C </td><td>1B </td><td>1B </td><td>1A</td></tr>
<tr><td>19 </td><td>19 </td><td>18 </td><td>18 </td><td>17 </td><td>16 </td><td>16 </td><td>15 </td><td>15 </td><td>14 </td><td>14 </td><td>13 </td><td>12 </td><td>12 </td><td>11 </td><td>11</td></tr>
<tr><td>10 </td><td>0F </td><td>0F </td><td>0E </td><td>0E </td><td>0D </td><td>0D </td><td>0C </td><td>0C </td><td>0B </td><td>0A </td><td>0A </td><td>09 </td><td>09 </td><td>08 </td><td>08</td></tr>
<tr><td>07 </td><td>07 </td><td>06 </td><td>06 </td><td>05 </td><td>05 </td><td>04 </td><td>04 </td><td>03 </td><td>03 </td><td>02 </td><td>02 </td><td>01 </td><td>01 </td><td>00 </td><td>00</td></tr></tbody></table>

(which is somewhat similar to <code>unrt[]</code> table from manual)<br>
<br>
During calculations those entries are extended to 32-bit 16.16 integers on the fly by GTE, but Pops additionally generates 0x8000 16.16 reciprocals table, to speedup calculations.<br>
<br>
<h1>Details</h1>

Source code of GTE divider on C:<br>
<br>
<pre><code><br>
// UNR table.<br>
// Must be hardwired somewhere in CPU chip.<br>
// If someone wish to decap PSX CPU I have bunch of them, contact me ogamespec@gmail.com, I'll send it free.<br>
static u8 unrt[] = {<br>
    0xFF, 0xFD, 0xFB, 0xF9, 0xF7, 0xF5, 0xF3, 0xF1, 0xEF, 0xEE, 0xEC, 0xEA, 0xE8, 0xE6, 0xE4, 0xE3,<br>
    0xE1, 0xDF, 0xDD, 0xDC, 0xDA, 0xD8, 0xD6, 0xD5, 0xD3, 0xD1, 0xD0, 0xCE, 0xCD, 0xCB, 0xC9, 0xC8,<br>
    0xC6, 0xC5, 0xC3, 0xC1, 0xC0, 0xBE, 0xBD, 0xBB, 0xBA, 0xB8, 0xB7, 0xB5, 0xB4, 0xB2, 0xB1, 0xB0,<br>
    0xAE, 0xAD, 0xAB, 0xAA, 0xA9, 0xA7, 0xA6, 0xA4, 0xA3, 0xA2, 0xA0, 0x9F, 0x9E, 0x9C, 0x9B, 0x9A,<br>
    0x99, 0x97, 0x96, 0x95, 0x94, 0x92, 0x91, 0x90, 0x8F, 0x8D, 0x8C, 0x8B, 0x8A, 0x89, 0x87, 0x86,<br>
    0x85, 0x84, 0x83, 0x82, 0x81, 0x7F, 0x7E, 0x7D, 0x7C, 0x7B, 0x7A, 0x79, 0x78, 0x77, 0x75, 0x74,<br>
    0x73, 0x72, 0x71, 0x70, 0x6F, 0x6E, 0x6D, 0x6C, 0x6B, 0x6A, 0x69, 0x68, 0x67, 0x66, 0x65, 0x64,<br>
    0x63, 0x62, 0x61, 0x60, 0x5F, 0x5E, 0x5D, 0x5D, 0x5C, 0x5B, 0x5A, 0x59, 0x58, 0x57, 0x56, 0x55,<br>
    0x54, 0x53, 0x53, 0x52, 0x51, 0x50, 0x4F, 0x4E, 0x4D, 0x4D, 0x4C, 0x4B, 0x4A, 0x49, 0x48, 0x48,<br>
    0x47, 0x46, 0x45, 0x44, 0x43, 0x43, 0x42, 0x41, 0x40, 0x3F, 0x3F, 0x3E, 0x3D, 0x3C, 0x3C, 0x3B,<br>
    0x3A, 0x39, 0x39, 0x38, 0x37, 0x36, 0x36, 0x35, 0x34, 0x33, 0x33, 0x32, 0x31, 0x31, 0x30, 0x2F,<br>
    0x2E, 0x2E, 0x2D, 0x2C, 0x2C, 0x2B, 0x2A, 0x2A, 0x29, 0x28, 0x28, 0x27, 0x26, 0x26, 0x25, 0x24,<br>
    0x24, 0x23, 0x22, 0x22, 0x21, 0x20, 0x20, 0x1F, 0x1E, 0x1E, 0x1D, 0x1D, 0x1C, 0x1B, 0x1B, 0x1A,<br>
    0x19, 0x19, 0x18, 0x18, 0x17, 0x16, 0x16, 0x15, 0x15, 0x14, 0x14, 0x13, 0x12, 0x12, 0x11, 0x11,<br>
    0x10, 0x0F, 0x0F, 0x0E, 0x0E, 0x0D, 0x0D, 0x0C, 0x0C, 0x0B, 0x0A, 0x0A, 0x09, 0x09, 0x08, 0x08,<br>
    0x07, 0x07, 0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03, 0x02, 0x02, 0x01, 0x01, 0x00, 0x00,<br>
};<br>
<br>
// Count leading zeros.<br>
// I know, there is more complicated algo, but meh... I'm lazy<br>
static inline int CLZ (u16 rs)<br>
{<br>
    u32 n, m;<br>
    for(n=0, m=1&lt;&lt;15; n&lt;16; n++, m&gt;&gt;=1)<br>
    {<br>
        if (rs &amp; m) break;<br>
    }<br>
    return 16 + n;<br>
}<br>
<br>
// inputs are 0.16.0, returns 0.16.16 fixed-point<br>
static inline u32 DIVIDE(u16 n, u16 d) {<br>
    if (n &lt; d * 2) {    <br>
        int zeros = CLZ ( d ) - 14;<br>
        u32 a3 = (d &lt;&lt; zeros) &gt;&gt; 2;<br>
        s32 t6 = unrt[(( a3 + 64) &gt;&gt; 7) - 256] + 257;<br>
        s32 t8 = 128 - t6 * a3;<br>
        s32 t7 = (t8 &gt;&gt; 8) &amp; 0x1FFFF;<br>
        s32 t4 = t7 * t6 + 128;<br>
        s32 t3 = t4 &gt;&gt; 8;<br>
        u32 reciprocal = t3 &lt;&lt; 14;<br>
        u64 res = 0x80000000 + (u64)(n &lt;&lt; zeros) * (u64)(reciprocal);<br>
        return res &gt;&gt; 32;<br>
    }<br>
<br>
    return 0xffffffff;<br>
}<br>
<br>
</code></pre>