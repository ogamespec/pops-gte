
This is code flow of GTE init procedure, called from Pops module_start.

The purpose of GTE init:

- Generate reciprocal table for RTPS/RTPT

- Load some constants to VFPU registers (used later in FLAG calculations)

- Load GTE FLAG value to the S330 VFPU register. S330 register is always aliased to GTE FLAG.


Also I added some disassembly of Pops init calls.
