# GTE Commands Reference #

## Limiters ##

During some calculation processing, calculation results, data values in registers, etc., are clipped when they
exceed specified upper limit and lower limit values. In other words, data values lower than the lower limit
value are converted to the lower limit value, and data values higher than the upper limit value are converted
to the upper limit value. Also, the occurrence of such conversions is reflected in out-of-bounds data
detection flags in the FLAG register. These functions are referred to as "limiters”.

The usage of the various limiters and the codes used to specify them in this documentation are listed
below.

|Code<br>Specific<br>ation<table><thead><th>Limiter</th><th>Out-of-<br>bounds<br>detect bit</th><th>Lower limit</th><th>Upper limit</th><th>Comments</th></thead><tbody>
<tr><td> <b>A1S</b> </td><td> <b>A1</b> </td><td> <b>24</b> </td><td> <b>-2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td><td>  </td></tr>
<tr><td> <b>A2S</b> </td><td> <b>A2</b> </td><td> <b>23</b> </td><td> <b>-2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td><td>  </td></tr>
<tr><td> <b>A3S</b> </td><td> <b>A3</b> </td><td> <b>22</b> </td><td> <b>-2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td><td>  </td></tr>
<tr><td> <b>A1U</b> </td><td> <b>A1</b> </td><td> <b>24</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>15-1</b> </td><td>  </td></tr>
<tr><td> <b>A2U</b> </td><td> <b>A2</b> </td><td> <b>23</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>15-1</b> </td><td>  </td></tr>
<tr><td> <b>A3U</b> </td><td> <b>A3</b> </td><td> <b>22</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>15-1</b> </td><td>  </td></tr>
<tr><td> <b>A1C</b> </td><td> <b>A1</b> </td><td> <b>24</b> </td><td> <b>0 or -2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td><td> Lower limit value is<br> specified using lim <br>argument.</td></tr>
<tr><td> <b>A2C</b> </td><td> <b>A3</b> </td><td> <b>23</b> </td><td> <b>0 or -2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td><td> Lower limit value <br>is specified using lim <br>argument.</td></tr>
<tr><td> <b>A3C</b> </td><td> <b>A3</b> </td><td> <b>22</b> </td><td> <b>0 or -2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td><td> Lower limit value <br>is specified using lim <br>argument.</td></tr>
<tr><td> <b>B1</b> </td><td> <b>B1</b> </td><td> <b>21</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>8-1</b> </td><td>  </td></tr>
<tr><td> <b>B2</b> </td><td> <b>B2</b> </td><td> <b>20</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>8-1</b> </td><td>  </td></tr>
<tr><td> <b>B3</b> </td><td> <b>B3</b> </td><td> <b>19</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>8-1</b> </td><td>  </td></tr>
<tr><td> <b>C</b> </td><td> <b>C</b> </td><td> <b>18</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>16-1</b> </td><td>  </td></tr>
<tr><td> <b>D1</b> </td><td> <b>D1</b> </td><td> <b>14</b> </td><td> <b>-2<code>^</code>10</b> </td><td> <b>2<code>^</code>10-1</b> </td><td>  </td></tr>
<tr><td> <b>D2</b> </td><td> <b>D2</b> </td><td> <b>13</b> </td><td> <b>-2<code>^</code>10</b> </td><td> <b>2<code>^</code>10-1</b> </td><td>  </td></tr>
<tr><td> <b>E</b> </td><td> <b>E</b> </td><td> <b>12</b> </td><td> <b>0</b> </td><td> <b>2<code>^</code>12-1</b> </td><td>  </td></tr></tbody></table>

<h2>Calculation Error Detection</h2>

Overflow and underflow detection are performed only for certain specific calculation operations. In this<br>
documentation, the calculation test result flag number is listed between angle brackets < > to the right of<br>
calculation operations that are subject to such detection.<br>
<br>
<h2>Explanations</h2>

<table><thead><th>Character attributes </th><th>Example </th><th>Content</th></thead><tbody>
<tr><td>Underline </td><td> <u><b>VAL</b></u> </td><td>Intermediate value<br>(No corresponding register)</td></tr>
<tr><td>Embolden </td><td> <b>OBJ</b> </td><td> 32-bit value</td></tr></tbody></table>

<table><thead><th>Code </th><th>Meaning</th></thead><tbody>
<tr><td> <b>limX()</b> </td><td>Limiter application X is the limiter designation code.</td></tr>
<tr><td> <b><-</b> </td><td> FIFO data transfer<br>Example: a <- b <- c <- d; is equivalent to the following:<br>a = b;<br>b = c;<br>c = d;<br></td></tr>
<tr><td> <b><code>^</code></b> </td><td> Power<br>Example: a<code>^</code>b means "a to the power of b". </td></tr>
<tr><td> <b>==</b> </td><td> Argument value condition </td></tr>
<tr><td> <b>n=0,1,2 {}</b> </td><td> Repeat the process between the curly parentheses {} three<br>times, substituting 0, 1, and 2 for n.</td></tr>
<tr><td> <b>(a.b.c)</b> </td><td> Fixed-point number<br>Sign portion: a bits, integer portion: b bits, fractional portion: c bits</td></tr>
<tr><td> <b>(-.b.-)</b> </td><td> b-bit binary data </td></tr>
<tr><td> <b><code>&lt;</code>n<code>&gt;</code></b> </td><td> Calculation subject to overflow and underflow testing<br>The test result is reflected in cumulative test flag n in the FLAG register.</td></tr></tbody></table>

<b>Descriptor examples:</b><br>
(A)<br>
(1.15.0) A = B;<br>
--> A=B is executed for the fixed-point expression (1.15.0).<br>
<br>
(B)<br>
(1.15.0) IR0 = limX(SSX);<br>
<br>
Limiter:<br>
<table><thead><th>Code </th><th>Lower limit </th><th>Upper limit</th></thead><tbody>
<tr><td> <b>limX</b> </td><td> <b>-2<code>^</code>15</b> </td><td> <b>2<code>^</code>15-1</b> </td></tr></tbody></table>

--> The 32-bit value SSX is rounded using the limiter specified by X. The fixed-point expression (1.15.0) representing the<br>
results obtained is substituted for IR1.<br>
<br>
(C)<br>
<pre><code>n=0,1,2{<br>
    (1.3.12)L1n<br>
        = limA(LL1n);<br>
}<br>
</code></pre>
--> For the fixed-point expression (1.3.12), the following are executed:<br>
L10=limA(LL10);<br>
L11=limA(LL11);<br>
L12=limA(LL12);<br>
<br>
(D)<br>
<pre><code>sf==0       sf==1<br>
(1.31.0)    (1.19.12)   A = B;<br>
</code></pre>
--> B is substituted for A. However, the value is converted into a 32-bit signed fixed-point number with no fractional part if sf<br>
is 0, and with a 12-bit fraction if sf is 1.<br>
<br>
<h2>Command List</h2>

<table><thead><th> Command </th><th> Required cycles </th><th> Function </th></thead><tbody>
<tr><td> <b>RTPS</b> </td><td> <b>14</b> </td><td> Coordinate transformation &<br>perspective transformation</td></tr>
<tr><td> <b>RTPT</b> </td><td> <b>22</b> </td><td> Coordinate transformation &<br>perspective transformation</td></tr>
<tr><td> <b>NCDS</b> </td><td> <b>19</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>NCDT</b> </td><td> <b>44</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>NCCS</b> </td><td> <b>17</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>NCCT</b> </td><td> <b>39</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>CDP</b> </td><td> <b>13</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>CC</b> </td><td> <b>11</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>NCS</b> </td><td> <b>14</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>NCT</b> </td><td> <b>30</b> </td><td> Light source calculation</td></tr>
<tr><td> <b>MVMVA</b> </td><td> <b>8</b> </td><td> Matrix calculation</td></tr>
<tr><td> <b>INTPL</b> </td><td> <b>8</b> </td><td> Interpolation</td></tr>
<tr><td> <b>DPCL</b> </td><td> <b>8</b> </td><td> Depth queuing</td></tr>
<tr><td> <b>DPCS</b> </td><td> <b>8</b> </td><td> Depth queuing</td></tr>
<tr><td> <b>DPCT</b> </td><td> <b>17</b> </td><td> Depth queuing</td></tr>
<tr><td> <b>SQR</b> </td><td> <b>5</b> </td><td> Vector squaring</td></tr>
<tr><td> <b>AVSZ3</b> </td><td> <b>5</b> </td><td> Z-averaging</td></tr>
<tr><td> <b>AVSZ4</b> </td><td> <b>6</b> </td><td> Z-averaging</td></tr>
<tr><td> <b>NCLIP</b> </td><td> <b>8</b> </td><td> Normal clipping</td></tr>
<tr><td> <b>OP</b> </td><td> <b>6</b> </td><td> Outer product</td></tr>
<tr><td> <b>GPF</b> </td><td> <b>5</b> </td><td> General purpose interpolation</td></tr>
<tr><td> <b>GPL</b> </td><td> <b>5</b> </td><td> General purpose interpolation</td></tr></tbody></table>

<h2>Command Details</h2>
Command details are listed on the pages which follow.<br>
<br>
<h2>RTPS Required cycles: 14</h2>

Function: Coordinate transformation and perspective transformation<br>
<br>
Calculations:<br>
<pre><code>(1.31.12) SSX = TRX + R11*VX0 + R12*VY0 + R13*VZ0; &lt;1&gt;<br>
(1.31.12) SSY = TRY + R21*VX0 + R22*VY0 + R23*VZ0; &lt;2&gt;<br>
(1.31.12) SSZ = TRZ + R31*VX0 + R32*VY0 + R33*VZ0; &lt;3&gt;<br>
(1.15. 0) IR1 = limA1S(SSX);<br>
(1.15. 0) IR2 = limA2S(SSY);<br>
(1.15. 0) IR3 = limA3S(SSZ);<br>
(0.16. 0) SZx(0) &lt;- SZ0(1) &lt;- SZ1(2) &lt;- SZ2(3) &lt;- limC(SSZ);<br>
(1.27.16) SX = OFX + IR1*(H/SZ); &lt;4&gt;<br>
(1.27.16) SY = OFY + IR2*(H/SZ); &lt;4&gt;<br>
(1.19.24) P = DQB + DQA*(H/SZ); &lt;4&gt;<br>
(1. 3.12) IR0 = limE(P)<br>
(1.15. 0) SX0 &lt;- SX1 &lt;- SX2 &lt;- limD1(SX);<br>
(1.15. 0) SY0 &lt;- SY1 &lt;- SY2 &lt;- limD2(SY);<br>
(1. 7.24) MAC0 = P;<br>
(1.31. 0) MAC1 = SSX;<br>
(1.31. 0) MAC2 = SSY;<br>
(1.31. 0) MAC3 = SSZ;<br>
</code></pre>

<h2>RTPT Required cycles: 22</h2>

Function: Coordinate transformation and perspective transformation<br>
<br>
Calculations:<br>
<pre><code>n=0,1,2 {<br>
    (1.31.12) SSXn = TRX + R11*VXn + R12*VYn +R13*VZn; &lt;1&gt;<br>
    (1.31.12) SSYn = TRY + R21*VXn + R22*VYn +R23*VZn; &lt;2&gt;<br>
    (1.31.12) SSZn = TRZ + R31*VXn + R32*VYn +R33*VZn; &lt;3&gt;<br>
    (0.16. 0) SZx(0) = SZ2(3);<br>
    (0.16. 0) SZ0(1) = limC(SSZ0);<br>
    (0.16. 0) SZ0(2) = limC(SSZ1);<br>
    (0.16. 0) SZ0(3) = limC(SSZ2);<br>
    (1.27.16) SXn = OFX + IR1*(H/SZ n); &lt;4&gt;<br>
    (1.27.16) SYn = OFY + IR2*(H/SZ n); &lt;4&gt;<br>
    (1.19.24) P = DQB + DQA*(H/SZ2); &lt;4&gt;<br>
    (1. 3.12) IR0 = limE(P);<br>
    (1.15. 0) SXn = limD1(SXn);<br>
    (1.15. 0) SYn = limD2(SYn);<br>
}<br>
    (1.15. 0) IR1 = limA1S(SSX2);<br>
    (1.15. 0) IR2 = limA2S(SSY2);<br>
    (1.15. 0) IR3 = limA3S(SSZ2);<br>
    (1. 7.24) MAC0 = P;<br>
    (1.31. 0) MAC1 = SSX2;<br>
    (1.31. 0) MAC2 = SSY2;<br>
    (1.31. 0) MAC3 = SSZ2;<br>
</code></pre>

<h2>NCDS Required cycles: 19</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>(1.19.24) LL1 = L11*VX0 + L12*VY0 + L13*VZ0; &lt;1&gt;<br>
(1.19.24) LL2 = L21*VX0 + L22*VY0 + L23*VZ0; &lt;2&gt;<br>
(1.19.24) LL3 = L31*VX0 + L32*VY0 + L33*VZ0; &lt;3&gt;<br>
(1. 3.12) L1 = limA1U(LL1);<br>
(1. 3.12) L2 = limA2U(LL2);<br>
(1. 3.12) L3 = limA3U(LL3);<br>
(1.19.24) RRLT = RBK + LR1*L1 + LR2*L2 + LR3*L3; &lt;1&gt;<br>
(1.19.24) GGLT = GBK + LG1*L1 + LG2*L2 + LG3*L3; &lt;2&gt;<br>
(1.19.24) BBLT = BBK + LB1*L1 + LB2*L2 + LB3*L3; &lt;3&gt;<br>
(1. 3.12) RLT = limA1U(RRLT);<br>
(1. 3.12) GLT = limA2U(GGLT);<br>
(1. 3.12) BLT = limA3U(BBLT);<br>
(1.27.16) RR0 = R*RLT + IR0*limA1S(RFC - R*RLT); &lt;1&gt;<br>
(1.27.16) GG0 = G*GLT + IR0*limA2S(GFC - G*GLT); &lt;2&gt;<br>
(1.27.16) BB0 = B*BLT + IR0*limA3S(BFC - B*BLT); &lt;3&gt;<br>
(1.11. 4) IR1 = limA1U(RR0);<br>
(1.11. 4) IR2 = limA2U(GG0);<br>
(1.11. 4) IR3 = limA3U(BB0);<br>
(-. 8. -) CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 8. 0) R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 8. 0) G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 8. 0) B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.27. 4) MAC1 = RR0;<br>
(1.27. 4) MAC2 = GG0;<br>
(1.27. 4) MAC3 = BB0;<br>
</code></pre>

<h2>NCDT Required cycles: 44</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>n=0,1,2 {<br>
    (1.19.24) LL1n = L11*VXn + L12*Vyn + L13*VZn; &lt;1&gt;<br>
    (1.19.24) LL2n = L21*VXn + L22*Vyn + L23*VZn; &lt;2&gt;<br>
    (1.19.24) LL3n = L31*VXn + L32*Vyn + L33*VZn; &lt;3&gt;<br>
    (1. 3.12) L1n = limA1U(LL1n);<br>
    (1. 3.12) L2n = limA2U(LL2n);<br>
    (1. 3.12) L3n = limA3U(LL3n);<br>
    (1.19.24) RRLTn = RBK + LR1*L1n + LR2*L2n + LR3*L3n; &lt;1&gt;<br>
    (1.19.24) GGLTn = GBK + LG1*L1n + LG2*L2n + LG3*L3n; &lt;2&gt;<br>
    (1.19.24) BBLTn = BBK + LB1*L1n + LB2*L2n + LB3*L3n; &lt;3&gt;<br>
    (1. 3.12) RLTn = limA1U(RRLTn);<br>
    (1. 3.12) GLTn = limA2U(GGLTn);<br>
    (1. 3.12) BLTn = limA3U(BBLTn);<br>
    (1.27.16) RRn = R*RLTn + IR0*limA1S(RFC - R*RLTn); &lt;1&gt;<br>
    (1.27.16) GGn = G*GLTn + IR0*limA2S(GFC - G*GLTn); &lt;2&gt;<br>
    (1.27.16) BBn = B*BLTn + IR0*limA3S(BFC - B*BLTn); &lt;3&gt;<br>
    (-. 8. -) CDn = CODE<br>
    (-. 8. 0) Rn = limB1(RRn); Gn = limB2(GGn);<br>
    (-.8. 0) Bn = limB3(BBn);<br>
}<br>
    (1.11. 4) IR1 = limA1U(RR2);<br>
    (1.11. 4) IR2 = limA2U(GG2);<br>
    (1.11. 4) IR3 = limA3U(BB2);<br>
    (1.27. 4) MAC1 = RR2;<br>
    (1.27. 4) MAC2 = GG2;<br>
    (1.27. 4) MAC3 = BB2;<br>
</code></pre>

<h2>NCCS Required cycles: 17</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>(1.19.24) LL1 = L11*VX0 + L12*VY0 + L13*VZ0; &lt;1&gt;<br>
(1.19.24) LL2 = L21*VX0 + L22*VY0 + L23*VZ0; &lt;2&gt;<br>
(1.19.24) LL3 = L31*VX0 + L32*VY0 + L33*VZ0; &lt;3&gt;<br>
(1. 3.12) L1 = limA(LL1);<br>
(1. 3.12) L2 = limA(LL2);<br>
(1. 3.12) L3 = limA(LL3);<br>
(1.19.24) RRLT = RBK + LR1*L1 +LR2*L2 + LR3*L3; &lt;1&gt;<br>
(1.19.24) GGLT = GBK + LG1*L1 +LG2*L2 + LG3*L3; &lt;2&gt;<br>
(1.19.24) BBLT = BBK + LB1*L1 +LB2*L2 + LB3*L3; &lt;3&gt;<br>
(1. 3.12) RLT = limA1U(RRLT);<br>
(1. 3.12) GLT = limA2U(GGLT);<br>
(1. 3.12) BLT = limA3U(BBLT);<br>
(1.27.16) RR0 = R*RLT; &lt;1&gt;<br>
(1.27.16) GG0 = G*GLT; &lt;2&gt;<br>
(1.27.16) BB0 = B*BLT; &lt;3&gt;<br>
(1.11. 4) IR1 = limA1U(RR0);<br>
(1.11. 4) IR2 = limA2U(GG0);<br>
(1.11. 4) IR3 = limA3U(BB0);<br>
(-. 8. -) CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 8. 0) R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 8. 0) G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 8. 0) B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.27. 4) MAC1 = RR0;<br>
(1.27. 4) MAC2 = GG0;<br>
(1.27. 4) MAC3 = BB0;<br>
</code></pre>

<h2>NCCT Required cycles: 39</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>n=0,1,2 {<br>
    (1.19.24) LL1n = L11*VXn + L12*VYn + L13*VZn; &lt;1&gt;<br>
    (1.19.24) LL2n = L21*VXn + L22*VYn + L23*VZn; &lt;2&gt;<br>
    (1.19.24) LL3n = L31*VXn + L32*VYn + L33*VZn; &lt;3&gt;<br>
    (1. 3.12) L1n = limA1U(LL1n);<br>
    (1. 3.12) L2n = limA2U(LL2n);<br>
    (1. 3.12) L3n = limA3U(LL3n);<br>
    (1.19.24) RRLTn = RBK + LR1*L1n + LR2*L2n + LR3*L3n; &lt;1&gt;<br>
    (1.19.24) GGLTn = GBK + LG1*L1n + LG2*L2n + LG3*L3n; &lt;2&gt;<br>
    (1.19.24) BBLTn = BBK + LB1*L1n + LB2*L2n + LB3*L3n; &lt;3&gt;<br>
    (1. 3.12) RLTn = limA1U(RRLTn);<br>
    (1. 3.12) GLTn = limA2U(GGLTn);<br>
    (1. 3.12) BLTn = limA3U(BBLTn);<br>
    (1.27.16) RRn = R*RLTn; &lt;1&gt;<br>
    (1.27.16) GGn = G*GLTn; &lt;2&gt;<br>
    (1.27.16) BBn = B*BLTn; &lt;3&gt;<br>
    (-. 8. -) CDn = CODE<br>
    (0. 8. 0) Rn = limB1(RRn);<br>
    (0. 8. 0) Gn = limB2(GGn);<br>
    (0. 8. 0) Bn = limB3(BBn);<br>
}<br>
    (1.11. 4) IR1 = limA1U(RR2); IR2 = limA2U(GG2);<br>
    (1.11. 4) IR3 = limA3U(BB2);<br>
    (1.27. 4) MAC1 = RR2;<br>
    (1.27. 4) MAC2 = GG2;<br>
    (1.27. 4) MAC3 = BB2;<br>
</code></pre>

<h2>CDP Required cycles: 13</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>(1.19.24) RRLT = RBK + LR1*IR1 + LR2*IR2 + LR3*IR3; &lt;1&gt;<br>
(1.19.24) GGLT = GBK + LG1*IR1 + LG2*IR2 + LG3*IR3; &lt;2&gt;<br>
(1.19.24) BBLT = BBK + LB1*IR1 + LB2*IR2 + LB3*IR3; &lt;3&gt;<br>
(1. 3.12) RLT = limA1U(RRLT);<br>
(1. 3.12) GLT = limA2U(GGLT);<br>
(1. 3.12) BLT = limA3U(BBLT);<br>
(1.27.16) RR0 = R*RLT + IR0*limA1S(RFC - R*RLT); &lt;1&gt;<br>
(1.27.16) GG0 = G*GLT + IR0*limA2S(GFC - G*GLT); &lt;2&gt;<br>
(1.27.16) BB0 = B*BLT + IR0*limA3S(BFC - B*BLT); &lt;3&gt;<br>
(1.11. 4) IR1 = limA1U(RR0);<br>
(1.11. 4) IR2 = limA2U(GG0);<br>
(1.11. 4) IR3 = limA3U(BB0);<br>
(-. 8. -) CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 8. 0) R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 8. 0) G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 8. 0) B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.27. 4) MAC1 = RR0;<br>
(1.27. 4) MAC2 = GG0;<br>
(1.27. 4) MAC3 = BB0;<br>
</code></pre>

<h2>CC Required cycles: 11</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>(1.19.24) RRLT = RBK + LR1*IR1 + LR2*IR2 + LR3*IR3; &lt;1&gt;<br>
(1.19.24) GGLT = GBK + LG1*IR1 + LG2*IR2 + LG3*IR3; &lt;2&gt;<br>
(1.19.24) BBLT = BBK + LB1*IR1 + LB2*IR2 + LB3*IR3; &lt;3&gt;<br>
(1. 3.12) RLT = limA1U(RRLT);<br>
(1. 3.12) GLT = limA2U(GGLT);<br>
(1. 3.12) BLT = limA3U(BBLT);<br>
(1.27.16) RR0 = R*RLT; &lt;1&gt;<br>
(1.27.16) GG0 = G*GLT; &lt;2&gt;<br>
(1.27.16) BB0 = B*BLT; &lt;3&gt;<br>
(1.11. 4) IR1 = limA1U(RR0);<br>
(1.11. 4) IR2 = limA2U(GG0);<br>
(1.11. 4) IR3 = limA3U(BB0);<br>
(-. 8. -) CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 8. 0) R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 8. 0) G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 8. 0) B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.27. 4) MAC1 = RR0;<br>
(1.27. 4) MAC2 = GG0;<br>
(1.27. 4) MAC3 = BB0;<br>
</code></pre>

<h2>NCS Required cycles: 14</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>(1.19.24) LL1 = L11*VX0 + L12*VY0 + L13*VZ0; &lt;1&gt;<br>
(1.19.24) LL2 = L21*VX0 + L22*VY0 + L23*VZ0; &lt;2&gt;<br>
(1.19.24) LL3 = L31*VX0 + L32*VY0 + L33*VZ0; &lt;3&gt;<br>
(1. 3.12) L1 = limA1U(LL1);<br>
(1. 3.12) L2 = limA2U(LL2);<br>
(1. 3.12) L3 = limA3U(LL3);<br>
(1.19.24) RR0 = RBK + LR1*L1 + LR2*L2 + LR3*L3; &lt;1&gt;<br>
(1.19.24) GG0 = GBK + LG1*L1 + LG2*L2 + LG3*L3; &lt;2&gt;<br>
(1.19.24) BB0 = BBK + LB1*L1 + LB2*L2 + LB3*L3; &lt;3&gt;<br>
(1. 3.12) IR1 = limA1U(RR0);<br>
(1. 3.12) IR2 = limA2U(GG0);<br>
(1. 3.12) IR3 = limA3U(BB0);<br>
(-. 8. -) CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 0. 8) R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 0. 8) G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 0. 8) B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.19.12) MAC1 = RR0;<br>
(1.19.12) MAC2 = GG0;<br>
(1.19.12) MAC3 = BB0;<br>
</code></pre>

<h2>NCT Required cycles: 30</h2>

Function: Light source calculation<br>
<br>
Calculations:<br>
<pre><code>n=0,1,2 {<br>
    (1.19.24) LL1n = L11*VXn + L12*VYn + L13*VZn; &lt;1&gt;<br>
    (1.19.24) LL2n = L21*VXn + L22*VYn + L23*VZn; &lt;2&gt;<br>
    (1.19.24) LL3n = L31*VXn + L32*VYn + L33*VZn; &lt;3&gt;<br>
    (1. 3.12) L1n = limA1U(LL1n);<br>
    (1. 3.12) L2n = limA2U(LL2n);<br>
    (1. 3.12) L3n = limA3U(LL3n);<br>
    (1.19.24) RRn = RBK + LR1*L1n + LR2*L2n + LR3*L3n; &lt;1&gt;<br>
    (1.19.24) GGn = GBK + LG1*L1n + LG2*L2n + LG3*L3n; &lt;2&gt;<br>
    (1.19.24) BBn = BBK + LB1*L1n + LB2*L2n + LB3*L3n; &lt;3&gt;<br>
    (-. 8. -) CDn = CODE<br>
    (0. 0. 8) Rn = limB1(RRn);<br>
    (0. 0. 8) Gn = limB2(GGn);<br>
    (0. 0. 8) Bn = limB3(BBn);<br>
}<br>
    (1. 3.12) IR1 = limA1U(RR2);<br>
    (1. 3.12) IR2 = limA2U(GG2);<br>
    (1. 3.12) IR3 = limA3U(BB2);<br>
    (1.19.12) MAC1 = RR2;<br>
    (1.19.12) MAC2 = GG2;<br>
    (1.19.12) MAC3 = BB2;<br>
</code></pre>

<h2>MVMVA sf,mx,v,cv,lm Required cycles: 8</h2>

Function: Matrix and vector multiplication<br>
<br>
Items specified using arguments:<br>
<table><thead><th>Argument </th><th>Specified content </th><th>Value=0 </th><th>Value = 1 </th><th>Value = 2</th><th> Value = 3</th></thead><tbody>
<tr><td>sf </td><td>Scaling format </td><td>Scale large </td><td>Scale small </td><td>Not valid </td><td>Not valid</td></tr>
<tr><td>mx </td><td>Multiplication<br>array (MX)<br><b>(1.3.12)</b></td><td><b>R</b> </td><td><b>L</b> </td><td><b>LR</b> </td><td>Not valid</td></tr>
<tr><td>v </td><td>Multiplication<br>vector (V)<br><b>(1.m.n)</b></td><td><b>Vp0</b><br><b>p=X/Y/Z</b></td><td><b>Vp1</b><br><b>p=X/Y/Z</b></td><td><b>Vp2</b><br><b>p=X/Y/Z</b></td><td><b>IRp</b><br><b>p=1/2/3</b></td></tr>
<tr><td>cv </td><td>Addition vector<br>(CV)<br><b>(1.16+m. n)</b></td><td><b>TRp</b><br><b>p=X/Y/Z</b></td><td><b>pBK</b><br><b>p=R/B/G</b></td><td>Not valid </td><td><b>0</b></td></tr>
<tr><td>lm </td><td>Limiter A1/2/3<br>lower limit</td><td>-2<code>^</code>15 </td><td><b>0</b> </td><td>Not valid </td><td>Not valid</td></tr></tbody></table>

<code>*</code> Data formats<br>
The multiplication matrix data format is fixed.<br>
The other data formats are determined by the multiplication vector data format.<br>
<br>
Calculations: (m and n are determined by the multiplication vector data format.)<br>
<pre><code>(1.16+m.n+12)   MT1 = CV1 + MX11*V1 + MX12*V2 + MX13*V3; &lt;1&gt;<br>
(1.16+m.n+12)   MT2 = CV2 + MX21*V1 + MX22*V2 + MX23*V3; &lt;2&gt;<br>
(1.16+m.n+12)   MT3 = CV3 + MX31*V1 + MX32*V2 + MX33*V3; &lt;3&gt;<br>
(1.16+m.n)      MAC1 = MT1;<br>
(1.16+m.n)      MAC2 = MT2;<br>
(1.16+m.n)      MAC3 = MT3;<br>
sf == 0         sf == 1<br>
(1.m-12.n+12)   (1.m.n)     IR1 = limA1C(MT1);<br>
(1.m-12.n+12)   (1.m.n)     IR2 = limA2C(MT2);<br>
(1.m-12.n+12)   (1.m.n)     IR3 = limA3C(MT3);<br>
</code></pre>

<h2>INTPL Required cycles: 8</h2>

Function: Interpolation<br>
<br>
Calculations: (m and n specify the data format of IRp(p=1,2,3) as (1.m.n).)<br>
<pre><code>(1.16+m.n+12)   IPL1 = 1.0*IR1 + IR0*limA1S(RFC-1.0*IR1); &lt;1&gt;<br>
(1.16+m.n+12)   IPL2 = 1.0*IR2 + IR0*limA2S(GFC-1.0*IR2); &lt;2&gt;<br>
(1.16+m.n+12)   IPL3 = 1.0*IR3 + IR0*limA3S(BFC-1.0*IR3); &lt;3&gt;<br>
(1.m.n)         IR1 = limA1S(IPL1);<br>
(1.m.n)         IR2 = limA2S(IPL2);<br>
(1.m.n)         IR3 = limA3S(IPL3);<br>
(-.8.-)         CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0.12-n.n-4)    R0 &lt;- R1 &lt;- R2 &lt;- limB1(IPL1);<br>
(0.12-n.n-4)    G0 &lt;- G1 &lt;- G2 &lt;- limB2(IPL2);<br>
(0.12-n.n-4)    B0 &lt;- B1 &lt;- B2 &lt;- limB3(IPL3);<br>
(1.16+m.n)      MAC1 = IPL1;<br>
(1.16+m.n)      MAC2 = IPL2;<br>
(1.16+m.n)      MAC3 = IPL3;<br>
</code></pre>

<h2>DPCL Required cycles: 8</h2>

Function: Depth queuing<br>
<br>
Calculations:<br>
<pre><code>(1.27.16)   RR0 = R*IR1 + IR0*limA1S(RFC - R*IR1); &lt;1&gt;<br>
(1.27.16)   GG0 = G*IR2 + IR0*limA2S(GFC - G*IR2); &lt;2&gt;<br>
(1.27.16)   BB0 = B*IR3 + IR0*limA3S(BFC - B*IR3); &lt;3&gt;<br>
(1.11. 4)   IR1 = limA1S(RR0);<br>
(1.11. 4)   IR2 = limA2S(GG0);<br>
(1.11. 4)   IR3 = limA3S(BB0);<br>
(-. 8. -)   CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 8. 0)   R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 8. 0)   G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 8. 0)   B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.27. 4)   MAC1 = RR0;<br>
(1.27. 4)   MAC2 = GG0;<br>
(1.27. 4)   MAC3 = BB0;<br>
</code></pre>

<h2>DPCS Required cycles: 8</h2>

Function: Depth queuing<br>
<br>
Calculations:<br>
<pre><code>(1.27.16) RR0 = R*1.0 + IR0*limA1S(RFC-R*1.0); &lt;1&gt;<br>
(1.27.16) GG0 = G*1.0 + IR0*limA2S(GFC-G*1.0); &lt;2&gt;<br>
(1.27.16) BB0 = B*1.0 + IR0*limA3S(BFC-B*1.0); &lt;3&gt;<br>
(1.11. 4) IR1 = limA1S(RR0);<br>
(1.11. 4) IR2 = limA2S(GG0);<br>
(1.11. 4) IR3 = limA3S(BB0);<br>
(-.8.-) CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 8. 0) R0 &lt;- R1 &lt;- R2 &lt;- limB1(RR0);<br>
(0. 8. 0) G0 &lt;- G1 &lt;- G2 &lt;- limB2(GG0);<br>
(0. 8. 0) B0 &lt;- B1 &lt;- B2 &lt;- limB3(BB0);<br>
(1.27. 4) MAC1 = RR0;<br>
(1.27. 4) MAC2 = GG0;<br>
(1.27. 4) MAC3 = BB0;<br>
</code></pre>

<h2>DPCT Required cycles: 17</h2>

Function: Depth queuing<br>
<br>
Calculations:<br>
<br>
<pre><code>n=0,1,2 {<br>
    (1.27.16)   RRn = Rn*1.0 + IR0*limA1S(RFC-R*1.0); &lt;1&gt;<br>
    (1.27.16)   GGn = Gn*1.0 + IR0*limA2S(GFC-G*1.0); &lt;2&gt;<br>
    (1.27.16)   BBn = Bn*1.0 + IR0*limA3S(BFC-B*1.0); &lt;3&gt;<br>
    (1.11. 4)   IR1 = limA1S(RR2);<br>
    (1.11. 4)   IR2 = limA2S(GG2);<br>
    (1.11. 4)   IR3 = limA3S(BB2);<br>
    (-.8.-)     CDn = CODE<br>
    (0. 8. 0)   Rn = limB1(RRn);<br>
    (0. 8. 0)   Gn = limB2(GGn);<br>
    (0. 8. 0)   Bn = limB3(BBn);<br>
}<br>
    (1.27. 4)   MAC1 = RR2;<br>
    (1.27. 4)   MAC2 = GG2;<br>
    (1.27. 4)   MAC3 = BB2;<br>
</code></pre>

<h2>SQR sf  Required cycles: 5</h2>

Function: Vector squaring<br>
<br>
Items specified using arguments:<br>
<br>
<table><thead><th>Argument </th><th>Specified content </th><th>Value=0 </th><th>Value=1</th></thead><tbody>
<tr><td>sf </td><td>Output format </td><td>-- </td><td>Performs calculations on data <br>shifted 12 bits to the left in the<br>IRn register.</td></tr></tbody></table>

Calculations: (m and n specify the data format of IRp(p=1,2,3) as (1.m.n).)<br>
<pre><code>sf == 0     sf == 1<br>
(1.m+28.n)  (1.m+16.n+12)   L1 = IR1*IR1; &lt;1&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   L2 = IR2*IR2; &lt;2&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   L3 = IR3*IR3; &lt;3&gt;<br>
(1.m.n)     (1.m+16.n+12)   IR1 = limA1U(L1);<br>
(1.m.n)     (1.m+16.n+12)   IR2 = limA2U(L2);<br>
(1.m.n)     (1.m+16.n+12)   IR3 = limA3U(L3);<br>
(1.m+16.0)  (1.m+16.n+12)   MAC1 = L1;<br>
(1.m+16.0)  (1.m+16.n+12)   MAC2 = L2;<br>
(1.m+16.0)  (1.m+16.n+12)   MAC3 = L3;<br>
</code></pre>

<h2>AVSZ3 Required cycles: 5</h2>

Function: Z-averaging<br>
<br>
Calculations:<br>
<pre><code>(1.31.21)   OOTZ = ZSF3*SZ0(1)<br>
                    + ZSF3*SZ1(2)<br>
                    + ZSF3*SZ2(3); &lt;4&gt;<br>
(0.16. 0)   OTZ = limC(OOTZ);<br>
(1.31. 0)   MAC0 = OOTZ;<br>
</code></pre>

<h2>AVSZ4 Required cycles: 6</h2>

Function: Z-averaging<br>
<br>
Calculations:<br>
<pre><code>(1.31.12)   OOTZ =ZSF4*SZx(0)<br>
                    + ZSF4*SZ0(1)<br>
                    + ZSF4*SZ1(2)<br>
                    + ZSF4*SZ2(3); &lt;4&gt;<br>
(0.16. 0)   OTZ = limC(OOTZ);<br>
(1.31. 0)   MAC0 = OOTZ;<br>
</code></pre>

<h2>NCLIP Required cycles: 8</h2>

Function: Normal clipping<br>
<br>
Calculations:<br>
<pre><code>(1.43. 0) OPZ = SX0*SY1 + SX1*SY2 + SX2*SY0<br>
                - SX0*SY2 - SX1*SY0 - SX2*SY1; &lt;4&gt;<br>
(1.31. 0) MAC0 = OPZ;<br>
</code></pre>

<h2>OP sf   Required cycles: 6</h2>

Function: Outer product<br>
<br>
Items specified using arguments:<br>
<br>
<table><thead><th>Argument </th><th>Specified content </th><th>Value=0 </th><th>Value=1</th></thead><tbody>
<tr><td>sf </td><td>Output format </td><td>--</td><td> Performs calculations on data<br>shifted 12 bits to the left in the<br>IRn register.</td></tr></tbody></table>

Calculations: (m and n specify the data format of IRp(p=1,2,3) as (1.m.n).)<br>
<pre><code>sf == 0     sf == 1<br>
(1.m+28.n)  (1.m+16.n+12)   OPX = DY1(R22)*DZ2(IR3)<br>
                                  - DZ1(R33)*DY2(IR2); &lt;1&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   OPY = DZ1(R33)*DX2(IR1)<br>
                                  - DX1(R11)*DZ2(IR3); &lt;2&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   OPZ = DX1(R11)*DY2(IR2)<br>
                                  - DY1(R22)*DX2(IR1); &lt;3&gt;<br>
(1.m.n)     (1.m.n)         IR1 = limA1S(OPX);<br>
(1.m.n)     (1.m.n)         IR2 = limA2S(OPY);<br>
(1.m.n)     (1.m.n)         IR3 = limA3S(OPZ);<br>
(1.m+16.n)  (1.m+16.n)      MAC1 = OPX;<br>
(1.m+16.n)  (1.m+16.n)      MAC2 = OPY;<br>
(1.m+16.n)  (1.m+16.n)      MAC3 = OPZ;<br>
</code></pre>

<h2>GPF sf  Required cycles: 5</h2>

Function: General purpose interpolation<br>
<br>
Items specified using arguments:<br>
<table><thead><th>Argument </th><th>Specified content </th><th>Value=0 </th><th>Value=1</th></thead><tbody>
<tr><td>sf </td><td>Output format </td><td>-- </td><td>Performs calculations on data<br>shifted 12 bits to the left in the<br>IRn register.</td></tr></tbody></table>

Calculations: (m and n specify the data format of IRp(p=1,2,3) as (1.m.n).)<br>
<pre><code>sf == 0     sf == 1<br>
(1.m+28.n)  (1.m+16.n+12)   IPX = IR0*IR1; &lt;1&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   IPY = IR0*IR2; &lt;2&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   IPZ = IR0*IR3; &lt;3&gt;<br>
(1.m.n)     (1.m.n)         IR1 = limA1S(IPX);<br>
(1.m.n)     (1.m.n)         IR2 = limA2S(IPY);<br>
(1.m.n)     (1.m.n)         IR3 = limA3S(IPZ);<br>
(1.m+16.n)  (1.m+16.n)      MAC1 = IPX;<br>
(1.m+16.n)  (1.m+16.n)      MAC2 = IPY;<br>
(1.m+16.n)  (1.m+16.n)      MAC3 = IPZ;<br>
(-.8.-)     CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 0. 8)   R0 &lt;- R1 &lt;- R2 &lt;- limB1(IPX);<br>
(0. 0. 8)   G0 &lt;- G1 &lt;- G2 &lt;- limB2(IPY);<br>
(0. 0. 8)   B0 &lt;- B1 &lt;- B2 &lt;- limB3(IPZ);<br>
</code></pre>

<h2>GPL sf Required cycles: 5</h2>

Function: General purpose interpolation<br>
<br>
Items specified using arguments:<br>
<table><thead><th>Argument </th><th>Specified content </th><th>Value=0 </th><th>Value=1</th></thead><tbody>
<tr><td>sf </td><td>Output format </td><td>-- </td><td>Performs calculations on data<br>shifted 12 bits to the left in the<br>IRn register.</td></tr></tbody></table>

Calculations: (m and n specify the data format of IRp(p=1,2,3) as (1.m.n).)<br>
<pre><code>sf == 0     sf == 1<br>
(1.m+28.n)  (1.m+16.n+12)   IPX = MAC1 + IR0*IR1; &lt;1&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   IPY = MAC2 + IR0*IR2; &lt;2&gt;<br>
(1.m+28.n)  (1.m+16.n+12)   IPZ = MAC3 + IR0*IR3; &lt;3&gt;<br>
(1.m.n)     (1.m.n)         IR1 = limA1S(IPX);<br>
(1.m.n)     (1.m.n)         IR2 = limA2S(IPY);<br>
(1.m.n)     (1.m.n)         IR3 = limA3S(IPZ);<br>
(1.m+16.n)  (1.m+16.n)      MAC1 = IPX;<br>
(1.m+16.n)  (1.m+16.n)      MAC2 = IPY;<br>
(1.m+16.n)  (1.m+16.n)      MAC3 = IPZ;<br>
(-.8.-)     CD0 &lt;- CD1 &lt;- CD2 &lt;- CODE<br>
(0. 0. 8)   R0 &lt;- R1 &lt;- R2 &lt;- limB1(IPX);<br>
(0. 0. 8)   G0 &lt;- G1 &lt;- G2 &lt;- limB2(IPY);<br>
(0. 0. 8)   B0 &lt;- B1 &lt;- B2 &lt;- limB3(IPZ);<br>
</code></pre>