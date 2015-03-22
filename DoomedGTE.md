
```
==========================================================================
GTE.txt - Documentation & Explanation.
==========================================================================


Disclaimer.
--------------------------------------------------------------------------
This document is a collection of all info on the GTE i could find and my
own notes. Most of this is the result of experiment, so not all info might
be correct. This document is most probably not complete, and not all
capabilities and quirks of the GTE are documented. No responsibility is
taken for anything that might occur using the information in this document.


--------------------------------------------------------------------------
Introduction.
--------------------------------------------------------------------------
The Geometry Transformation Engine (GTE) is the heart of all 3d
calculations on the psx. The GTE has specialised functions for perspective
transformations, light sourcing and the like, and is much faster than the
CPU on these operations. It is mounted as the second coprocessor and as
such has no physical address in the memory of the psx. All control is done
through special instructions.


--------------------------------------------------------------------------
Basic mathematics
--------------------------------------------------------------------------
The GTE is basicly an engine for vector mathematics, so some knowledge
of that area is vital for correct usage of the GTE. I will not delve to
deeply in that area, as that's beyond the scope of this text, but i'll
introduce some concepts.


The basic representation of a point(vertex) in 3d space is through a vector
of the sort [X,Y,Z]. In GTE operation there's basicly two kinds of these,
vectors of variable length and vectors of a unit length of 1.0, called
normal vectors. The first is used to decribe a locations and translations
in 3d space, the second to describe a direction.


Rotation of vertices is performed by multiplying the vector of the vertex
with a rotation matrix. The rotation matrix is a 3x3 matrix consisting of
3 normal vectors which are orthogonal to each other. (It's actually the
matrix which describes the coordinate system in which the vertex is located
in relation to the unit coordinate system. See a maths book for more
details.) This matrix is derived from rotation angles as follows:


(s? = sin(?), c? = cos(?))


Rotation angle A   Rotation angle B    Rotation angle C
about X axis:      about Y axis:       about Z axis:


|  1   0   0|       | cB   0  sB|        | cC -sC   0|
|  0  cA -sA|       |  0   1   0|        | sC  cC   0|
|  0  sA  cA|       |-sB   0  cB|        |  0   0   1|


Rotation about multiple axis can be done by multiplying these matrices
with eachother. Note that the order in which this multiplication is done
*IS* important. The GTE has no sine or cosine functions, so the calculation
of these must be done by the CPU.


Translation is the simple addition of two vectors, relocating the vertex
within its current coordinate system. Needless to say the order in which
translation and rotation occur for a vector is important.


--------------------------------------------------------------------------
Brief Function descriptions
--------------------------------------------------------------------------
RTPS/RTPT         Rotate, translate and perpective transformation.


These two functions perform the final 3d calculations on one or three
vertices at once. The points are first multiplied with a rotation matrix(R),
and after that translated(TR). Finally a perspective transformation is
applied, which results in 2d screen coordinates. It also returns an
interpolation value to be used with the various depth cueing instructions.
--------------------------------------------------------------------------
MVMVA             Matrix & Vector multiplication and addition.


Multiplies a vector with either the rotation matrix, the light matrix or
the color matrix and then adds the translation vector or background color
vector.
--------------------------------------------------------------------------
DCPL              Depth cue light color


First calculates a color from a light vector(normal vector of a plane
multiplied with the light matrix and zero limited) and a provided RGB value.
Then performs depth cueing by interpolating between the far color vector and
the newfound color.
--------------------------------------------------------------------------
DPCS/DPCT         Depth cue single/triple


Performs depth cueing by interpolating between a color and the far color
vector on one or three colors.
--------------------------------------------------------------------------
INTPL             Interpolation


Interpolates between a vector and the far color vector.
--------------------------------------------------------------------------
SQR               Square


Calculates the square of a vector.
--------------------------------------------------------------------------
NCS/NCT           Normal Color


Calculates a color from the normal of a point or plane and the light
sources and colors. The basic color of the plane or point the normal
refers to is assumed to be white.
--------------------------------------------------------------------------
NCDS/NCDT         Normal Color Depth Cue.


Same as NCS/NCT but also performs depth cueing (like DPCS/DPCT)
--------------------------------------------------------------------------
NCCS/NCCT


Same NCS/NCT, but the base color of the plane or point is taken into
account.
--------------------------------------------------------------------------
CDP


A color is calculated from a light vector (base color is assumed to be
white) and depth cueing is performed (like DPCS).
--------------------------------------------------------------------------
CC


A color is calculated from a light vector and a base color.
--------------------------------------------------------------------------
NCLIP


Calculates the outer product of three 2d points.(ie. 3 vertices which
define a plane after projection.)


The 3 vertices should be stored clockwise according to the visual point:


          Z+
         /
       /____ X+
       |
       |
        Y+


If this is so, the result of this function will be negative if we are
facing the backside of the plane.
--------------------------------------------------------------------------
AVSZ3/AVSZ4


Adds 3 or 4 z values together and multplies them by a fixed point value.
This value is normally chosen so that this function returns the average
of the z values (usually further divided by 2 or 4 for easy adding to the
OT)
--------------------------------------------------------------------------
OP


Calculates the outer product of 2 vectors.
--------------------------------------------------------------------------
GPF


Multiplies 2 vectors. Also returns the result as 24bit rgb value.
--------------------------------------------------------------------------
GPL


Multiplies a vector with a scalar and adds the result to another vector.
Also returns the result as 24bit rgb value.


--------------------------------------------------------------------------
GTE Operation.
--------------------------------------------------------------------------
Instructions.
--------------------------------------------------------------------------
The CPU has six special load and store instructions for the GTE registers,
and an instruction to issue commands to the coprocessor.


rt        CPU register 0-31
gd        GTE data register 0-31
gc        GTE control register 0-31
imm       16 bit immediate value
base      CPU register 0-31
imm(base) address pointed to by base + imm.
b25       25 bit wide data field.


LWC2  gd, imm(base)   stores value at imm(base) in gte data register gd.
SWC2  gd, imm(base)   stores gte data register at imm(base).
MTC2  rt, gd          stores register rt in GTE data register gd.
MFC2  rt, gd          stores GTE data register gd in register rt.
CTC2  rt, gc          stores register rt in GTE control register gc.
CFC2  rt, gc          stores GTE control register in register rt.


COP2  b25             Issues a GTE command.


Gte load and store instructions have a delay of 2 instructions, for any
gte commands or operations accessing that register.


--------------------------------------------------------------------------
Registers.
--------------------------------------------------------------------------
The GTE has 32 data registers, and 32 control registers,each 32 bits wide.
The following list describes their common use and format. Note in some
functions format is different from the one that's given here. The numbers
in the format fields are the signed, integer and fractional parts of the
field. So 1,3,12 means signed(1 bit), 3 bits integral part, 12 bits
fractional part.


Control registers:
No. Name    |31-24 23-16|15-08 07-01| Description
 0  R11R12  |R12 1, 3,12|R11 1, 3,12| Rotation matrix elements 11, 12
 1  R13R21  |R21 1, 3,12|R13 1, 3,12| Rotation matrix elements 13, 21
 2  R22R23  |R23 1, 3,12|R22 1, 3,12| Rotation matrix elements 22, 23
 3  R31R32  |R32 1, 3,12|R31 1, 3,12| Rotation matrix elements 31, 32
 4  R33     |          0|R33 1, 3,12| Rotation matrix element 33
 5  TRX     |TRX 1,31, 0            | Translation vector X
 6  TRY     |TRY 1,31, 0            | Translation vector Y
 7  TRZ     |TRZ 1,31, 0            | Translation vector Z
 8  L11L12  |L12 1, 3,12|L11 1, 3,12| Light source matrix elements 11, 12
 9  L13L21  |L21 1, 3,12|L13 1, 3,12| Light source matrix elements 13, 21
10  L22L23  |L23 1, 3,12|L22 1, 3,12| Light source matrix elements 22, 23
11  L31L32  |L32 1, 3,12|L31 1, 3,12| Light source matrix elements 31, 32
12  L33     |          0|L33 1, 3,12| Light source matrix element 33
13  RBK     |RBK 1,19,12            | Background color red component.
14  GBK     |GBK 1,19,12            | Background color green component.
15  BBK     |RBK 1,19,12            | Background color blue component.
16  LR1LR2  |LR2 1, 3,12|LR1 1, 3,12| Light color matrix source 1&2 red comp.
17  LR3LG1  |LG1 1, 3,12|LR3 1, 3,12| Light color matrix source 3 red, 1 green
18  LG2LG3  |LG3 1, 3,12|LG2 1, 3,12| Light color matrix source 2&3 green comp.
19  LB1LB2  |LB2 1, 3,12|LB1 1, 3,12| Light color matrix source 1&2 blue comp.
20  LB3     |          0|LB3 1, 3,12| Light color matrix source 3 blue component.
21  RFC     |RFC 1,27, 4            | Far color red component.
22  GFC     |GFC 1,27, 4            | Far color green component.
23  BFC     |BFC 1,27, 4            | Far color blue component.
24  OFX     |OFX 1,15,16            | Screen offset X
25  OFY     |OFY 1,15,16            | Screen offset Y
26  H       |          0|H   0,16, 0| Projection plane distance.
27  DQA     |          0|DQA 1, 7, 8| Depth queing parameter A.(coefficient.)
28  DQB     |          0|DQB 1, 7,24| Depth queing parameter B.(offset.)
29  ZSF3    |          0|ZSF3 1,3,12| Z3 average scale factor (normally 1/3)
30  ZSF4    |          0|ZSF4 1,3,12| Z4 average scale factor (normally 1/4)
31  FLAG    |See gte funcions       | Returns any calculation errors.


Data registers:
No. Name  rw|31-24 23-16|15-08 07-01| Description
 0  VXY0  rw|VY0        |VX0        | Vector 0 X and Y. 1,3,12 or 1,15,0
 1  VZ0   rw|          0|VZ0        | Vector 0 Z.
 2  VXY1  rw|VY1        |VX1        | Vector 1 X and Y. 1,3,12 or 1,15,0
 3  VZ1   rw|          0|VZ1        | Vector 1 Z.
 4  VXY2  rw|VY2        |VX2        | Vector 2 X and Y. 1,3,12 or 1,15,0
 5  VZ2   rw|          0|VZ2        | Vector 2 Z.
 6  RGB   rw|Code |B    |G    |R    | Rgb value. Code is passed, but not used in calc.
 7  OTZ   r |           |OTZ 0,15, 0| Z Average value.
 8  IR0   rw|Sign       |IR0 1, 3,12| Intermediate value 0. *1
 9  IR1   rw|Sign       |IR0 1, 3,12| Intermediate value 1. *1
10  IR2   rw|Sign       |IR0 1, 3,12| Intermediate value 2. *1
11  IR3   rw|Sign       |IR0 1, 3,12| Intermediate value 3. *1
12  SXY0  rw|SY0 1,15, 0|SX0 1,15, 0| Screen XY coordinate fifo. *2
13  SXY1  rw|SY1 1,15, 0|SX1 1,15, 0|
14  SXY2  rw|SY2 1,15, 0|SX2 1,15, 0|
15  SXYP  rw|SYP 1,15, 0|SXP 1,15, 0|
16  SZ0   rw|          0|SZ0 0,16, 0| Screen Z fifo. *2
17  SZ1   rw|          0|SZ1 0,16, 0|
18  SZ2   rw|          0|SZ2 0,16, 0|
19  SZ3   rw|          0|SZ3 0,16, 0|
20  RGB0  rw|CD0  |B0   |G0   |R0   | Characteristic color fifo. *2
21  RGB1  rw|CD1  |B1   |G1   |R1   |
22  RGB2  rw|CD2  |B2   |G2   |R2   | CD2 is the bit pattern of currently executed function
23 (RES1)   |                       | Prohibited
24  MAC0  rw|MAC0 1,31,0            | Sum of products value 0
25  MAC1  rw|MAC1 1,31,0            | Sum of products value 1
26  MAC2  rw|MAC2 1,31,0            | Sum of products value 2
27  MAC3  rw|MAC3 1,31,0            | Sum of products value 3
28  IRGB   w|           |IB |IG |IR | *3
29  ORGB  r |           |OB |OG |OR | *4
30  LZCS   w|LZCS 1,31,0            | Leading zero count source data.*5
31  LZCR  r |LZCR 0,6,0             | Leading zero count result.*5


*1) The specified format is the format which GTE functions output to these
    registers. The input format is mostly (1,19,12)


*2) The SXYx, SZx and RGBx are first in first out registers (fifo). The last
    calculation result is stored in the last register, and previous results
    are stored in previous registers. So for example when a new SXY value
    is obtained the following happens:
    SXY0 = SXY1
    SXY1 = SXY2
    SXY2 = SXYP
    SXYP = result.


*3) IRGB:
    |31        15|14-10| 9- 5| 4- 0|
    |           0|IR   |IG   |IB   |
    When writing a value to IRGB the following happens:
    IR1 = IR format converted to (1,11,4)
    IR2 = IG format converted to (1,11,4)
    IR3 = IB format converted to (1,11,4)


*4) ORGB:
    |31        15|14-10| 9- 5| 4- 0|
    |           0|IR   |IG   |IB   |
    When writing a value to IRGB the following happens:
    IR = (IR1>>7) &$1f
    IG = (IR2>>7) &$1f
    IB = (IR3>>7) &$1f
*5) Reading LZCR returns the leading 0 count of LZCS if LZCS is positive
    and the leading 1 count of LZCS if LZCS is negative.


--------------------------------------------------------------------------
Programming Considerations.
--------------------------------------------------------------------------
Before use the GTE must be turned on. The GTE has bit 30 allocated to it in
the status register of the stystem control coprocessor (cop0). Before any
GTE instruction is used, this bit must be set.


GTE instructions and functions should not be used in
- Delay slots of jumps and branches
- Event handlers or interrupts.


If an instruction that reads a GTE register or a GTE command is executed
before the current GTE command is finished, the cpu will hold until the
instruction has finished. The number of cycles each GTE instruction takes
is in the command list.


--------------------------------------------------------------------------
Function Operation.
--------------------------------------------------------------------------
This part describes the actual calculations performed by the various GTE
functions. The first line contains the name of the function, the number
of cycles it takes and a brief description. The second line any fields that
may be set in the opcode and in the third line is the actual opcode. See
the end of the list for the fields and their descriptions. Then follows a
list of all registers which are needed in the calculation under the 'in',
and a list of registers which modified under the 'out' with a brief
description and the format of the data. Next follows the calculation which
is performed after initiating the function. The format field left is the
size in which the data is stored, the format field on the right contains
the format in which the calculation is performed. At certain points in the
calculation checks and limitations are done and their results stored in the
flag register, see the table below. They are identified with the code from
the second column of the table directly followed by square brackets
enclosing the part of the calculation on which the check is performed. The
additional Lm_ identifier means the value is limited to the bottom or
ceiling of the check if it exceeds the boundary.


bit      description
31       Checksum.
30  A1   Result larger than 43 bits and positive
29  A2   Result larger than 43 bits and positive
28  A3   Result larger than 43 bits and positive
27  A1   Result larger than 43 bits and negative
26  A2   Result larger than 43 bits and negative
25  A3   Result larger than 43 bits and negative
24  B1   Value negative(lm=1) or larger than 15 bits(lm=0)
23  B2   Value negative(lm=1) or larger than 15 bits(lm=0)
22  B3   Value negative(lm=1) or larger than 15 bits(lm=0)
21  C1   Value negative or larger than 8 bits.
20  C2   Value negative or larger than 8 bits.
19  C3   Value negative or larger than 8 bits.
18  D    Value negative or larger than 16 bits.
17  E    Divide overflow. (quotient > 2.0)
16  F    Result larger than 31 bits and positive.
15  F    Result larger than 31 bits and negative.
14  G1   Value larger than 10 bits.
13  G2   Value larger than 10 bits.
12  H    Value negative or larger than 12 bits.




--------------------------------------------------------------------------
RTPS     15       Perspective transformation          
Fields:  none
Opcode:  cop2 $0180001


In:      V0       Vector to transform.                         [1,15,0]
         R        Rotation matrix                              [1,3,12]
         TR       Translation vector                           [1,31,0]
         H        View plane distance                          [0,16,0]
         DQA      Depth que interpolation values.              [1,7,8]
         DQB                                                   [1,7,8]
         OFX      Screen offset values.                        [1,15,16]
         OFY                                                   [1,15,16]
Out:     SXY fifo Screen XY coordinates.(short)                [1,15,0]
         SZ fifo  Screen Z coordinate.(short)                  [0,16,0]
         IR0      Interpolation value for depth queing.        [1,3,12]
         IR1      Screen X (short)                             [1,15,0]
         IR2      Screen Y (short)                             [1,15,0]
         IR3      Screen Z (short)                             [1,15,0]
         MAC1     Screen X (long)                              [1,31,0]
         MAC2     Screen Y (long)                              [1,31,0]
         MAC3     Screen Z (long)                              [1,31,0]


Calculation:
[1,31,0] MAC1=A1[TRX + R11*VX0 + R12*VY0 + R13*VZ0]            [1,31,12]
[1,31,0] MAC2=A2[TRY + R21*VX0 + R22*VY0 + R23*VZ0]            [1,31,12]
[1,31,0] MAC3=A3[TRZ + R31*VX0 + R32*VY0 + R33*VZ0]            [1,31,12]
[1,15,0] IR1= Lm_B1[MAC1]                                      [1,31,0]
[1,15,0] IR2= Lm_B2[MAC2]                                      [1,31,0]
[1,15,0] IR3= Lm_B3[MAC3]                                      [1,31,0]
         SZ0<-SZ1<-SZ2<-SZ3
[0,16,0] SZ3= Lm_D(MAC3)                                       [1,31,0]
         SX0<-SX1<-SX2, SY0<-SY1<-SY2
[1,15,0] SX2= Lm_G1[F[OFX + IR1*(H/SZ)]]                       [1,27,16]
[1,15,0] SY2= Lm_G2[F[OFY + IR2*(H/SZ)]]                       [1,27,16]
[1,31,0] MAC0= F[DQB + DQA * (H/SZ)]                           [1,19,24]
[1,15,0] IR0= Lm_H[MAC0]                                       [1,31,0]


Notes:
Z values are limited downwards at 0.5 * H. For smaller z values you'll have
write your own routine.
--------------------------------------------------------------------------
RTPT     23       Perspective Transformation on 3 points.
Fields   none
opcode   cop2 $0280030


in       V0       Vector to transform.                         [1,15,0]
         V1                                                    [1,15,0]
         V2                                                    [1,15,0]
         R        Rotation matrix                              [1,3,12]
         TR       Translation vector                           [1,31,0]
         H        View plane distance                          [0,16,0]
         DQA      Depth que interpolation values.              [1,7,8]
         DQB                                                   [1,7,8]
         OFX      Screen offset values.                        [1,15,16]
         OFY                                                   [1,15,16]
out      SXY fifo Screen XY coordinates.(short)                [1,15,0]
         SZ fifo  Screen Z coordinate.(short)                  [0,16,0]
         IR0      Interpolation value for depth queing.        [1,3,12]
         IR1      Screen X (short)                             [1,15,0]
         IR2      Screen Y (short)                             [1,15,0]
         IR3      Screen Z (short)                             [1,15,0]
         MAC1     Screen X (long)                              [1,31,0]
         MAC2     Screen Y (long)                              [1,31,0]
         MAC3     Screen Z (long)                              [1,31,0]


Calculation: Same as RTPS, but repeats for V1 and V2.
--------------------------------------------------------------------------
MVMVA    8        Multiply vector by matrix and vector addition.
Fields:  sf,mx,v,cv,lm
Opcode:  cop2 $0400012


in:      V0/V1/V2/IR       Vector v0, v1, v2 or [IR1,IR2,IR3]
         R/LLM/LCM         Rotation, light or color matrix.    [1,3,12]
         TR/BK             Translation or background color vector.
out:     [IR1,IR2,IR3]     Short vector
         [MAC1,MAC2,MAC3]  Long vector


Calculation:
MX = matrix specified by mx
V = vector specified by v
CV = vector specified by cv




         MAC1=A1[CV1 + MX11*V1 + MX12*V2 + MX13*V3]
         MAC2=A2[CV2 + MX21*V1 + MX22*V2 + MX23*V3]
         MAC3=A3[CV3 + MX31*V1 + MX32*V2 + MX33*V3]
         IR1=Lm_B1[MAC1]
         IR2=Lm_B2[MAC2]
         IR3=Lm_B3[MAC3]


Notes:
The cv field allows selection of the far color vector, but this vector
is not added correctly by the GTE.
--------------------------------------------------------------------------
DCPL     8        Depth Cue Color light
Fields:  none
Opcode:  cop2 $0680029
In:      RGB               Primary color.         R,G,B,CODE   [0,8,0]
         IR0               interpolation value.                [1,3,12]
         [IR1,IR2,IR3]     Local color vector.                 [1,3,12]
         CODE              Code value from RGB.           CODE [0,8,0]
         FC                Far color.                          [1,27,4]
Out:     RGBn              RGB fifo               Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation:
[1,27,4]  MAC1=A1[R*IR1 + IR0*(Lm_B1[RFC - R * IR1])]          [1,27,16]
[1,27,4]  MAC2=A2[G*IR2 + IR0*(Lm_B1[GFC - G * IR2])]          [1,27,16]
[1,27,4]  MAC3=A3[B*IR3 + IR0*(Lm_B1[BFC - B * IR3])]          [1,27,16]
[1,11,4]  IR1=Lm_B1[MAC1]                                      [1,27,4]
[1,11,4]  IR2=Lm_B2[MAC2]                                      [1,27,4]
[1,11,4]  IR3=Lm_B3[MAC3]                                      [1,27,4]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
DPCS     8        Depth Cueing.
Fields:  none
Opcode:  cop2 $0780010


In:      IR0               Interpolation value                 [1,3,12]
         RGB               Color                  R,G,B,CODE   [0,8,0]
         FC                Far color              RFC,GFC,BFC  [1,27,4]
Out:     RGBn              RGB fifo               Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculations:
[1,27,4]  MAC1=A1[(R + IR0*(Lm_B1[RFC - R])]                   [1,27,16][lm=0]
[1,27,4]  MAC2=A2[(G + IR0*(Lm_B1[GFC - G])]                   [1,27,16][lm=0]
[1,27,4]  MAC3=A3[(B + IR0*(Lm_B1[BFC - B])]                   [1,27,16][lm=0]
[1,11,4]  IR1=Lm_B1[MAC1]                                      [1,27,4][lm=0]
[1,11,4]  IR2=Lm_B2[MAC2]                                      [1,27,4][lm=0]
[1,11,4]  IR3=Lm_B3[MAC3]                                      [1,27,4][lm=0]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
INTPL    8        Interpolation of a vector and far color vector.
Fields:  none
Opcode:  cop2 $0980011


In:      [IR1,IR2,IR3]     Vector                              [1,3,12]
         IR0               Interpolation value                 [1,3,12]
         CODE              Code value from RGB.           CODE [0,8,0]
         FC                Far color              RFC,GFC,BFC  [1,27,4]
Out:     RGBn              RGB fifo               Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculations:
[1,27,4]  MAC1=A1[IR1 + IR0*(Lm_B1[RFC - IR1])]                [1,27,16]
[1,27,4]  MAC2=A2[IR2 + IR0*(Lm_B1[GFC - IR2])]                [1,27,16]
[1,27,4]  MAC3=A3[IR3 + IR0*(Lm_B1[BFC - IR3])]                [1,27,16]
[1,11,4]  IR1=Lm_B1[MAC1]                                      [1,27,4]
[1,11,4]  IR2=Lm_B2[MAC2]                                      [1,27,4]
[1,11,4]  IR3=Lm_B3[MAC3]                                      [1,27,4]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
SQR      5        Square vector.
Fields:  sf
Opcode:  cop2 $0a00428
                                                       sf=0    sf=1
in:      [IR1,IR2,IR3]     vector                      [1,15,0][1,3,12]
out:     [IR1,IR2,IR3]     vector^2                    [1,15,0][1,3,12]
         [MAC1,MAC2,MAC3]  vector^2                    [1,31,0][1,19,12]


Calculation: (left format sf=0, right format sf=1)


[1,31,0][1,19,12] MAC1=A1[IR1*IR1]                     [1,43,0][1,31,12]
[1,31,0][1,19,12] MAC2=A2[IR2*IR2]                     [1,43,0][1,31,12]
[1,31,0][1,19,12] MAC3=A3[IR3*IR3]                     [1,43,0][1,31,12]
[1,15,0][1,3,12]  IR1=Lm_B1[MAC1]                      [1,31,0][1,19,12][lm=1]
[1,15,0][1,3,12]  IR2=Lm_B2[MAC2]                      [1,31,0][1,19,12][lm=1]
[1,15,0][1,3,12]  IR3=Lm_B3[MAC3]                      [1,31,0][1,19,12][lm=1]
--------------------------------------------------------------------------
NCS      14       Normal color
Fields:  none
Opcode:  cop2 $0C8041E


In:      V0                Normal vector                       [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         CODE              Code value from RGB.           CODE [0,8,0]
         LCM               Color matrix                        [1,3,12]
         LLM               Light matrix                        [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


[1,19,12] MAC1=A1[L11*VX0 + L12*VY0 + L13*VZ0]                 [1,19,24]
[1,19,12] MAC2=A2[L21*VX0 + L22*VY0 + L23*VZ0]                 [1,19,24]
[1,19,12] MAC3=A3[L31*VX0 + L32*VY0 + L33*VZ0]                 [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,19,12][lm=1]
[1,19,12] MAC1=A1[RBK + LR1*IR1 + LR2*IR2 + LR3*IR3]           [1,19,24]
[1,19,12] MAC2=A2[GBK + LG1*IR1 + LG2*IR2 + LG3*IR3]           [1,19,24]
[1,19,12] MAC3=A3[BBK + LB1*IR1 + LB2*IR2 + LB3*IR3]           [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,19,12][lm=1]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
NCT      30       Normal color
Fields:  none
Opcode:  cop2 $0D80420


In:      V0,V1,V2          Normal vector                       [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         CODE              Code value from RGB.           CODE [0,8,0]
         LCM               Color matrix                        [1,3,12]
         LLM               Light matrix                        [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation: Same as NCS, but repeated for V1 and V2.
--------------------------------------------------------------------------
NCDS     19       Normal color depth cue single vector
Fields:  none
Opcode:  cop2 $0e80413
In:      V0                Normal vector                       [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         RGB               Primary color          R,G,B,CODE   [0,8,0]
         LLM               Light matrix                        [1,3,12]
         LCM               Color matrix                        [1,3,12]
         IR0               Interpolation value                 [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation:
[1,19,12] MAC1=A1[L11*VX0 + L12*VY0 + L13*VZ0]                 [1,19,24]
[1,19,12] MAC2=A1[L21*VX0 + L22*VY0 + L23*VZ0]                 [1,19,24]
[1,19,12] MAC3=A1[L31*VX0 + L32*VY0 + L33*VZ0]                 [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,19,12][lm=1]
[1,19,12] MAC1=A1[RBK + LR1*IR1 + LR2*IR2 + LR3*IR3]           [1,19,24]
[1,19,12] MAC2=A1[GBK + LG1*IR1 + LG2*IR2 + LG3*IR3]           [1,19,24]
[1,19,12] MAC3=A1[BBK + LB1*IR1 + LB2*IR2 + LB3*IR3]           [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,19,12][lm=1]
[1,27,4]  MAC1=A1[R*IR1 + IR0*(Lm_B1[RFC-R*IR1])]              [1,27,16][lm=0]
[1,27,4]  MAC2=A1[G*IR2 + IR0*(Lm_B2[GFC-G*IR2])]              [1,27,16][lm=0]
[1,27,4]  MAC3=A1[B*IR3 + IR0*(Lm_B3[BFC-B*IR3])]              [1,27,16][lm=0]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,27,4][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,27,4][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,27,4][lm=1]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
NCDT     44       Normal color depth cue triple vectors
Fields:  none
Opcode:  cop2 $0f80416
In:      V0                Normal vector                       [1,3,12]
         V1                Normal vector                       [1,3,12]
         V2                Normal vector                       [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         FC                Far color              RFC,GFC,BFC  [1,27,4]
         RGB               Primary color          R,G,B,CODE   [0,8,0]
         LLM               Light matrix                        [1,3,12]
         LCM               Color matrix                        [1,3,12]
         IR0               Interpolation value                 [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation:
Same as NCDS but repeats for v1 and v2.
--------------------------------------------------------------------------
DPCT     17       Depth Cueing.
Fields:  none
Opcode:  cop2 $0F8002A


In:      IR0               Interpolation value                 [1,3,12]
         RGB0,RGB1,RGB2    Colors in RGB fifo.    Rn,Gn,Bn,CDn [0,8,0]
         FC                Far color              RFC,GFC,BFC  [1,27,4]
Out:     RGBn              RGB fifo               Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculations:
[1,27,4]  MAC1=A1[R0+ IR0*(Lm_B1[RFC - R0])]                   [1,27,16][lm=0]
[1,27,4]  MAC2=A2[G0+ IR0*(Lm_B1[GFC - G0])]                   [1,27,16][lm=0]
[1,27,4]  MAC3=A3[B0+ IR0*(Lm_B1[BFC - B0])]                   [1,27,16][lm=0]
[1,11,4]  IR1=Lm_B1[MAC1]                                      [1,27,4][lm=0]
[1,11,4]  IR2=Lm_B2[MAC2]                                      [1,27,4][lm=0]
[1,11,4]  IR3=Lm_B3[MAC3]                                      [1,27,4][lm=0]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]


Performs this calculation 3 times, so all three RGB values have been
replaced by the depth cued RGB values.


--------------------------------------------------------------------------
NCCS     17       Normal Color Color single vector
Fields:  none
Opcode:  cop2 $108041B


In:      V0                Normal vector                       [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         RGB               Primary color          R,G,B,CODE   [0,8,0]
         LLM               Light matrix                        [1,3,12]
         LCM               Color matrix                        [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation:


[1,19,12] MAC1=A1[L11*VX0 + L12*VY0 + L13*VZ0]                  [1,19,24]
[1,19,12] MAC2=A2[L21*VX0 + L22*VY0 + L23*VZ0]                  [1,19,24]
[1,19,12] MAC3=A3[L31*VX0 + L32*VY0 + L33*VZ0]                  [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                      [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                      [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                      [1,19,12][lm=1]
[1,19,12] MAC1=A1[RBK + LR1*IR1 + LR2*IR2 + LR3*IR3]            [1,19,24]
[1,19,12] MAC2=A2[GBK + LG1*IR1 + LG2*IR2 + LG3*IR3]            [1,19,24]
[1,19,12] MAC3=A3[BBK + LB1*IR1 + LB2*IR2 + LB3*IR3]            [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                      [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                      [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                      [1,19,12][lm=1]
[1,27,4]  MAC1=A1[R*IR1]                                        [1,27,16]
[1,27,4]  MAC2=A2[G*IR2]                                        [1,27,16]
[1,27,4]  MAC3=A3[B*IR3]                                        [1,27,16]
[1,3,12]  IR1= Lm_B1[MAC1]                                      [1,27,4][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                      [1,27,4][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                      [1,27,4][lm=1]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                              [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                              [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                              [1,27,4]
--------------------------------------------------------------------------
NCCT     39       Normal Color Color triple vector
Fields:  none
Opcode:  cop2 $118043F


In:      V0                Normal vector 1                     [1,3,12]
         V1                Normal vector 2                     [1,3,12]
         V2                Normal vector 3                     [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         RGB               Primary color          R,G,B,CODE   [0,8,0]
         LLM               Light matrix                        [1,3,12]
         LCM               Color matrix                        [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation:
Same as NCCS but repeats for v1 and v2.
--------------------------------------------------------------------------
CDP      13       Color Depth Que
Fields:  none
Opcode:  cop2 $1280414


In:      [IR1,IR2,IR3]     Vector                              [1,3,12]
         RGB               Primary color          R,G,B,CODE   [0,8,0]
         IR0               Interpolation value                 [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         LCM               Color matrix                        [1,3,12]
         FC                Far color              RFC,GFC,BFC  [1,27,4]
Out:     RGBn              RGB fifo               Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculation:
[1,19,12] MAC1=A1[RBK + LR1*IR1 + LR2*IR2 + LR3*IR3]           [1,19,24]
[1,19,12] MAC2=A2[GBK + LG1*IR1 + LG2*IR2 + LG3*IR3]           [1,19,24]
[1,19,12] MAC3=A3[BBK + LB1*IR1 + LB2*IR2 + LB3*IR3]           [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,19,12][lm=1]
[1,27,4]  MAC1=A1[R*IR1 + IR0*(Lm_B1[RFC-R*IR1])]              [1,27,16][lm=0]
[1,27,4]  MAC2=A2[G*IR2 + IR0*(Lm_B2[GFC-G*IR2])]              [1,27,16][lm=0]
[1,27,4]  MAC3=A3[B*IR3 + IR0*(Lm_B3[BFC-B*IR3])]              [1,27,16][lm=0]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,27,4][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,27,4][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,27,4][lm=1]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
CC       11       Color Color.
Fields:  none
Opcode:  cop2 $138041C
In:      [IR1,IR2,IR3]     Vector                              [1,3,12]
         BK                Background color       RBK,GBK,BBK  [1,19,12]
         RGB               Primary color          R,G,B,CODE   [0,8,0]
         LCM               Color matrix                        [1,3,12]
Out:     RGBn              RGB fifo.              Rn,Gn,Bn,CDn [0,8,0]
         [IR1,IR2,IR3]     Color vector                        [1,11,4]
         [MAC1,MAC2,MAC3]  Color vector                        [1,27,4]


Calculations:
[1,19,12] MAC1=A1[RBK + LR1*IR1 + LR2*IR2 + LR3*IR3]           [1,19,24]
[1,19,12] MAC2=A2[GBK + LG1*IR1 + LG2*IR2 + LG3*IR3]           [1,19,24]
[1,19,12] MAC3=A3[BBK + LB1*IR1 + LB2*IR2 + LB3*IR3]           [1,19,24]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,19,12][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,19,12][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,19,12][lm=1]
[1,27,4]  MAC1=A1[R*IR1]                                       [1,27,16]
[1,27,4]  MAC2=A2[G*IR2]                                       [1,27,16]
[1,27,4]  MAC3=A3[B*IR3]                                       [1,27,16]
[1,3,12]  IR1= Lm_B1[MAC1]                                     [1,27,4][lm=1]
[1,3,12]  IR2= Lm_B2[MAC2]                                     [1,27,4][lm=1]
[1,3,12]  IR3= Lm_B3[MAC3]                                     [1,27,4][lm=1]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]                             [1,27,4]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]                             [1,27,4]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]                             [1,27,4]
--------------------------------------------------------------------------
NCLIP    8        Normal clipping
Fields:
Opcode:  cop2 $1400006


in:      SXY0,SXY1,SXY2    Screen coordinates                  [1,15,0]
out:     MAC0              Outerproduct of SXY1 and SXY2 with  [1,31,0]
                           SXY0 as origin.


Calculation:
[1,31,0] MAC0 = F[SX0*SY1+SX1*SY2+SX2*SY0-SX0*SY2-SX1*SY0-SX2*SY1] [1,43,0]
--------------------------------------------------------------------------
AVSZ3    5        Average of three Z values
fields:
Opcode:  cop2 $158002D


in:      SZ1, SZ2, SZ3     Z-Values                            [0,16,0]
         ZSF3              Divider                             [1,3,12]
out:     OTZ               Average.                            [0,16,0]
         MAC0              Average.                            [1,31,0]


Calculation:
[1,31,0] MAC0=F[ZSF3*SZ1 + ZSF3*SZ2 + ZSF3*SZ3]                [1,31,12]
[0,16,0] OTZ=Lm_D[MAC0]                                        [1,31,0]
--------------------------------------------------------------------------
AVSZ4    6        Average of four Z values
Fields:
Opcode:  cop2 $168002E


in:      SZ1,SZ2,SZ3,SZ4   Z-Values                            [0,16,0]
         ZSF4              Divider                             [1,3,12]
out:     OTZ               Average.                            [0,16,0]
         MAC0              Average.                            [1,31,0]


Calculation:
[1,31,0] MAC0=F[ZSF4*SZ0 + ZSF4*SZ1 + ZSF4*SZ2 + ZSF4*SZ3]     [1,31,12]
[0,16,0] OTZ=Lm_D[MAC0]                                        [1,31,0]
--------------------------------------------------------------------------
OP       6        Outer product of 2 vectors
Fields:  sf
Opcode:  cop2 $170000C


in:      [R11R12,R22R23,R33] vector 1
         [IR1,IR2,IR3]      vector 2
out:     [IR1,IR2,IR3]      outer product
         [MAC1,MAC2,MAC3]   outer product


Calculation: (D1=R11R12,D2=R22R23,D3=R33)


         MAC1=A1[D2*IR3 - D3*IR2]
         MAC2=A2[D3*IR1 - D1*IR3]
         MAC3=A3[D1*IR2 - D2*IR1]
         IR1=Lm_B1[MAC0]
         IR2=Lm_B2[MAC1]
         IR3=Lm_B3[MAC2]


--------------------------------------------------------------------------
GPF      5        General purpose interpolation
Fields:  sf
Opcode:  cop2 $190003D


in:      IR0               scaling factor
         CODE              code field of RGB
         [IR1,IR2,IR3]     vector
out:     [IR1,IR2,IR3]     vector
         [MAC1,MAC2,MAC3]  vector
         RGB2              RGB fifo.


Calculation:


         MAC1=A1[IR0 * IR1]
         MAC2=A2[IR0 * IR2]
         MAC3=A3[IR0 * IR3]
         IR1=Lm_B1[MAC1]
         IR2=Lm_B2[MAC2]
         IR3=Lm_B3[MAC3]
[0,8,0]   Cd0<-Cd1<-Cd2<- CODE
[0,8,0]   R0<-R1<-R2<- Lm_C1[MAC1]
[0,8,0]   G0<-G1<-G2<- Lm_C2[MAC2]
[0,8,0]   B0<-B1<-B2<- Lm_C3[MAC3]
--------------------------------------------------------------------------
GPL      5        General purpose interpolation
Fields:  sf
Opcode:  cop2 $1A0003E


in:      IR0               scaling factor
         CODE              code field of RGB
         [IR1,IR2,IR3]     vector
         [MAC1,MAC2,MAC3]  vector
out:     [IR1,IR2,IR3]     vector
         [MAC1,MAC2,MAC3]  vector
         RGB2              RGB fifo.


Calculation:


         MAC1=A1[MAC1 + IR0 * IR1]
         MAC2=A2[MAC2 + IR0 * IR2]
         MAC3=A3[MAC3 + IR0 * IR3]
         IR1=Lm_B1[MAC1]
         IR2=Lm_B2[MAC2]
         IR3=Lm_B3[MAC3]
[0,8,0]  Cd0<-Cd1<-Cd2<- CODE
[0,8,0]  R0<-R1<-R2<- Lm_C1[MAC1]
[0,8,0]  G0<-G1<-G2<- Lm_C2[MAC2]
[0,8,0]  B0<-B1<-B2<- Lm_C3[MAC3]
--------------------------------------------------------------------------
Field decriptions.


bit |24 23 22 21 20|19|18 17|16 15|14 13|12 11|10|
desc|              |sf|mx   |v    |cv   |     |lm|


bit |09 08 07 06 05 04 03 02 01 00|
desc|                             |


sf 0  Normal calculation.
   1  Calculations on data shifted 12 bits to the left in the IR regs.
(Not entirely sure about what really happens.)


mx 0  Multiply with rotation matrix
   1  Multiply with light matrix
   2  Multiply with color matrix
   3  -


v  0  V0 source vector (short)
   1  V1 source vector (short)
   2  V2 source vector (short)
   3  IR source vector (long)


cv 0  Add translation vector (TR)
   1  Add back color vector  (BK)
   2  Bugged. Should add far color vector. (FC)
   3  Add no vector


lm 0  No negative limit.
   1  Limit negative results to 0.


--------------------------------------------------------------------------
A list of common MVMVA instructions:


rtv0     cop2 $0486012  v0 * rotmatrix
rtv1     cop2 $048E012  v1 * rotmatrix
rtv2     cop2 $0496012  v2 * rotmatrix


rtir12   cop2 $049E012  ir * rotmatrix
rtir0    cop2 $041E012  ir * rotmatrix.


rtv0tr   cop2 $0480012  v0 * rotmatrix + tr vector
rtv1tr   cop2 $0488012  v1 * rotmatrix + tr vector
rtv2tr   cop2 $0490012  v2 * rotmatrix + tr vector
rtirtr   cop2 $0498012  ir * rotmatrix + tr vector


rtv0bk   cop2 $0482012  v0 * rotmatrix + bk vector
rtv1bk   cop2 $048A012  v1 * rotmatrix + bk vector
rtv2bk   cop2 $0492012  v2 * rotmatrix + bk vector
rtirbk   cop2 $049A012  ir * rotmatrix + bk vector


ll       cop2 $04A6412  v0 * light matrix. Lower limit result to 0.


llv0     cop2 $04A6012  v0 * light matrix
llv1     cop2 $04AE012  v1 * light matrix
llv2     cop2 $04B6012  v2 * light matrix
llir     cop2 $04BE012  ir * light matrix


llv0tr   cop2 $04A0012  v0 * light matrix + tr vector
llv1tr   cop2 $04A8012  v1 * light matrix + tr vector
llv2tr   cop2 $04B0012  v2 * light matrix + tr vector
llirtr   cop2 $04B8012  ir * light matrix + tr vector


llv0bk   cop2 $04A2012  v0 * light matrix + bk vector
llv1bk   cop2 $04AA012  v1 * light matrix + bk vector
llv2bk   cop2 $04B2012  v2 * light matrix + bk vector
llirbk   cop2 $04BA012  ir * light matrix + bk vector


lc       cop2 $04DA412


lcv0     cop2 $04C6012  v0 * color matrix
lcv1     cop2 $04CE012  v1 * color matrix
lcv2     cop2 $04D6012  v2 * color matrix
lcir     cop2 $04DE012  ir * color matrix


lcv0tr   cop2 $04C0012  v0 * color matrix + tr vector
lcv1tr   cop2 $04C8012  v1 * color matrix + tr vector
lcv2tr   cop2 $04D0012  v2 * color matrix + tr vector
lcirtr   cop2 $04D8012  ir * color matrix + tr vector


lcv0bk   cop2 $04C2012  v0 * color matrix + bk vector
lcv1bk   cop2 $04CA012  v1 * color matrix + bk vector
lcv2bk   cop2 $04D2012  v2 * color matrix + bk vector
lcirbk   cop2 $04DA012  ir * color matrix + bk vector


Other instructions:


sqr12    cop2 $0A80428  square of ir  (1,19,12)
sqr0     cop2 $0A00428                (1,31, 0)


op12     cop2 $178000C  outer product (1,19,12)
op0      cop2 $170000C                (1,31, 0)


gpf12    cop2 $198003D  general purpose interpolation (1,19,12)
gpf0     cop2 $190003D                                (1,31, 0)


gpl12    cop2 $1A8003E  general purpose interpolation (1,19,12)
gpl0     cop2 $1A0003E                                (1,31, 0)


--------------------------------------------------------------------------
doomed@c64.org <- corrections/additions     latest update -> psx.rules.org
--------------------------------------------------------------------------
 8/jun/1999       Initial version.
23/aug/1999       Almost completely rewritten.
 2/feb/2000	  Small fix.
--------------------------------------------------------------------------
If you miss anything that was in the previous version please mail me.
--------------------------------------------------------------------------
```