@echo off
del main.exe

SET PSYQ_PATH=C:\PSYQ\BIN
set PATH=c:\PsyQ\BIN;%PATH%

ccpsx -O2 -c -Xo$80010000 main.c
ccpsx -O2 -c gte.c
asmpsx /l gte2.asm, gte2.obj
psylink /c /z @main.lnk,main.cpe
