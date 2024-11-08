#ifndef API_H
#define API_H

#include <err_codes.h>
#include <common_types.h>
#include <datapath.h>
#include <stdio.h>

#define API_VERSION 0x01
#define API_NAME "Emulator API"

#define TYPE_CELEM_RA    0x01
#define TYPE_CELEM_RB    0x02
#define TYPE_CELEM_ALU   0x03
#define TYPE_CELEM_MEM   0x04
#define TYPE_CELEM_SP    0x05
#define TYPE_CELEM_PC    0x06
#define TYPE_CELEM_CU    0x07

#define INDEX_PORT_CU_OPCODE 0x0
#define INDEX_PORT_CU_INSTR  0x1
#define INDEX_PORT_CU_W_EN_SP 0x2
#define INDEX_PORT_CU_W_EN_B 0x3
#define INDEX_PORT_CU_W_EN_A 0x4
#define INDEX_PORT_CU_W_EN_PC 0x5
#define INDEX_PORT_CU_W_EN_MEM 0x6
#define INDEX_PORT_CU_MUX_PC_IN 0x7
#define INDEX_PORT_CU_MUX_MEM_IN 0x8
#define INDEX_PORT_CU_MUX_A_IN 0x9
#define INDEX_PORT_CU_MUX_BR 0xA
#define INDEX_PORT_CU_MUX_BR_FINE 0xB
#define INDEX_PORT_CU_MUX_ALU_A 0xC
#define INDEX_PORT_CU_MUX_ALU_B 0xD
#define INDEX_PORT_CU_MUX_MEM_IN 0xE
#define INDEX_PORT_CU_ALU_SEL 0xF
#define INDEX_PORT_CU_IMM 0x10

#define INDEX_PORT_MEM_DOUT_A 0x0
#define INDEX_PORT_MEM_DOUT_B 0x1
#define INDEX_PORT_MEM_DIN 0x2
#define INDEX_PORT_MEM_WADDR 0x3
#define INDEX_PORT_MEM_WEN 0x4
#define INDEX_PORT_MEM_RADDR_A 0x5
#define INDEX_PORT_MEM_RADDR_B 0x6

#define BUFFER_SIZE_MEM_CELEM 0x07
#define BUFFER_SIZE_CU_CELEM 0x11




typedef struct _api_interface API;

struct _api_interface {

    DP* _dp;
    EmErr (*load)(API*, FILE*); /* Accepts standard LSD file format */
    EmErr (*reset)(API*);
    EmErr (*restart)(API*);
    EmErr (*get)(API*, EmType, EmByte*);
    EmErr (*dump_mem)(API*, FILE*);
    EmErr (*clock)(API*, EmSize);
    EmErr (*destroy)(API*);
};

EmErr get_api(API**);


#endif