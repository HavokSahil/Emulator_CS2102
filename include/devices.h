#ifndef _DEVICES_H
#define _DEVICES_H

#include <common_types.h>

typedef struct _port_struct Port;
typedef struct _bus_struct Bus;
typedef struct _circ_elem CElem;

struct _bus_struct {
	EmId id;
	EmState state;
	Port* master;
	Port** slaves;
	EmSize n_slaves;
	EmSize width;
	
	EmErr (*update)(Bus*);
	EmErr (*tap)(Bus*, EmState*);
	EmErr (*connect)(Bus*, Port*);
	void (*destroy)(Bus*);
};

struct _port_struct {
	EmName name;
	EmType type;	/* Input or Output */
	EmId port_id;
	EmState state;
	EmSize width;
	Bus* bus;
	CElem* parent;
	
	EmErr (*update)(Port*, EmState);
	EmErr (*inspect)(Port*, EmState*);
	EmErr (*connect)(Port*, Bus*);
	void (*destroy)(Port*);
};

struct _circ_elem {
	EmType type;	/* Sequential or Non-Sequential */
	EmName name;
	Port** input_ports;
	EmSize num_input_ports;

	Port** output_ports;
	EmSize num_output_ports;
	
	EmErr (*transition)(CElem*);	/* Transition the state of the circuit element. In case of NSEQ Elem, it intrinsically calls propogate */
	EmErr (*propogate)(CElem*);	/* Propogate the signal to the output ports, only applicable for SEQ Elem*/
	EmErr (*dump_memory)(CElem*, EmData**); /* Only for memory element */
	EmErr (*add_port)(CElem*, EmType, EmId, EmName, EmSize);
	EmErr (*get_port)(CElem*, EmType, EmId, Port**);
	void (*destroy)(CElem*);
};

EmErr dev_new_bus(Port*, EmSize, EmId, Bus**);
EmErr dev_new_port(EmName, EmId, EmType, EmSize, CElem*, Port**);
EmErr dev_new_celem(EmType, CElem**);

void debug_print_bus(Bus* bus);
void debug_print_port(Port* port);
void debug_print_celem(CElem* celem);

/* Definations of Higher Components */
EmErr dev_new_register(EmName, CElem**);
EmErr dev_new_memory(EmName, CElem**);
EmErr dev_new_mux(EmName, EmSize, CElem**);	/* Mux requires number of control bits for definations */
EmErr dev_new_alu(EmName, CElem**);
EmErr dev_new_adder(EmName, CElem**);

#endif
