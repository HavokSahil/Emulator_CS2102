#ifndef _DATAPATH_H
#define _DATAPATH_H

#include <devices.h>

struct _dp_struct {
    /* All the Circuit Element in the Datapath */
    CElem* cu;
    CElem* regA;
    CElem* regB;
    CElem* alu;
    CElem* mem_code;
    CElem* mem_data;
    CElem* pc;
    CElem* sp;
    CElem* mux_a_in;
    CElem* mux_mem_in;
    CElem* mux_pc_in;
    CElem* mux_br;
    CElem* mux_br_fine;
    CElem* mux_bz_pc;
    CElem* mux_bneg_pc;
    CElem* mux_alu_a;
    CElem* mux_alu_b;
    CElem* pc_adder;

    /* All the buses in the Datapath */
    Bus* bus_pc_adder;
    Bus* bus_pc;
    Bus* bus_ra;
    Bus* bus_rb;
    Bus* bus_sp;
    Bus* bus_alu;
    Bus* bus_alu_zero;
    Bus* bus_alu_neg;
    Bus* bus_cmem;
    Bus* bus_dmem;
    Bus* bus_mux_a_in;
    Bus* bus_mux_mem_in;
    Bus* bus_mux_pc_in;
    Bus* bus_mux_br;
    Bus* bus_mux_br_fine;
    Bus* bus_mux_bz_pc;
    Bus* bus_mux_bneg_pc;
    Bus* bus_mux_alu_a;
    Bus* bus_mux_alu_b;

    /* Interface Options */
    EmErr (*init)(struct _dp_struct*);
    EmErr (*load)(struct _dp_struct*, EmData*, EmSize);
    EmErr (*load_data)(struct _dp_struct*, EmData*, EmSize);
    EmErr (*reset)(struct _dp_struct*);
    EmErr (*restart)(struct _dp_struct*);
    EmErr (*inspect)(struct _dp_struct*, EmName, EmType, EmId, EmState*);
    EmErr (*clock)(struct _dp_struct*);
    EmErr (*destroy)(struct _dp_struct*);
};

typedef struct _dp_struct DP;

EmErr dp_get_datapath(DP** ptr);

void dp_print_cu(DP*);
void dp_print_stack_pointer(DP*);
void dp_print_register_a(DP*);
void dp_print_register_b(DP*);
void dp_print_program_counter(DP*);
void dp_print_mem_comp(DP*);
void dp_print_adder(DP*);
void dp_print_alu(DP*);

#endif
