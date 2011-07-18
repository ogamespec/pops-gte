
This is raw unprocessed disassembly of emulated GTE instructions, ripped from Pops executable.

Reversed pseudo-source code is located in cooked dir.

Some notes:

- prxtool has msub bug (discovered here: http://www.psp-programming.com/forums/index.php?topic=4969.0)
  I replaced all buggy msub disassembly with proper one.

  EDIT: vi2uc.q also buggy. I fixed disassembly manually.

- RTPS contained inside RTPT

- Disassembly of MoveFrom / MoveTo GTE register instructions are missed.

- Final calculation of GTE FLAG (sum) is also not detected yet.
