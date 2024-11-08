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