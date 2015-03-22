# GTE Register Specification #

## Control Register Group ##

|Register<br>number<table><thead><th>Name </th><th>Access </th><th>Content</th></thead><tbody>
<tr><td> <b>0</b> </td><td> <b>R11R12</b> </td><td> <b>R/W</b> </td><td> Rotation matrix </td></tr>
<tr><td> <b>1</b> </td><td> <b>R13R21</b> </td><td> <b>R/W</b> </td><td> Rotation matrix </td></tr>
<tr><td> <b>2</b> </td><td> <b>R22R23</b> </td><td> <b>R/W</b> </td><td> Rotation matrix </td></tr>
<tr><td> <b>3</b> </td><td> <b>R31R32</b> </td><td> <b>R/W</b> </td><td> Rotation matrix </td></tr>
<tr><td> <b>4</b> </td><td> <b><a href='https://code.google.com/p/pops-gte/source/detail?r=33'>R33</a></b> </td><td> <b>R/W</b> </td><td> Rotation matrix </td></tr>
<tr><td> <b>5</b> </td><td> <b>TRX</b> </td><td> <b>R/W</b> </td><td> Translation vector (X) </td></tr>
<tr><td> <b>6</b> </td><td> <b>TRY</b> </td><td> <b>R/W</b> </td><td> Translation vector (Y) </td></tr>
<tr><td> <b>7</b> </td><td> <b>TRZ</b> </td><td> <b>R/W</b> </td><td> Translation vector (Z) </td></tr>
<tr><td> <b>8</b> </td><td> <b>L11L12</b> </td><td> <b>R/W</b> </td><td> Light source direction vector X 3 </td></tr>
<tr><td> <b>9</b> </td><td> <b>L13L21</b> </td><td> <b>R/W</b> </td><td> Light source direction vector X 3 </td></tr>
<tr><td> <b>10</b> </td><td> <b>L22L23</b> </td><td> <b>R/W</b> </td><td> Light source direction vector X 3 </td></tr>
<tr><td> <b>11</b> </td><td> <b>L31L32</b> </td><td> <b>R/W</b> </td><td> Light source direction vector X 3 </td></tr>
<tr><td> <b>12</b> </td><td> <b>L33</b> </td><td> <b>R/W</b> </td><td> Light source direction vector X 3 </td></tr>
<tr><td> <b>13</b> </td><td> <b>RBK</b> </td><td> <b>R/W</b> </td><td> Peripheral color (background color) (R) </td></tr>
<tr><td> <b>14</b> </td><td> <b>GBK</b> </td><td> <b>R/W</b> </td><td> Peripheral color (background color) (B) </td></tr>
<tr><td> <b>15</b> </td><td> <b>BBK</b> </td><td> <b>R/W</b> </td><td> Peripheral color (background color) (G) </td></tr>
<tr><td> <b>16</b> </td><td> <b>LR1LR2</b> </td><td> <b>R/W</b> </td><td> Light source color X 3 </td></tr>
<tr><td> <b>17</b> </td><td> <b>LR3LG1</b> </td><td> <b>R/W</b> </td><td> Light source color X 3 </td></tr>
<tr><td> <b>18</b> </td><td> <b>LG2LG3</b> </td><td> <b>R/W</b> </td><td> Light source color X 3 </td></tr>
<tr><td> <b>19</b> </td><td> <b>LB1LB2</b> </td><td> <b>R/W</b> </td><td> Light source color X 3 </td></tr>
<tr><td> <b>20</b> </td><td> <b>LB3</b> </td><td> <b>R/W</b> </td><td> Light source color X 3 </td></tr>
<tr><td> <b>21</b> </td><td> <b>RFC</b> </td><td> <b>R/W</b> </td><td> Far color (R) </td></tr>
<tr><td> <b>22</b> </td><td> <b>GFC</b> </td><td> <b>R/W</b> </td><td> Far color (G) </td></tr>
<tr><td> <b>23</b> </td><td> <b>BFC</b> </td><td> <b>R/W</b> </td><td> Far color (B) </td></tr>
<tr><td> <b>24</b> </td><td> <b>OFX</b> </td><td> <b>R/W</b> </td><td> Screen offset (X) </td></tr>
<tr><td> <b>25</b> </td><td> <b>OFY</b> </td><td> <b>R/W</b> </td><td> Screen offset (Y) </td></tr>
<tr><td> <b>26</b> </td><td> <b>H</b> </td><td> <b>R/W</b> </td><td> Screen position </td></tr>
<tr><td> <b>27</b> </td><td> <b>DQA</b> </td><td> <b>R/W</b> </td><td> Depth parameter A (coefficient) </td></tr>
<tr><td> <b>28</b> </td><td> <b>DQB</b> </td><td> <b>R/W</b> </td><td> Depth parameter B (offset) </td></tr>
<tr><td> <b>29</b> </td><td> <b>ZSF3</b> </td><td> <b>R/W</b> </td><td> Z-averaging scale factor </td></tr>
<tr><td> <b>30</b> </td><td> <b>ZSF4</b> </td><td> <b>R/W</b> </td><td> Z-averaging scale factor </td></tr>
<tr><td> <b>31</b> </td><td> <b>FLAG</b> </td><td> <b>R</b> </td><td> Flag </td></tr></tbody></table>

<h2>Data Register Group</h2>

<table><thead><th>Register<br>number </th><th>Name </th><th>Access </th><th>Content</th></thead><tbody>
<tr><td> <b>0</b> </td><td> <b>VXY0</b> </td><td> <b>R/W</b> </td><td> Vector #0 (X/Y) </td></tr>
<tr><td> <b>1</b> </td><td> <b>VZ0</b> </td><td> <b>R/W</b> </td><td> Vector #0 (Z) </td></tr>
<tr><td> <b>2</b> </td><td> <b>VXY1</b> </td><td> <b>R/W</b> </td><td> Vector #1 (X/Y) </td></tr>
<tr><td> <b>3</b> </td><td> <b>VZ1</b> </td><td> <b>R/W</b> </td><td> Vector #1 (Z) </td></tr>
<tr><td> <b>4</b> </td><td> <b>VXY2</b> </td><td> <b>R/W</b> </td><td> Vector #2 (X/Y) </td></tr>
<tr><td> <b>5</b> </td><td> <b>VZ2</b> </td><td> <b>R/W</b> </td><td> Vector #2 (Z) </td></tr>
<tr><td> <b>6</b> </td><td> <b>RGB</b> </td><td> <b>R/W</b> </td><td> Color data + GTE instruction </td></tr>
<tr><td> <b>7</b> </td><td> <b>OTZ</b> </td><td> <b>R</b> </td><td> Z-component average value </td></tr>
<tr><td> <b>8</b> </td><td> <b>IR0</b> </td><td> <b>R/W</b> </td><td> Intermediate value #0 </td></tr>
<tr><td> <b>9</b> </td><td> <b>IR1</b> </td><td> <b>R/W</b> </td><td> Intermediate value #1 </td></tr>
<tr><td> <b>10</b> </td><td> <b>IR2</b> </td><td> <b>R/W</b> </td><td> Intermediate value #2 </td></tr>
<tr><td> <b>11</b> </td><td> <b>IR3</b> </td><td> <b>R/W</b> </td><td> Intermediate value #3 </td></tr>
<tr><td> <b>12</b> </td><td> <b>SXY0</b> </td><td> <b>R/W</b> </td><td> Calculation result record (XY) </td></tr>
<tr><td> <b>13</b> </td><td> <b>SXY1</b> </td><td> <b>R/W</b> </td><td> Calculation result record (XY) </td></tr>
<tr><td> <b>14</b> </td><td> <b>SXY2</b> </td><td> <b>R/W</b> </td><td> Calculation result record (XY) </td></tr>
<tr><td> <b>15</b> </td><td> <b>SXYP</b> </td><td> <b>W</b> </td><td> Calculation result setting register </td></tr>
<tr><td> <b>16</b> </td><td> <b>SZ0</b> </td><td> <b>R/W</b> </td><td> Calculation result record (Z) </td></tr>
<tr><td> <b>17</b> </td><td> <b>SZ1</b> </td><td> <b>R/W</b> </td><td> Calculation result record (Z) </td></tr>
<tr><td> <b>18</b> </td><td> <b>SZ2</b> </td><td> <b>R/W</b> </td><td> Calculation result record (Z) </td></tr>
<tr><td> <b>19</b> </td><td> <b>SZ3</b> </td><td> <b>R/W</b> </td><td> Calculation result record (Z) </td></tr>
<tr><td> <b>20</b> </td><td> <b>RGB0</b> </td><td> <b>R/W</b> </td><td> Calculation result record (color data) </td></tr>
<tr><td> <b>21</b> </td><td> <b>RGB1</b> </td><td> <b>R/W</b> </td><td> Calculation result record (color data) </td></tr>
<tr><td> <b>22</b> </td><td> <b>RGB2</b> </td><td> <b>R/W</b> </td><td> Calculation result record (color data) </td></tr>
<tr><td> <b>23</b> </td><td> <b>RES1</b> </td><td> <b>n/a</b> </td><td> Reserved by system (access prohibited) </td></tr>
<tr><td> <b>24</b> </td><td> <b>MAC0</b> </td><td> <b>R</b> </td><td> Sum of products #0 </td></tr>
<tr><td> <b>25</b> </td><td> <b>MAC1</b> </td><td> <b>R/W</b> </td><td> Sum of products #1 </td></tr>
<tr><td> <b>26</b> </td><td> <b>MAC2</b> </td><td> <b>R/W</b> </td><td> Sum of products #2 </td></tr>
<tr><td> <b>27</b> </td><td> <b>MAC3</b> </td><td> <b>R/W</b> </td><td> Sum of products #3 </td></tr>
<tr><td> <b>28</b> </td><td> <b>IRGB</b> </td><td> <b>W</b> </td><td> Color data input register </td></tr>
<tr><td> <b>29</b> </td><td> <b>ORGB</b> </td><td> <b>R</b> </td><td> Color data output register </td></tr>
<tr><td> <b>30</b> </td><td> <b>LZCS</b> </td><td> <b>W</b> </td><td> Leading zero/one count source data </td></tr>
<tr><td> <b>31</b> </td><td> <b>LZCR</b> </td><td> <b>R</b> </td><td> Leading zero/one count processing result </td></tr></tbody></table>

<b>Register number: Control #0</b>

Register name: R11R12<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |R12                              |R11                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
R11     (1.3.12)        Element (1,1) of rotation matrix<br>
R12     (1.3.12)        Element (1,2) of rotation matrix<br>
</code></pre>

<b>Register number: Control #1</b>

Register name: R21R13<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |R21                              |R13                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
R13     (1.3.12)        Element (1,3) of rotation matrix<br>
R21     (1.3.12)        Element (2,1) of rotation matrix<br>
</code></pre>

<b>Register number: Control #2</b>

Register name: R23R22<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |R23                              |R22                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
R22     (1.3.12)        Element (2,2) of rotation matrix<br>
R23     (1.3.12)        Element (2,3) of rotation matrix<br>
</code></pre>

<b>Register number: Control #3</b>

Register name: R32R31<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |R32                              |R31                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
R31     (1.3.12)        Element (3,1) of rotation matrix<br>
R32     (1.3.12)        Element (3,2) of rotation matrix<br>
</code></pre>

<b>Register number: Control #4</b>

Register name: <a href='https://code.google.com/p/pops-gte/source/detail?r=33'>R33</a><br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |R33                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
R33     (1.3.12)        Element (3,3) of rotation matrix<br>
</code></pre>

Matrix expression of Control registers 1-4:<br>
<pre><code>            -               -<br>
           |(1,1),(1,2),(1,3)|<br>
Matrix X = |(2,1),(2,2),(2,3)|<br>
           |(3,1),(3,2),(3,3)|<br>
            -               -<br>
</code></pre>

<b>Register number: Control #5</b>

Register name: TRX<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |TRX                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
TRX     (1.31.0)        Translation vector X-component<br>
</code></pre>

<b>Register number: Control #6</b>

Register name: TRY<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |TRY                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
TRY     (1.31.0)        Translation vector Y-component<br>
</code></pre>

<b>Register number: Control #7</b>

Register name: TRZ<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |TRZ                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
TRZ     (1.31.0)        Translation vector Z-component<br>
</code></pre>

<b>Register number: Control #8</b>

Register name: L11L12<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |L12                              |L11                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
L11     (1.3.12)        Light source direction vector #1 X-component<br>
L12     (1.3.12)        Light source direction vector #1 Y-component<br>
</code></pre>

<b>Register number: Control #9</b>

Register name: L21L13<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |L21                              |L13                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
L13     (1.3.12)        Light source direction vector #1 Z-component<br>
L21     (1.3.12)        Light source direction vector #2 X-component<br>
</code></pre>

<b>Register number: Control #10</b>

Register name: L23L22<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |L23                              |L22                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
L22     (1.3.12)        Light source direction vector #2 Y-component<br>
L23     (1.3.12)        Light source direction vector #2 Z-component<br>
</code></pre>

<b>Register number: Control #11</b>

Register name: L32L31<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |L32                              |L31                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
L31     (1.3.12)        Light source direction vector #3 X-component<br>
L32     (1.3.12)        Light source direction vector #3 Y-component<br>
</code></pre>

<b>Register number: Control #12</b>

Register name: L33<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |L33                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
L33     (1.3.12)        Light source direction vector #3 Z-component<br>
</code></pre>

Matrix expression  of Control registers 8-12:<br>
"Light source direction vector X 3" is a matrix combining three light source direction vectors. The allocation of the elements is as<br>
follows.<br>
<pre><code>          -               -<br>
         |(1,X),(1,Y),(1,Z)|<br>
Matrix = |(2,X),(2,Y),(2,Z)|<br>
         |(3,X),(3,Y),(3,Z)|<br>
          -               -<br>
</code></pre>

<b>Register number: Control #13</b>

Register name: RBK<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |RBK                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
RBK     (1.19.12)        Background color R-component<br>
</code></pre>

<b>Register number: Control #14</b>

Register name: GBK<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |GBK                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
GBK     (1.19.12)        Background color G-component<br>
</code></pre>

<b>Register number: Control #15</b>

Register name: BBK<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |BBK                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
BBK     (1.19.12)        Background color B-component<br>
</code></pre>

<b>Register number: Control #16</b>

Register name: LR1LR2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |LR2                              |LR1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LR1     (1.3.12)        Light source color #1 R-component<br>
LR2     (1.3.12)        Light source color #2 R-component<br>
</code></pre>

<b>Register number: Control #17</b>

Register name: LR3LG1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |LG1                              |LR3                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LR3     (1.3.12)        Light source color #3 R-component<br>
LG1     (1.3.12)        Light source color #1 G-component<br>
</code></pre>

<b>Register number: Control #18</b>

Register name: LG2LG3<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |LG3                              |LG2                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LG2     (1.3.12)        Light source color #2 G-component<br>
LG3     (1.3.12)        Light source color #3 G-component<br>
</code></pre>

<b>Register number: Control #19</b>

Register name: LB1LB2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |LB2                              |LB1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LB1     (1.3.12)        Light source color #1 B-component<br>
LB2     (1.3.12)        Light source color #2 B-component<br>
</code></pre>

<b>Register number: Control #20</b>

Register name: LB3<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |LB3                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LB3     (1.3.12)        Light source color #3 B-component<br>
</code></pre>

Matrix expression:<br>
"Light source color X 3" is a matrix combining three light source RGB expression color data values. The allocation of the<br>
elements is as follows.<br>
<pre><code>          -               -<br>
         |(R,1),(R,2),(R,3)|<br>
Matrix = |(G,1),(G,2),(G,3)|<br>
         |(B,1),(B,2),(B,3)|<br>
          -               -<br>
</code></pre>

<b>Register number: Control #21</b>

Register name: RFC<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |RFC                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
RFC     (1.27.4)        Far color R-component<br>
</code></pre>

<b>Register number: Control #22</b>

Register name: GFC<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |GFC                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
GFC     (1.27.4)        Far color G-component<br>
</code></pre>

<b>Register number: Control #23</b>

Register name: BFC<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |BFC                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
BFC     (1.27.4)        Far color B-component<br>
</code></pre>

<b>Register number: Control #24</b>

Register name: OFX<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |OFX                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
OFX     (1.15.16)        Screen offset X-component<br>
</code></pre>

<b>Register number: Control #25</b>

Register name: OFY<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |OFY                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
OFY     (1.15.16)        Screen offset Y-component<br>
</code></pre>

<b>Register number: Control #26</b>

Register name: H<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |H                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
H     (0.16.0)        Screen position<br>
</code></pre>

<b>Register number: Control #27</b>

Register name: DQA<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |DQA                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
DQA     (1.7.8)        Depth parameter A (coefficient)<br>
</code></pre>

<b>Register number: Control #28</b>

Register name: DQB<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |DQB                                                              |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
DQB     (1.7.24)        Depth parameter B (offset)<br>
</code></pre>

<b>Register number: Control #29</b>

Register name: ZSF3<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |ZSF3                           |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
ZSF3     (1.3.12)        Z-averaging scale factor (normally set to 1/3)<br>
</code></pre>

<b>Register number: Control #30</b>

Register name: ZSF4<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |ZSF4                           |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
ZSF4     (1.3.12)        Z-averaging scale factor (normally set to 1/4)<br>
</code></pre>

<b>Register number: Control #31</b>

Register name: FLAG<br>
Access: R/W <i>(?) must be typo, should be read-only, see table "Control Registers Group"</i><br>
Bit pattern:<br>
<pre><code>Bit  31                                    12 11                     0<br>
     -----------------------------------------------------------------<br>
    |FLAG                                    |Not used                |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
FLAG    As indicated in table below<br>
</code></pre>

<table><thead><th>Bit<br>number</th><th>Content</th></thead><tbody>
<tr><td> <b>31</b> </td><td> Logical sum of bits 30 - 23 and bits 18 - 13 </td></tr>
<tr><td> <b>30</b> </td><td> 1: Calculation test result #1 overflow generated (2<code>^</code>43 or more) </td></tr>
<tr><td> <b>29</b> </td><td> 1: Calculation test result #2 overflow generated (2<code>^</code>43 or more)</td></tr>
<tr><td> <b>28</b> </td><td> 1: Calculation test result #3 overflow generated (2<code>^</code>43 or more)</td></tr>
<tr><td> <b>27</b> </td><td> 1: Calculation test result #1 underflow generated (less than -2<code>^</code>43)</td></tr>
<tr><td> <b>26</b> </td><td> 1: Calculation test result #2 underflow generated (less than -2<code>^</code>43)</td></tr>
<tr><td> <b>25</b> </td><td> 1: Calculation test result #3 underflow generated (less than -2<code>^</code>43)</td></tr>
<tr><td> <b>24</b> </td><td> 1: Limiter A1 out of range detected (less than 0 or less than -2<code>^</code>15, or 2<code>^</code>15 or more)</td></tr>
<tr><td> <b>23</b> </td><td> 1: Limiter A2 out of range detected (less than 0 or less than -2<code>^</code>15, or 2<code>^</code>15 or more)</td></tr>
<tr><td> <b>22</b> </td><td> 1: Limiter A3 out of range detected (less than -0 or less than -2<code>^</code>15, or 2<code>^</code>15 or more)</td></tr>
<tr><td> <b>21</b> </td><td> 1: Limiter B1 out of range detected (less than 0, or 2<code>^</code>8 or more)</td></tr>
<tr><td> <b>20</b> </td><td> 1: Limiter B2 out of range detected (less than 0, or 2<code>^</code>8 or more)</td></tr>
<tr><td> <b>19</b> </td><td> 1: Limiter B3 out of range detected (less than 0, or 2<code>^</code>8 or more)</td></tr>
<tr><td> <b>18</b> </td><td> 1: Limiter C out of range detected (less than 0, or 2<code>^</code>16 or more)</td></tr>
<tr><td> <b>17</b> </td><td> 1: Divide overflow generated (quotient of 2.0 or more)</td></tr>
<tr><td> <b>16</b> </td><td> 1: Calculation test result #4 overflow generated (2<code>^</code>31 or more)</td></tr>
<tr><td> <b>15</b> </td><td> 1: Calculation test result #4 underflow generated (less than -2<code>^</code>31)</td></tr>
<tr><td> <b>14</b> </td><td> 1: Limiter D1 out of range detected (less than -2<code>^</code>10, or 2<code>^</code>10 or more)</td></tr>
<tr><td> <b>13</b> </td><td> 1: Limiter D2 out of range detected (less than -2<code>^</code>10, or 2<code>^</code>10 or more)</td></tr>
<tr><td> <b>12</b> </td><td> 1: Limiter E out of range detected (less than 0, or 2<code>^</code>12 or more)</td></tr></tbody></table>

<b>Register number: Data #0</b>

Register name: VXY0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |VY0                              |VX0                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
VX0     (1.15.0) or (1.3.12)        Vector #0 X-element<br>
VY0     (1.15.0) or (1.3.12)        Vector #0 Y-element<br>
</code></pre>

<b>Register number: Data #1</b>

Register name: VZ0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |VZ0                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
VZ0     (1.15.0) or (1.3.12)        Vector #0 Z-element<br>
</code></pre>

<b>Register number: Data #2</b>

Register name: VXY1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |VY1                              |VX1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
VX1     (1.15.0) or (1.3.12)        Vector #1 X-element<br>
VY1     (1.15.0) or (1.3.12)        Vector #1 Y-element<br>
</code></pre>

<b>Register number: Data #3</b>

Register name: VZ1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |VZ1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
VZ1     (1.15.0) or (1.3.12)        Vector #1 Z-element<br>
</code></pre>

<b>Register number: Data #4</b>

Register name: VXY2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |VY2                              |VX2                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
VX2     (1.15.0) or (1.3.12)        Vector #2 X-element<br>
VY2     (1.15.0) or (1.3.12)        Vector #2 Y-element<br>
</code></pre>

<b>Register number: Data #5</b>

Register name: VZ2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |Not used                         |VZ2                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
VZ2     (1.15.0) or (1.3.12)        Vector #2 Z-element<br>
</code></pre>

<b>Register number: Data #6</b>

Register name: RGB<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                             16 15                              0<br>
     -------------------------------------------------------------------<br>
    |CODE            |B               |G               |R               |<br>
     -------------------------------------------------------------------<br>
<br>
Fields:<br>
R       (0.8.0)     Characteristic color R-element<br>
G       (0.8.0)     Characteristic color G-element<br>
B       (0.8.0)     Characteristic color B-element<br>
CODE    (-.8.-)     Arbitrary 8-bit data (normally specified by GPU draw command)<br>
</code></pre>

<b>Register number: Data #7</b>

Register name: OTZ<br>
Access: R<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |0                                |OTZ                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
OTZ     (0.15.0)        Z-element average value<br>
</code></pre>

<b>Register number: Data #8</b>

Register name: IR0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |sign                             |IR0                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
IR0     (1.3.12) or the like Intermediate value #0<br>
sign    All bits 0 or 1<br>
</code></pre>

<b>Register number: Data #9</b>

Register name: IR1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |sign                             |IR1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
IR1     (1.3.12) or the like Intermediate value #1<br>
sign    All bits 0 or 1<br>
</code></pre>

<b>Register number: Data #10</b>

Register name: IR2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |sign                             |IR2                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
IR2     (1.3.12) or the like Intermediate value #2<br>
sign    All bits 0 or 1<br>
</code></pre>

<b>Register number: Data #11</b>

Register name: IR3<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |sign                             |IR3                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
IR3     (1.3.12) or the like Intermediate value #3<br>
sign    All bits 0 or 1<br>
</code></pre>

<b>Register number: Data #12</b>

Register name: SXY0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |SY0                              |SX0                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SX0     (1.15.0)    X-element of 2-dimensional screen coordinates or 2-dimensional coordinates following<br>
                    perspective transformation. Note that this value was obtained in the calculation three times<br>
                    previous.<br>
SY0     (1.15.0)    Y-element of 2-dimensional screen coordinates or 2-dimensional coordinates following<br>
                    perspective transformation. Note that this value was obtained in the calculation three times<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
See Data #14: SXY2 and Data #15: SXYP.<br>
<br>
<b>Register number: Data #13</b>

Register name: SXY1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |SY1                              |SX1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SX1     (1.15.0)    X-element of 2-dimensional screen coordinates or 2-dimensional coordinates following<br>
                    perspective transformation. Note that this value was obtained in the calculation two times<br>
                    previous.<br>
SY1     (1.15.0)    Y-element of 2-dimensional screen coordinates or 2-dimensional coordinates following<br>
                    perspective transformation. Note that this value was obtained in the calculation two times<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
See Data #14: SXY2 and Data #15: SXYP.<br>
<br>
<b>Register number: Data #14</b>

Register name: SXY2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |SY2                              |SX2                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SX2     (1.15.0)    X-element of 2-dimensional screen coordinates or 2-dimensional coordinates following<br>
                    perspective transformation. Note that this value was obtained in the calculation one time<br>
                    previous.<br>
SY2     (1.15.0)    Y-element of 2-dimensional screen coordinates or 2-dimensional coordinates following<br>
                    perspective transformation. Note that this value was obtained in the calculation one time<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
In several GTE instructions, substitutions are made in the following sequence.<br>
SXY0 = SXY1;<br>
SXY1 = SXY2;<br>
SXY2 = Coordinate XY-elements obtained through calculation.<br>
<br>
<b>Register number: Data #15</b>

Register name: SXYP<br>
Access: W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |SYP                              |SXP                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SXP     (1.15.0)    X-element of coordinates transferred to SXY2<br>
SYP     (1.15.0)    Y-element of coordinates transferred to SXY2<br>
</code></pre>
Internal operations:<br>
The following operations are generated at the same time as the write.<br>
SXY0 = SXY1;<br>
SXY1 = SXY2;<br>
SXY2 = SXYP;<br>
<br>
<b>Register number: Data #16</b>

Register name: SZ0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |0                                |SZ0                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SZ0     (0.16.0)    Screen coordinate Z-element. Note that this value was obtained in the calculation four times<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
See Data #19: SZ3.<br>
<br>
<b>Register number: Data #17</b>

Register name: SZ1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |0                                |SZ1                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SZ1     (0.16.0)    Screen coordinate Z-element. Note that this value was obtained in the calculation three times<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
See Data #19: SZ3.<br>
<br>
<b>Register number: Data #18</b>

Register name: SZ2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |0                                |SZ2                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SZ2     (0.16.0)    Screen coordinate Z-element. Note that this value was obtained in the calculation two times<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
See Data #19: SZ3.<br>
<br>
<b>Register number: Data #19</b>

Register name: SZ3<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                            16 15                             0<br>
     -----------------------------------------------------------------<br>
    |0                                |SZ3                            |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
SZ3     (0.16.0)    Screen coordinate Z-element. Note that this value was obtained in the calculation one time<br>
                    previous.<br>
</code></pre>
Internal operations:<br>
In several GTE instructions, substitutions are made in the following sequence.<br>
SZ0 = SZ1;<br>
SZ1 = SZ2;<br>
SZ2 = SZ3;<br>
SZ3 = Coordinate Z-element obtained through calculation.<br>
<br>
<b>Register number: Data #20</b>

Register name: RGB0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                             16 15                              0<br>
     -------------------------------------------------------------------<br>
    |CD0             |B0              |G0              |R0              |<br>
     -------------------------------------------------------------------<br>
<br>
Fields:<br>
R0      (0.8.0)     Characteristic color R-element<br>
G0      (0.8.0)     Characteristic color G-element<br>
B0      (0.8.0)     Characteristic color B-element<br>
CD0     (-.8.-)     Arbitrary 8-bit data<br>
</code></pre>
Internal operations:<br>
See Data #22: RGB2.<br>
<br>
<b>Register number: Data #21</b>

Register name: RGB1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                             16 15                              0<br>
     -------------------------------------------------------------------<br>
    |CD1             |B1              |G1              |R1              |<br>
     -------------------------------------------------------------------<br>
<br>
Fields:<br>
R1      (0.8.0)     Characteristic color R-element<br>
G1      (0.8.0)     Characteristic color G-element<br>
B1      (0.8.0)     Characteristic color B-element<br>
CD1     (-.8.-)     Arbitrary 8-bit data<br>
</code></pre>
Internal operations:<br>
See Data #22: RGB2.<br>
<br>
<b>Register number: Data #22</b>

Register name: RGB2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                             16 15                              0<br>
     -------------------------------------------------------------------<br>
    |CD2             |B2              |G2              |R2              |<br>
     -------------------------------------------------------------------<br>
<br>
Fields:<br>
R2      (0.8.0)     Characteristic color R-element<br>
G2      (0.8.0)     Characteristic color G-element<br>
B2      (0.8.0)     Characteristic color B-element<br>
CD2     (-.8.-)     Arbitrary 8-bit data<br>
</code></pre>
Internal operations:<br>
When several GTE instructions are executed, substitutions are made in the following sequence.<br>
<a href='https://code.google.com/p/pops-gte/source/detail?r=0'>R0</a> = <a href='https://code.google.com/p/pops-gte/source/detail?r=1'>R1</a>;<br>
<a href='https://code.google.com/p/pops-gte/source/detail?r=1'>R1</a> = <a href='https://code.google.com/p/pops-gte/source/detail?r=2'>R2</a>;<br>
<a href='https://code.google.com/p/pops-gte/source/detail?r=2'>R2</a> = RGB Register R-field<br>
G0 = G1;<br>
G1 = G2;<br>
G2 = RGB Register G-field<br>
B0 = B1;<br>
B1 = B2;<br>
B2 = RGB Register B-field<br>
CD0 = CD1;<br>
CD1 = CD2;<br>
CD2 = Bit pattern of GTE instruction currently being executed.<br>
<br>
<b>Register number: Data #23</b>

Register name: RES1<br>
Access: Prohibited<br>

<b>Register number: Data #24</b>

Register name: MAC0<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |MAC0                                                             |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
MAC0     (1.31.0)        Sum of products value #0<br>
</code></pre>

<b>Register number: Data #25</b>

Register name: MAC1<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |MAC1                                                             |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
MAC1     (1.31.0)        Sum of products value #1<br>
</code></pre>

<b>Register number: Data #26</b>

Register name: MAC2<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |MAC2                                                             |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
MAC2     (1.31.0)        Sum of products value #2<br>
</code></pre>

<b>Register number: Data #27</b>

Register name: MAC3<br>
Access: R/W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |MAC3                                                             |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
MAC3     (1.31.0)        Sum of products value #3<br>
</code></pre>

<b>Register number: Data #28</b>

Register name: IRGB<br>
Access: W<br>
Bit pattern:<br>
<pre><code>Bit  31                              15 14      10 9        5 4        0<br>
     -------------------------------------------------------------------<br>
    |                                  |IB        |IG        |IR        |<br>
     -------------------------------------------------------------------<br>
Fields:<br>
IR      (-.5.-)     Color data (R-element) to be set as intermediate value<br>
IG      (-.5.-)     Color data (G-element) to be set as intermediate value<br>
IB      (-.5.-)     Color data (B-element) to be set as intermediate value<br>
</code></pre>
Internal operations:<br>
The following processing is accomplished by writing data to this register.<br>
IR1 = The value which format-converted R to (1.11.4)<br>
IR2 = The value which format-converted G to (1.11.4)<br>
IR3 = The value which format-converted B to (1.11.4)<br>

<b>Register number: Data #29</b>

Register name: ORGB<br>
Access: W<br>
Bit pattern:<br>
<pre><code>Bit  31                              15 14      10 9        5 4        0<br>
     -------------------------------------------------------------------<br>
    |                                  |OB        |OG        |OR        |<br>
     -------------------------------------------------------------------<br>
Fields:<br>
OR      (-.5.-)     Color data generated from intermediate value (R-element)<br>
OG      (-.5.-)     Color data generated from intermediate value (G-element)<br>
OB      (-.5.-)     Color data generated from intermediate value (B-element)<br>
</code></pre>
Internal operations:<br>
By reading data from this register, the following operations are performed, including substitutions to each field.<br>
OR = (IR1>>7)&0x1f;<br>
OG = (IR2>>7)&0x1f;<br>
OB = (IR3>>7)&0x1f;<br>
The results obtained are then read.<br>

<b>Register number: Data #30</b>

Register name: LZCS<br>
Access: W<br>
Bit pattern:<br>
<pre><code>Bit  31                                                              0<br>
     -----------------------------------------------------------------<br>
    |LZCS                                                             |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LZCS     (1.31.0)        LZC source data<br>
</code></pre>
Internal operations:<br>
See Data #31: LZCR.<br>
<br>
<b>Register number: Data #31</b>

Register name: LZCR<br>
Access: R<br>
Bit pattern:<br>
<pre><code>Bit  31                                                 6 5          0<br>
     -----------------------------------------------------------------<br>
    |0                                                   |LZCR        |<br>
     -----------------------------------------------------------------<br>
Fields:<br>
LZCR     (0.6.0)        Leading zero/one count calculation result<br>
</code></pre>
Internal operations:<br>
By reading data from this register, the following operations are performed, including substitutions to each field.<br>
<br>
Data #30: If the value of LZCS is positive,<br>
LZCR = Leading zero count of LZCS value.<br>
<br>
Data #30: If the value of LZCS is negative,<br>
LZCR = Leading one count of LZCS value.<br>
The results obtained are then read.