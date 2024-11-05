#ifndef _COMMON_TYPES_H
#define _COMMON_TYPES_H

#include <ctype.h>
#include <stdint.h>

#define TRUE 1
#define FALSE 0

#define LIM_PORT_NUMBER 10
#define LIM_MUX_CTRL	2
#define MAX_DATA        0x0FFFFFFF

#define ENABLE	1
#define DISABLE 0

#define TYPE_CIRC_ELEM_SEQ 	0x00
#define TYPE_CIRC_ELEM_NSEQ 0x01

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

#define ID_PORT_TEST0				0x01
#define ID_PORT_TEST1				0x02

#define ID_PORT_REG_WEN			0x03
#define ID_PORT_REG_DIN			0x06
#define ID_PORT_REG_DOUT		0x07

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

#define TYPE_PORT_INPUT			0x00
#define TYPE_PORT_OUTPUT		0x01

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

#define WIDTH_EN		    0x01
#define WIDTH_ADDR		    0x20
#define WIDTH_DATA		    0x20
#define WIDTH_MUX_CTRL_2X1	0x01
#define WIDTH_MUX_CTRL_4X1	0x02
#define WIDTH_ALU_OP        0x04

#define SIGNAL_MEM_INIT			0x00
#define SIGNAL_MEM_RESET		0x01
#define SIGNAL_MEM_WRITE		0x02
#define SIGNAL_MEM_READ			0x03
#define SIGNAL_MEM_BURN			0x04

#define ALU_OP_ADD			0x00
#define ALU_OP_SUB			0x01
#define ALU_OP_SL           0x02
#define ALU_OP_SR           0x03
#define ALU_OP_AND			0x04
#define ALU_OP_OR			0x05
#define ALU_OP_XOR			0x06
#define ALU_OP_NOT			0x07

typedef unsigned char EmType;
typedef uint64_t EmSize;
typedef unsigned char EmBool;
typedef uint64_t EmInt;
typedef uint8_t EmByte;
typedef uint8_t EmErr;
typedef uint32_t EmState;
typedef uint32_t EmData;
typedef char* EmString;
typedef char EmChar;
typedef uint32_t EmName;
typedef unsigned char EmId;
typedef uint8_t EmSignal;

#endif
