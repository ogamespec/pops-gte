# Introduction #

Pops use static address assignment to major emu variables, such as registers, memory buffers and tables.


# Details #

Some big structure related to PSX CPU registers is resided at address **0x00010000**:<br>
Size of this structure is 0x22C bytes.<br>
<table><thead><th><b>offset</b></th><th><b>description</b></th></thead><tbody>
<tr><td>+0x0000</td><td>GTE Data Registers</td></tr>
<tr><td>+0x0080</td><td>GTE Control Registers</td></tr>
<tr><td>+0x0100</td><td>COP0 Registers</td></tr>
<tr><td>+0x0208</td><td>Program Counter</td></tr>
<tr><td>+0x0214</td><td>Cycle Counter ?</td></tr></tbody></table>

RTPS/RTPT generated reciprocal table is located at <b>0x000F198C</b>, 0x8000 32-bit words.<br>
<br>
At <b>0x09800000</b> located 2 MB of PSX RAM buffer<br>
<br>
At <b>0x00013000</b> located 1024 byte Scratch Pad<br>
<br>
<h2>MDEC</h2>

<b>0x13400</b> : quantization table. Format :<br>
<pre><code>{<br>
    float   y;<br>
    float   uv;<br>
} [64];<br>
</code></pre>

<b>0x0002D500</b> : quantization scale table. 64 halfwords:<br>
<pre><code>        8000 B18B  B18B A73D  F642 A73D  E7F8 9683   <br>
        E7F8 9683  8000 D0C4  DA82 D0C4  6492 8000   <br>
        B18B C4A7  C4A7 B18B  6492 4546  8B7E A73D  <br>
        B0FC A73D  8B7E 4546  2351 6016  8366 9683  <br>
        9683 8366  6016 2351  30FC 5A82  7642 8000  <br>
        7642 5A82  30FC 2E24  5175 6492  6492 5175  <br>
        2E24 2987  4546 4F04  4546 2987  2351 366D  <br>
        366D 2351  1BBF 257E  1BBF 131D  131D 09BE  <br>
</code></pre>
(already "zigzag"-ed)