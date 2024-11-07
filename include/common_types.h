#ifndef _COMMON_TYPES_H
#define _COMMON_TYPES_H

#include <ctype.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define LIM_PORT_NUMBER 16
#define LIM_MUX_CTRL	2
#define MAX_DATA        0x0FFFFFFF

#define ENABLE	1
#define DISABLE 0

#define TYPE_CIRC_ELEM_SEQ 	0x00
#define TYPE_CIRC_ELEM_NSEQ 0x01

#define PHASE_SEQ_UPDATE    0x00
#define PHASE_SEQ_EXPORT    0x01

#define TYPE_INSTR_IMM_NONE 0x00

#define SIZE_MUX_2X1				1
#define SIZE_MUX_4X1				2

#define SIZE_MEM				40960	/* 40*4 KB of Memory */
#define MEM_END_EXEC_SEG		10240	/* 10*4 KB of executable segment  */
#define MEM_BEG_DATA_SEG		10240	/* Starting position of data section  */
#define CUR_BEG_STK_PTR			40959	/* Begining of the Stack Pointer Cursor  */

#define CATEG_CIRC_ELEM_REG	0x01
#define CATEG_CIRC_ELEM_ALU	0x02
#define CATEG_CIRC_ELEM_MUX	0x03
#define CATEG_CIRC_ELEM_MEM 0x04
#define CATEG_CIRC_ELEM_DEC	0x05	/* Control Decoder Circuit Element */

#define ID_PORT_TEST0		0x01
#define ID_PORT_TEST1		0x02

#define ID_PORT_REG_WEN	    0x03
#define ID_PORT_REG_DIN	    0x06
#define ID_PORT_REG_DOUT    0x07

#define ID_PORT_MUX_2X1_INA	0x08
#define ID_PORT_MUX_2X1_INB	0x09
#define ID_PORT_MUX_2X1_OUT	0x0A
#define ID_PORT_MUX_2X1_CTR	0x0B

#define ID_PORT_MUX_4X1_INA	0x0C
#define ID_PORT_MUX_4X1_INB	0x0D
#define ID_PORT_MUX_4X1_INC	0x0E
#define ID_PORT_MUX_4X1_IND	0x0F
#define ID_PORT_MUX_4X1_OUT	0x10
#define ID_PORT_MUX_4X1_CTR	0x11

#define ID_PORT_MEM_WEN			0x12
#define ID_PORT_MEM_DIN 		0x13
#define ID_PORT_MEM_DOUT_A		0x14
#define ID_PORT_MEM_DOUT_B		0x15
#define ID_PORT_MEM_WADDR       0x16 
#define ID_PORT_MEM_RADDR_A     0x17
#define ID_PORT_MEM_RADDR_B     0x18
#define ID_PORT_MEM_RESET       0x19

#define ID_PORT_ALU_OP          0x1A
#define ID_PORT_ALU_INA         0x1B
#define ID_PORT_ALU_INB         0x1C
#define ID_PORT_ALU_OUT         0x1D
#define ID_PORT_ALU_ZERO        0x1E
#define ID_PORT_ALU_NEG         0x1F
#define ID_PORT_ALU_CARRY       0x20

#define ID_PORT_ADDER_INA		0x21
#define ID_PORT_ADDER_INB		0x22
#define ID_PORT_ADDER_OUT		0x23
#define ID_PORT_ADDER_CARRY		0x24
#define ID_PORT_ADDER_ZERO		0x25
#define ID_PORT_ADDER_NEG		0x26

#define ID_PORT_CU_MUX_BR       0x27 /**/
#define ID_PORT_CU_MUX_BR_FINE  0x28 /**/
#define ID_PORT_CU_W_EN_SP      0x29 /**/
#define ID_PORT_CU_W_EN_B       0x2A /**/
#define ID_PORT_CU_W_EN_A       0x2B /**/
#define ID_PORT_CU_MUX_PC_IN    0x2C /**/
#define ID_PORT_CU_W_EN_PC      0x2D /**/
#define ID_PORT_CU_MUX_ALU_A    0x2E /**/
#define ID_PORT_CU_MUX_A_IN     0x2F /**/
#define ID_PORT_CU_ALU_SEL      0x30 
#define ID_PORT_CU_MUX_ALU_B    0x31 
#define ID_PORT_CU_MUX_MEM_IN   0x32 
#define ID_PORT_CU_W_EN_MEM     0x33 
#define ID_PORT_CU_IMM          0x34 
#define ID_PORT_CU_INSTR        0x35 

#define TYPE_PORT_INPUT			0x00
#define TYPE_PORT_OUTPUT		0x01

#define TYPE_MEM_DUMP           0x00
#define TYPE_MEM_NODUMP         0x01

#define NAME_PORT_WEN			0x01
#define NAME_PORT_RADDR			0x02
#define NAME_PORT_WADDR			0x03
#define NAME_PORT_INDAT			0x04
#define NAME_PORT_OUTDAT		0x05
#define NAME_PORT_INP_ASYNC	    0x06
#define NAME_PORT_RESET         0x07

#define NAME_MUX_2X1			0x08
#define NAME_MUX_4X1			0x09
#define NAME_MUX_INPUT			0x0A
#define NAME_MUX_CTRL			0x0B
#define NAME_MUX_OUT			0x0C

#define NAME_MEM_40K            0x0D

#define NAME_ALU_OP             0x0E
#define NAME_ALU_INA            0x0F
#define NAME_ALU_INB            0x10
#define NAME_ALU_OUT            0x11
#define NAME_ALU_ZERO           0x12
#define NAME_ALU_NEG            0x13
#define NAME_ALU_CARRY          0x14

#define NAME_ADDER_INA			0x15
#define NAME_ADDER_INB			0x16
#define NAME_ADDER_OUT			0x17
#define NAME_ADDER_CARRY		0x18
#define NAME_ADDER_ZERO			0x19
#define NAME_ADDER_NEG			0x1A
#define NAME_ADDER              0x1B

#define NAME_DP_REG_A			0x01
#define NAME_DP_REG_B			0x02
#define NAME_DP_PC              0x03
#define NAME_DP_SP              0x04
#define NAME_DP_ALU             0x05
#define NAME_DP_MEM_CODE        0x06
#define NAME_DP_MEM_DATA        0x07
#define NAME_DP_MUX_A_IN        0x08
#define NAME_DP_MUX_MEM_IN      0x09
#define NAME_DP_MUX_PC_IN       0x0A
#define NAME_DP_MUX_BR          0x0B
#define NAME_DP_MUX_BR_FINE     0x0C
#define NAME_DP_MUX_BZ_PC       0x0D
#define NAME_DP_MUX_BNEG_PC     0x0E
#define NAME_DP_MUX_ALU_A       0x0F
#define NAME_DP_MUX_ALU_B       0x10
#define NAME_DP_PC_ADDER        0x11

#define NAME_CU_OUT             0x11

#define WIDTH_EN		        0x01
#define WIDTH_ADDR		        0x20
#define WIDTH_DATA		        0x20
#define WIDTH_MUX_CTRL_2X1	    0x01
#define WIDTH_MUX_CTRL_4X1	    0x02
#define WIDTH_ALU_OP            0x04

#define WIDTH_PORT_CU_MUX_BR        1
#define WIDTH_PORT_CU_MUX_BR_FINE   1
#define WIDTH_PORT_CU_W_EN_SP       1
#define WIDTH_PORT_CU_W_EN_B        1
#define WIDTH_PORT_CU_W_EN_A        1
#define WIDTH_PORT_CU_MUX_PC_IN     1
#define WIDTH_PORT_CU_W_EN_PC       1
#define WIDTH_PORT_CU_MUX_ALU_A     2
#define WIDTH_PORT_CU_MUX_A_IN      2
#define WIDTH_PORT_CU_ALU_SEL       2
#define WIDTH_PORT_CU_MUX_ALU_B     2
#define WIDTH_PORT_CU_MUX_MEM_IN    1
#define WIDTH_PORT_CU_W_EN_MEM      1
#define WIDTH_PORT_CU_IMM           32
#define WIDTH_PORT_CU_INSTR         32

#define SIGNAL_MEM_INIT		0x00
#define SIGNAL_MEM_RESET	0x01
#define SIGNAL_MEM_WRITE	0x02
#define SIGNAL_MEM_READ		0x03
#define SIGNAL_MEM_BURN		0x04

#define ALU_OP_ADD			0x00
#define ALU_OP_SUB			0x01
#define ALU_OP_SL           0x02
#define ALU_OP_SR           0x03
#define ALU_OP_AND			0x04
#define ALU_OP_OR			0x05
#define ALU_OP_XOR			0x06
#define ALU_OP_NOT			0x07

/*
Instruction Set
----------------------------
Mnemonic  Operand    Opcode
br         1          0011
adc        1          0001
add        0          0006
adj        1          000A
brz        1          000F
ldc        1          0000
ldl        1          0002
shl        0          0008
shr        0          0009
stl        1          0003
sub        0          0007
return     0          000E
HALT       0          0012
a2sp       0          000B
brlz       1          0010
call       1          000D
ldnl       1          0004
sp2a       0          000C
stnl       1          0005
*/

#define INSTR_BR		0x11
#define INSTR_ADC		0x01
#define INSTR_ADD		0x06
#define INSTR_ADJ		0x0A
#define INSTR_BRZ		0x0F
#define INSTR_LDC		0x00
#define INSTR_LDL		0x02
#define INSTR_SHL		0x08
#define INSTR_SHR		0x09
#define INSTR_STL		0x03
#define INSTR_SUB		0x07
#define INSTR_RETURN	0x0E
#define INSTR_HALT		0x12
#define INSTR_A2SP		0x0B
#define INSTR_BRLZ		0x10
#define INSTR_CALL		0x0D
#define INSTR_LDNL		0x04
#define INSTR_SP2A		0x0C
#define INSTR_STNL		0x05

/* Bus from the Master Output Ports */
#define BUS_PC_ADDER    0x00
#define BUS_PC          0x01
#define BUS_RA          0x02
#define BUS_RB          0x03
#define BUS_SP          0x04
#define BUS_ALU         0x05
#define BUS_CMEM        0x06
#define BUS_DMEM        0x07
#define BUS_MUX_A_IN    0x08
#define BUS_MUX_MEM_IN  0x09
#define BUS_MUX_PC_IN   0x0A
#define BUS_MUX_BR      0x0B
#define BUS_MUX_BR_FINE 0x0C
#define BUS_MUX_BZ_PC   0x0D
#define BUS_MUX_BNEG_PC 0x0E
#define BUS_MUX_ALU_A   0x0F
#define BUS_MUX_ALU_B   0x10
#define BUS_ALU_ZERO    0x11
#define BUS_ALU_NEG     0x12

/* Buses fromt the Control Unit */
#define BUS_CU_MUX_BR        0x14 /**/
#define BUS_CU_MUX_BR_FINE   0x15 /**/
#define BUS_CU_W_EN_SP       0x16 /**/
#define BUS_CU_W_EN_B        0x17 /**/
#define BUS_CU_W_EN_A        0x18 /**/
#define BUS_CU_MUX_PC_IN     0x19 /**/
#define BUS_CU_W_EN_PC       0x1A /**/
#define BUS_CU_MUX_ALU_A     0x1B /**/
#define BUS_CU_MUX_A_IN      0x1C /**/
#define BUS_CU_ALU_SEL       0x1D /**/
#define BUS_CU_MUX_ALU_B     0x1E /**/
#define BUS_CU_MUX_MEM_IN    0x1F /*.*/
#define BUS_CU_W_EN_MEM      0x20 /*.*/
#define BUS_CU_IMM           0x21 /*.*/

typedef unsigned char EmType;
typedef uint64_t EmSize;
typedef unsigned char EmBool;
typedef uint32_t EmInt;
typedef uint8_t EmByte;
typedef uint8_t EmErr;
typedef int32_t EmState;
typedef int32_t EmData;
typedef char* EmString;
typedef char EmChar;
typedef uint32_t EmName;
typedef unsigned char EmId;
typedef uint8_t EmSignal;

#endif
