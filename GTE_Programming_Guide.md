# GTE Programming Guide #

This is confidential information from PlayStation devkit. Thanks to anonymous contributor.

## Format ##
GTE is a vector/matrix processor implemented as "coprocessor 2" under the MIPS architecture
specification. The data format it handles consists of fixed decimal (fractional) real numbers.

## Registers ##
Coprocessors in the MIPS architecture can have two sets of registers: "data registers" and "control
registers". GTE has 32 data registers and 32 control registers. These are all 32-bit registers, and access by
the CPU is performed in register units. However, some registers are divided into multiple 8- or 16-bit fields.
Only GTE registers are referenced or changed when GTE is performing calculations.
For a detailed description of the various registers, refer to the "GTE Register Specification".

## Register Access Instructions ##
Data is transferred between GTE registers and CPU registers, or GTE registers and main memory (including
the scratchpad) by executing the CPU instructions listed below.
|CPU Instruction|Source|Destination|
|:--------------|:-----|:----------|
| **lwc2** |Memory scratchpad|GTE data register|
| **swc2** |GTE data register|Memory scratchpad|
| **mtc2** |CPU general-purpose register|GTE data register|
| **mfc2** |GTE data register|CPU general-purpose register|
| **ctc2** |CPU general-purpose register|GTE control register|
| **cfc2** |GTE control register|CPU general-purpose register|

The instructions mtc2, mfc2, ctc2, and cfc2 transfer data between registers. However, as is the case for
on-cache memory accesses, delayed loads should be used. In examples such as those listed below, nop
should be inserted into the delay slot.<br>
Example 1:<br>
<pre><code>cfc2 v0,C2_FLAG<br>
and v0,v0,v1 # No good<br>
</code></pre>
Example 2:<br>
<pre><code>cfc2 v0,C2_FLAG<br>
nop # delay slot<br>
and v0,v0,v1<br>
</code></pre>

<h2>Register Names</h2>
The macro definition of GTE register names can be found in the include header file "gtereg.h", which is part<br>
of the PlayStation library. The names of the macros are formed by adding the prefix "C2<code>_</code>" to the register<br>
names used in the "GTE Register Specification".<br>
<table><thead><th>Register number</th><th>Data register</th><th>Control register</th></thead><tbody>
<tr><td>0 </td><td><code>C2_VXY0</code></td><td><code>C2_R11R12</code></td></tr>
<tr><td>1 </td><td><code>C2_VZ0</code></td><td><code>C2_R13R21</code></td></tr>
<tr><td>2 </td><td><code>C2_VXY1</code></td><td><code>C2_R22R23</code></td></tr>
<tr><td>3 </td><td><code>C2_VZ1</code></td><td><code>C2_R31R32</code></td></tr>
<tr><td>4 </td><td><code>C2_VXY2</code></td><td><code>C2_R33</code></td></tr>
<tr><td>5 </td><td><code>C2_VZ2</code></td><td><code>C2_TRX</code></td></tr>
<tr><td>6 </td><td><code>C2_RGB</code></td><td><code>C2_TRY</code></td></tr>
<tr><td>7 </td><td><code>C2_OTZ</code></td><td><code>C2_TRZ</code></td></tr>
<tr><td>8 </td><td><code>C2_IR0</code></td><td><code>C2_L11L12</code></td></tr>
<tr><td>9 </td><td><code>C2_IR1</code></td><td><code>C2_L13L21</code></td></tr>
<tr><td>10</td><td><code>C2_IR2</code></td><td><code>C2_L22L23</code></td></tr>
<tr><td>11</td><td><code>C2_IR3</code></td><td><code>C2_L31L32</code></td></tr>
<tr><td>12</td><td><code>C2_SXY0</code></td><td><code>C2_L33</code></td></tr>
<tr><td>13</td><td><code>C2_SXY1</code></td><td><code>C2_RBK</code></td></tr>
<tr><td>14</td><td><code>C2_SXY2</code></td><td><code>C2_GBK</code></td></tr>
<tr><td>15</td><td><code>C2_SXYP</code></td><td><code>C2_BBK</code></td></tr>
<tr><td>16</td><td><code>C2_SZ0</code></td><td><code>C2_LR1LR2</code></td></tr>
<tr><td>17</td><td><code>C2_SZ1</code></td><td><code>C2_LR3LG1</code></td></tr>
<tr><td>18</td><td><code>C2_SZ2</code></td><td><code>C2_LG2LG3</code></td></tr>
<tr><td>19</td><td><code>C2_SZ3</code></td><td><code>C2_LB1LB2</code></td></tr>
<tr><td>20</td><td><code>C2_RGB0</code></td><td><code>C2_LB3</code></td></tr>
<tr><td>21</td><td><code>C2_RGB1</code></td><td><code>C2_RFC</code></td></tr>
<tr><td>22</td><td><code>C2_RGB2</code></td><td><code>C2_GFC</code></td></tr>
<tr><td>23</td><td> <i>Undefined</i> </td><td><code>C2_BFC</code></td></tr>
<tr><td>24</td><td><code>C2_MAC0</code></td><td><code>C2_OFX</code></td></tr>
<tr><td>25</td><td><code>C2_MAC1</code></td><td><code>C2_OFY</code></td></tr>
<tr><td>26</td><td><code>C2_MAC2</code></td><td><code>C2_H</code></td></tr>
<tr><td>27</td><td><code>C2_MAC3</code></td><td><code>C2_DQA</code></td></tr>
<tr><td>28</td><td><code>C2_IRGB</code></td><td><code>C2_DQB</code></td></tr>
<tr><td>29</td><td><code>C2_ORGB</code></td><td><code>C2_ZSF3</code></td></tr>
<tr><td>30</td><td><code>C2_LZCS</code></td><td><code>C2_ZSF4</code></td></tr>
<tr><td>31</td><td><code>C2_LZCR</code></td><td><code>C2_FLAG</code></td></tr></tbody></table>

<h2>Commands</h2>
GTE can perform an entire series of calculations essential for graphics programming (such as coordinate<br>
transformation, perspective transformation, and light source calculation) by executing a single command.<br>
Also, general-purpose matrix and vector calculations (such as matrix calculation, outer product, and<br>
interpolation) are available as commands. In all of the above cases, the calculation speed is several times<br>
faster than if the calculations in question were performed by the CPU.<br>
Refer to the "GTE Command Reference" for a detailed description of the available GTE commands. Also,<br>
GTE commands are macro defined in the file "inline.h", which is included with DMPSX.<br>
<br>
<h2>Delay Slots</h2>
CPU instructions that execute coprocessor 2 commands (referred to as "cop2"), require two delay slots for<br>
preceding GTE-related instructions.<br>
Example 3:<br>
<pre><code>mtc2 v0,C2_VXY0<br>
nop # delay slot<br>
nop # delay slot<br>
RTPS<br>
</code></pre>

<h2>Command Execution Cycles</h2>
The various GTE commands require the number of cycles listed below to complete. After a coprocessor 2<br>
execute instruction is issued, if the prescribed number of cycles is not left open, and either a GTE register<br>
read instruction (swc2, mfc2, cfc2) or another coprocessor 2 command execute instruction is issued, the<br>
CPU will stall until the initial coprocessor 2 instruction has completed execution.<br>
Example 4:<br>
<pre><code>RTPS<br>
## interlock ] &lt;- 15 cycles<br>
cfc2 v0,C2_FLAG<br>
</code></pre>
Example 5:<br>
<pre><code>RTPS<br>
add v1,v2,v3  -|<br>
sub v1,v2,v3   |&lt;- 15 cycles<br>
## interlock  -|<br>
cfc2 v0,C2_FLAG<br>
</code></pre>

<h2>Coding Limitations</h2>
<ol><li>A GTE instruction (cop2) must not be executed in an event handler or callback function.<br>
</li><li>A GTE instruction (cop2) must not be inserted into the delay slot following a jump or branch instruction.<br>
</li><li>A GTE register access instruction (lwc2, swc2, mtc2, mfc2, ctc2, cfc2) must not be inserted into the delay slot following a jump or branch command.<br>
</li><li>A GTE register load instruction (lwc2, mtc2, ctc2) must not be used between a GTE instruction (cop2) and a GTE register save instruction (swc2, mfc2, cfc2) or between a GTE instruction (cop2) and another GTE instruction (cop2).<br>
Example 6:<br>
<pre><code>/* cop2-load-save (NG) */<br>
RTPS            /* cop2 */<br>
                /* cpu instructions */<br>
mtc2 v0,C2_VXY0 /* NG !!!!!! */<br>
                /* cpu instructions */<br>
cfc2 v0,C2_FLAG /* save instruction */<br>
</code></pre>
Example 7:<br>
<pre><code>/* cop2-load-cop2 (NG) */<br>
RTPT            /* cop2 */<br>
                /* cpu instructions */<br>
mtc2 v0,C2_VXY0 /* NG !!!!!! */<br>
                /* cpu instructions */<br>
NCLIP           /* cop2 */<br>
</code></pre>
</li></ol><blockquote>5. If a GTE register to which data is to be loaded is not being referenced or overwritten by a GTE command that is currently executing, it is possible to execute a command which transfers data to the GTE register without worrying about the GTE command (cop2).<br>
Example 8:<br>
<pre><code>/* cop2-load-save (OK) */<br>
RTPS            /* cop2 */<br>
                /* cpu instructions */<br>
mtc2 v0,C2_VXY1 /* OK !! */<br>
                /* cpu instructions */<br>
cfc2 v0,C2_FLAG /* save instruction */<br>
</code></pre>
Example 9:<br>
<pre><code>/* cop2-load-cop2 (OK) */<br>
RTPT           /* cop2 */<br>
               /* cpu instructions */<br>
mtc2 v0,C2_RGB /* OK !! */<br>
               /* cpu instructions */<br>
NCLIP          /* cop2 */<br>
</code></pre></blockquote>

<h2>Recommended Development Style</h2>
When coding in assembler, programs that violate some of the above rules may appear to run properly at<br>
first glance. However, such violations tend to become evident as bugs that are extremely difficult to track<br>
down, such as incorrect operation during an interrupt. For this reason, programmers are advised to avoid<br>
coding directly in assembler as much as possible.<br>
To prevent bad code from being generated, the following development sequence should be used.<br>
C (libgte) -> C (DMPSX) -> Assembler (DMPSX)