# Overview #

<img src='http://ogamespec.com/imgstore/whc4e032dbd75870.jpg'>

Reverse engineering of <code>PlayStation</code> CPU GTE.<br>
<br>
<s>The aim of this project is full discovery how Pops emulating GTE and write own port for some of freeware Sony <code>PlayStation</code> emulators (e.g. Pcsx).</s> <b>DEPRECATED</b>

Since Pops is buggy shit, new goal is: drop acid on PSX CPU, microscope it, find GTE, recover standard cells and study its logic layout.<br>
<br>
GTE was always kind of mystery for PSX emu authors, now we have a chance to look how it was made of silicon.<br>
<br>
Overall progress:<br>
- Decap CPU <b>DONE</b><br>
- Microscope top metal layer (M2) on 20x zoom <b>DONE</b><br>
- Microscope bottom metal layer (M1) <b>DONE</b><br>
- Trace both metal layers<br>
- Delayer metal and microscope diffusion layer <b>DONE</b><br>
- Trace diffusion <b>DONE</b><br>
- Find all combinations of standard cells <b>DONE</b><br>
- Locate GTE <b>DONE</b><br>
- Restore GTE logic circuit<br>

<h1>News</h1>

13 sep 2013:<br>
CPU was delayered and imaged on 40x. Now we have to stitch 2900 image pieces (8.5 GB of data) and recover CPU Standard cells %) <br>
<img src='http://wiki.psxdev.ru/images/4/4f/Cells.jpg' /><br>
<img src='http://wiki.psxdev.ru/images/a/ae/Cellblock.jpg' />

2 jun 2013:<br>
Starting to stitch 850 pieces on 20x zoom.<br>
<br>
27 may 2013: Sony, squeeze your rolls :P Here we go!<br>
<img src='http://ogamespec.com/imgstore/whc51a3124a21d97.jpg'> <br>
Waves to <a href='http://zeptobars.ru'>http://zeptobars.ru</a> for high-resolution PSX CPU images.<br>
<br>
15 oct 2012: I captured PSX CPU die photo, wow :P<br>
<img src='http://ogamespec.com/imgstore/whc51a31241062f2.jpg'>

1 feb 2012: Pwned GTE divider, used in RTPS/RTPT. See wiki. Also uploaded gte_divider.h in source tree.<br>
<br>
24 aug 2011: Uploaded GTECheck. This small program is used to test GTE instructions on the real hardware.<br>
+ discovered that Pops has bug in <a href='AVSZ3.md'>AVSZ3</a> emulation (see wiki)<br>
<br>
21 jul 2011: GTETest is reported to be working on real hardware! Thanks to edgbla :) You can grab latest version on SVN.<br>
<br>
20 jul 2011: Found strange thing : DPCL and CDP instructions are swapped in opcode table. See details on "Bug_DPCL_CDP" wiki page.<br>
GTETest now uploaded to the repo + I found that GTE instructions opcode decoding in Disasm.c was a bit wrong :=)  (OP2 instruction field).<br>
<br>
18 jul 2011: GTETest is reported to be not working on real hardware. Still available from downloads though. DPCS disassembled. Found bug in vi2uc.q instruction in prxtool (I already fixed disassembly listings where it was occured). Some small corrections here and there.<br>
<br>
23 jun 2011: DCPL was mistyped. It should be <b>DPCL</b>. Small program for PSX was uploaded (GTETest)<br>
<br>
24 jun 2011: Added some MDEC reversing by unknown reason<br>
<br>
25 jun 2011: Added cool project logo. Tell me, if you have hires microscoped PSX-CPU image, I want to use it as logo.<br>
<br>
<h1>Credits</h1>

Credits go to old scene members:<br>
- Doomed/Padua: first complete GTE documentation. Where did you get it guys? o_O <b><code>[now I know hehe]</code></b><br>
- Groepaz/Hitmen: for valuable help with VFPU instructions<br>
- Tyranid: for prxtool<br>
- Pcsx team: good testing framework, nah, and for the best opensource PSX emu :P<br>
- Anonymous contributor for the convudendual <code>Inlinref.pdf</code> "Inline Programming Reference"<br>
<br>
(c) org, 2011, 2012<br>
<br>
Contact:<br>
email: ogamespec at gmail.com<br>
Skype: ogamespec
