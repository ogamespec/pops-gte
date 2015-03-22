# Introduction #

PSP has custom CPU named Allegrex. It has additional MIPS instructions + VFPU (vector FPU) coprocessor.

On this page you can find quick description of these weird instructions, which can be found in disassembly.

# MIPS Extension #

## Extract bits ##
ext rd, rs, p, s: Extract **s** bits from **rs** from position **p** and put into **rd**<br>
Example:<br>
<pre><code>rs = 0x11223344<br>
ext   rd, rs, 8, 8<br>
rd = 0x33<br>
</code></pre>

<h2>Insert bits</h2>
ins rd, rs, p, s: Insert first <b>s</b> bits of <b>rs</b> into <b>rd</b>, from position <b>p</b><br>
Example:<br>
<pre><code>rs = 0xAA<br>
rd = 0x11223344<br>
ins   rd, rs, 16, 8<br>
rd = 0x11AA3344<br>
</code></pre>

Widely used for RGB calculations.<br>
<br>
<h2>Conditional Move</h2>

movn rd, rs, rt: if (rt != 0) rd = rs<br>
movz rd, rs, rt: if (rt == 0) rd = rs<br>

<h2>Advanced Multiply</h2>

madd rs, rt: Acc += rs <code>*</code> rt<br>
msub rs, rt: Acc -= rs <code>*</code> rt<br>
maddu rs, rt: Acc += (unsigned)rs <code>*</code> (unsigned)rt<br>
msubu rs, rt: Acc -= (unsigned)rs <code>*</code> (unsigned)rt<br>

<h2>Count leading bits</h2>

clo rd: rs: rd = Count leading ones of rs<br>
clz rd: rs: rd = Count leading zeros of rs<br>

Based on nice pdf: <a href='http://www.mips.com/media/files/MD00565-2B-MIPS32-QRC-01.01.pdf'>MIPS32 Quick Reference</a>

<h1>MIPS Delay Slot Instructions</h1>

On the MIPS architecture, jump and branch instructions have a "delay slot". This means that the instruction after the jump or branch instruction is executed before the jump or branch is executed.<br>
<br>
In addition, there is a group of "branch likely" conditional branch instructions in which the instruction in the delay slot is executed only if the branch is taken.<br>
<br>
<b>!</b> So please remember, that <b>BEQ</b> is not the same as <b>BEQL</b>: BEQ delay slot is always executed, but BEQL delay slot executed only if branch taken. This may ruin whole disassembly logic.<br>
<br>
Borrowed here: <a href='http://public.lanl.gov/totalview/online-4.1.0-4/user_guide/appc28.html'>http://public.lanl.gov/totalview/online-4.1.0-4/user_guide/appc28.html</a>

<h1>Small note on VFPU disassembly</h1>

When I write:<br>
<pre><code>[x] [y] [z] [w]<br>
</code></pre>
this mean single VFPU quad vector<br>
<br>
When I write:<br>
<pre><code>block number:<br>
   [0] [1] [2] [3]<br>
   [4] [5] [6] [7]<br>
   [8] [9] [A] [B]<br>
   [C] [D] [E] [F]<br>
</code></pre>
this mean contents of whole VFPU 'block'<br>
<br>
It is very convenient to represent VFPU disassembly by steps, as content of its registers, for example:<br>
<br>
<pre><code>2:<br>
        [L11L12] [L33] [VXY0] []<br>
        [L13L21] [RBK] [VZ0]  []<br>
        [L22L23] [GBK] [VXY1] []<br>
        [L31L32] [BBK] [VZ1]  []<br>
<br>
        0x0000DCB0: 0xDB8800A0 '....' - lv.q       C200, 160($gp)       // L11L12<br>
        0x0000DCB4: 0xDB8900B0 '....' - lv.q       C210, 176($gp)       // L33<br>
        0x0000DCB8: 0xDB8A0000 '....' - lv.q       C220, 0($gp)<br>
</code></pre>

This writings represent final result of block #2 after three subsequent lv.q instructions.<br>
<br>
For more details on VFPU registers look here: <a href='http://wiki.fx-world.org/doku.php?id=general:vfpu_registers'>VFPU Register Mapping</a>

<img src='http://ogamespec.com/imgstore/whc4e200167b0e4e.jpg'>

When I write:<br>
<pre><code>[F 10] [F 20] [F 40] [F 80]<br>
</code></pre>
this mean VFPU registers contain <b>floats</b>

When I write:<br>
<pre><code>[I 10] [I 20] [I 40] [I 80]<br>
</code></pre>
this mean VFPU registers contain <b>integers</b>

If I/F of register is not specified, it supposed to be <b>integer</b>

<h1>VFPU Load/Store with 'shuffle'</h1>

<h2>lvl.q: Load Quad Word Left to VFPU</h2>

<table><thead><th>offset % 16</th><th>address & ~0xf</th><th>vfpu</th></thead><tbody>
<tr><td>+0</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[-]</code> <code>[-]</code> <code>[-]</code> <code>[1]</code></td></tr>
<tr><td>+4</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[-]</code> <code>[-]</code> <code>[1]</code> <code>[2]</code></td></tr>
<tr><td>+8</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[-]</code> <code>[1]</code> <code>[2]</code> <code>[3]</code></td></tr>
<tr><td>+12</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td></tr></tbody></table>

<code>[-]</code> mean keep unchanged<br>
<br>
<h2>lvr.q: Load Quad Word Right to VFPU</h2>

<table><thead><th>offset % 16</th><th>address & ~0xf</th><th>vfpu</th></thead><tbody>
<tr><td>+0</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td></tr>
<tr><td>+4</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[2]</code> <code>[3]</code> <code>[4]</code> <code>[-]</code></td></tr>
<tr><td>+8</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[3]</code> <code>[4]</code> <code>[-]</code> <code>[-]</code></td></tr>
<tr><td>+12</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[4]</code> <code>[-]</code> <code>[-]</code> <code>[-]</code></td></tr></tbody></table>

<code>[-]</code> mean keep unchanged<br>
<br>
<h2>svl.q: Store Quad Word Left from VFPU</h2>

<table><thead><th>offset % 16</th><th>vfpu</th><th>address & ~0xf</th></thead><tbody>
<tr><td>+0</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[4]</code> <code>[-]</code> <code>[-]</code> <code>[-]</code></td></tr>
<tr><td>+4</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[3]</code> <code>[4]</code> <code>[-]</code> <code>[-]</code></td></tr>
<tr><td>+8</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[2]</code> <code>[3]</code> <code>[4]</code> <code>[-]</code></td></tr>
<tr><td>+12</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td></tr></tbody></table>

<code>[-]</code> mean keep unchanged<br>
<br>
<h2>svr.q: Store Quad Word Right from VFPU</h2>

<table><thead><th>offset % 16</th><th>vfpu</th><th>address & ~0xf</th></thead><tbody>
<tr><td>+0</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td></tr>
<tr><td>+4</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[-]</code> <code>[1]</code> <code>[2]</code> <code>[3]</code></td></tr>
<tr><td>+8</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[-]</code> <code>[-]</code> <code>[1]</code> <code>[2]</code></td></tr>
<tr><td>+12</td><td><code>[1]</code> <code>[2]</code> <code>[3]</code> <code>[4]</code></td><td><code>[-]</code> <code>[-]</code> <code>[-]</code> <code>[1]</code></td></tr></tbody></table>

<code>[-]</code> mean keep unchanged<br>
<br>
Example of use:<br>
Some piece of GTE calculations require to "push" FIFO registers:<br>
<pre><code>RGB0 = RGB1<br>
RGB1 = RGB2<br>
RGB2 = RGB<br>
</code></pre>

So we do:<br>
<pre><code>lv.q      C000, &amp;gteData[20]<br>
.... do some calculations of RGB value, so C000 would be:<br>
[RGB0] [RGB1] [RGB2] [RGB]<br>
svl.q     C000, &amp;gteData[22]<br>
It writes to memory:<br>
[RGB0] [RGB1] [RGB2] [RES1] &lt;= [RGB1] [RGB2] [RGB] [unchanged]<br>
</code></pre>

<h1>VFPU Simple</h1>

<table><thead><th> <b>instruction</b> </th><th> <b>description</b> </th><th> <b>operation</b> </th></thead><tbody>
<tr><td>vi2f.s</td><td> Convert integer to float with Scaling Single Word</td><td> <code>[d0]</code> <= float (<code>[s0]</code>) / (1 << imm) </td></tr>
<tr><td>vi2f.p</td><td> Convert integer to float with Scaling Pair Word</td><td> same for pair </td></tr>
<tr><td>vi2f.t</td><td> Convert integer to float with Scaling Triple Word</td><td> same for triple </td></tr>
<tr><td>vi2f.q</td><td> Convert integer to float with Scaling Quad Word</td><td> same for quad </td></tr>
<tr><td>vmax.s</td><td> Maximum Single Word</td><td> <code>[d0]</code> <= max(<code>[s0]</code>,<code>[t0]</code>) </td></tr>
<tr><td>vmax.p</td><td> Maximum Pair Word</td><td> same for pair </td></tr>
<tr><td>vmax.t</td><td> Maximum Triple Word</td><td> same for triple </td></tr>
<tr><td>vmax.q</td><td> Maximum Quad Word</td><td> same for quad</td></tr>
<tr><td>vmin.s</td><td> Minimum Single Word</td><td> <code>[d0]</code> <= min(<code>[s0]</code>,<code>[t0]</code>) </td></tr>
<tr><td>vmin.p</td><td> Minimum Pair Word</td><td> same for pair</td></tr>
<tr><td>vmin.t</td><td> Minimum Triple Word</td><td> same for triple </td></tr>
<tr><td>vmin.q</td><td> Minimum Quad Word</td><td> same for quad </td></tr>
<tr><td>vmov.s</td><td> Move Single Word</td><td> <code>[d0]</code> <= <code>[s0]</code> </td></tr>
<tr><td>vmov.p</td><td> Move Pair Word</td><td> <code>[d0]</code> <code>[d1]</code> <= <code>[s0]</code> <code>[s1]</code></td></tr>
<tr><td>vmov.t</td><td> Move Triple Word</td><td> <code>[d0]</code> <code>[d1]</code> <code>[d2]</code> <= <code>[s0]</code> <code>[s1]</code> <code>[s2]</code></td></tr>
<tr><td>vmov.q</td><td> Move Quad Word</td><td> <code>[d0]</code> <code>[d1]</code> <code>[d2]</code> <code>[d3]</code> <= <code>[s0]</code> <code>[s1]</code> <code>[s2]</code> <code>[s3]</code></td></tr>
<tr><td>vzero.s</td><td> Set Zero Single Word</td><td> <code>[d0]</code> <= 0 </td></tr>
<tr><td>vzero.p</td><td> Set Zero Pair Word</td><td> <code>[d0]</code> <code>[d1]</code> <= 0 0</td></tr>
<tr><td>vzero.t</td><td> Set Zero Triple Word</td><td> <code>[d0]</code> <code>[d1]</code> <code>[d2]</code> <= 0 0 0</td></tr>
<tr><td>vzero.q</td><td> Set Zero Quad Word</td><td> <code>[d0]</code> <code>[d1]</code> <code>[d2]</code> <code>[d3]</code> <= 0 0 0 0</td></tr></tbody></table>

<h1>VFPU Not Simple :)</h1>

<h2>vs2i.p: Convert signed short to integer Pair Word</h2>

Four packed signed shorts converted to four unpacked longs.<br>
<br>
Example:<br>
<pre><code> Source: [0xAABBCCDD] [0x11223344] [-] [-]<br>
 Dest: [0xCCDD0000] [0xAABB0000] [0x33440000] [0x11220000]<br>
</code></pre>

<b>!</b> <i>Dont forget to shift >> 16 all result values before use</i>

Used to unpack GTE registers, such as:<br>
<pre><code> 8  L11L12  |L12 1, 3,12|L11 1, 3,12| Light source matrix elements 11, 12<br>
 9  L13L21  |L21 1, 3,12|L13 1, 3,12| Light source matrix elements 13, 21<br>
10  L22L23  |L23 1, 3,12|L22 1, 3,12| Light source matrix elements 22, 23<br>
11  L31L32  |L32 1, 3,12|L31 1, 3,12| Light source matrix elements 31, 32<br>
</code></pre>

<h1>VFPU Prefix Instructions</h1>

VFPU has three prefix instructions: vpfxd, vpfxs and vpfxt which is applied to rd (destination), rs (source) and rt (target) operands of the <b>next</b> instruction.<br>
<br>
You can shuffle or discard some of operands, by applying prefix on it. For example:<br>
<pre><code>vpfxt   [x, y, 0, 0]<br>
vadd.q  rd, rs, rt<br>
<br>
rt will be [x, y, 0, 0] before vadd.<br>
</code></pre>

Prefix table codes for source and target:<br>
<table><thead><th> <b>code</b> </th><th> <b>take</b> </th></thead><tbody>
<tr><td>x </td><td>v<code>[0]</code></td></tr>
<tr><td>y </td><td>v<code>[1]</code></td></tr>
<tr><td>z </td><td>v<code>[2]</code></td></tr>
<tr><td>w </td><td>v<code>[3]</code></td></tr>
<tr><td>-x</td><td>-v<code>[0]</code></td></tr>
<tr><td>-y</td><td>-v<code>[1]</code></td></tr>
<tr><td>-z</td><td>-v<code>[2]</code></td></tr>
<tr><td>-w</td><td>-v<code>[3]</code></td></tr>
<tr><td><code>|x|</code></td><td>abs(v<code>[0]</code>)</td></tr>
<tr><td><code>|y|</code></td><td>abs(v<code>[1]</code>)</td></tr>
<tr><td><code>|z|</code></td><td>abs(v<code>[2]</code>)</td></tr>
<tr><td><code>|w|</code></td><td>abs(v<code>[3]</code>)</td></tr>
<tr><td>-<code>|x|</code></td><td>-abs(v<code>[0]</code>)</td></tr>
<tr><td>-<code>|y|</code></td><td>-abs(v<code>[1]</code>)</td></tr>
<tr><td>-<code>|z|</code></td><td>-abs(v<code>[2]</code>)</td></tr>
<tr><td>-<code>|w|</code></td><td>-abs(v<code>[3]</code>)</td></tr>
<tr><td>0 </td><td>0 </td></tr>
<tr><td>1 </td><td>1 </td></tr>
<tr><td>2 </td><td>2 </td></tr>
<tr><td>3 </td><td>3 </td></tr>
<tr><td>1/2</td><td>1/2</td></tr>
<tr><td>1/3</td><td>1/3</td></tr>
<tr><td>1/4</td><td>1/4</td></tr>
<tr><td>1/6</td><td>1/6</td></tr></tbody></table>

Prefix table codes for destination:<br>
<table><thead><th> <b>code</b> </th><th> <b>result</b> </th></thead><tbody>
<tr><td><code> </code></td><td>pass through</td></tr>
<tr><td>m </td><td>ignore</td></tr>
<tr><td>0:1</td><td>clamp value to <code>[0.0; 1.0]</code></td></tr>
<tr><td>-1:1</td><td>clamp value to <code>[-1.0; 1.0]</code></td></tr></tbody></table>

<h1>prxtool Bugs</h1>

<h2>Bug in msub decoding</h2>

All msub instructions use $zr instead proper RS register, for example:<br>
<br>
<pre><code>   0x0000E5B8: 0x00C1002E '....' - msub       $zr, $at<br>
</code></pre>

Should be:<br>
<br>
<pre><code>   0x0000E5B8: 0x00C1002E '....' - msub       $a2, $at<br>
</code></pre>

<h2>Bug in vi2uc.q decoding</h2>

<pre><code>0x0000D420: 0xD03C83FE '..&lt;.' - vi2uc.q    R702, C030<br>
</code></pre>

Destination is always single register. Following instruction should be decoded as follow:<br>
<br>
<pre><code>0x0000D420: 0xD03C83FE '..&lt;.' - vi2uc.q    S723, C030<br>
</code></pre>