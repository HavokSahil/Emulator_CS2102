#ifndef _DATAPATH_H
#define _DATAPATH_H

#include <devices.h>

struct _dp_struct {
    CElem* cu;
    CElem* regA;
    CElem* regB;
    CElem* mux_alu_a;
    CElem* mux_alu_b;
    CElem* alu;
    CElem* mem;
    CElem* pc;
    CElem* sp;
    CElem* ir;
    CElem* mux_a_in;
    CElem* mux_mem_in;
    CElem* mux_pc_in;
    CElem* mux_bz_pc;
    CElem* mux_bneg_pc;

    EmErr (*init)(struct _dp_struct*);
    EmErr (*load)(struct _dp_struct*);
    EmErr (*reset)(struct _dp_struct*);
    EmErr (*clock)(struct _dp_struct*);
    EmErr (*destroy)(struct _dp_struct*);
};

#endif
