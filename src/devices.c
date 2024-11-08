#include <devices.h>
#include <stddef.h>
#include <stdlib.h>
#include <err_codes.h>

/**
 * Functions for Bus Interface
 * -----------------------------------------*/

static EmErr _dev_bus_update(Bus* bus) {
	if (bus == NULL)
		return ERR_INV_PTR;

	Port* master = bus->master;
	if (master == NULL)
		return ERR_INV_PTR;

	EmState state;

	EmErr err = master->inspect(master, &state);
	if (err != SUCCESS)
		return err;

	bus->state = state;

	EmInt iter;
	for (iter = 0; iter<bus->n_slaves; iter++) {
		Port* slave = (bus->slaves)[iter];
		/* Trigger update on each slave port */
		err = slave->update(slave, state);
		if (err != SUCCESS)
			return err;
	}

	return SUCCESS;
}

static EmErr _dev_bus_tap(Bus* bus, EmState* state) {
	if (bus == NULL || state == NULL)
		return ERR_INV_PTR;

	*state = bus->state;
	return SUCCESS;
}

static EmErr _dev_bus_connect(Bus* bus, Port* slave) {
	if (bus == NULL || slave == NULL)
		return ERR_INV_PTR;

	if (bus->n_slaves >= LIM_PORT_NUMBER)
		return ERR_PRT_LME;

	EmSize n_slaves = bus->n_slaves;
	bus->slaves[n_slaves++] = slave;
	bus->n_slaves = n_slaves;

	return SUCCESS;
}

static void _dev_bus_destroy(Bus* bus) {
	if (bus == NULL)
		return;

	if (bus->slaves != NULL) 
		free(bus->slaves);

	free(bus);
}

EmErr dev_new_bus(Port* master, EmSize width, EmId bus_id, Bus** ptr) {
	if (master == NULL)
		return ERR_INV_PTR;
	
	if (master->type != TYPE_PORT_OUTPUT)
		return ERR_USP_PTY;
		
	if (master->bus != NULL)
		return ERR_MUL_MST;

	if (master->width != width)
		return ERR_QOS_MIS;

	Bus* bus = (Bus*)malloc(sizeof(Bus));
	if (bus == NULL)
		return ERR_MEM_ALLOC;

	Port** slaves = (Port**)malloc(sizeof(Port*) * LIM_PORT_NUMBER);
	if (slaves == NULL) {
		free(bus);
		return ERR_MEM_ALLOC;
	}
	
	EmInt iter;
	for (iter = 0; iter < LIM_PORT_NUMBER; iter++) {
		slaves[iter] = NULL;
	}

	bus->id = bus_id;
	bus->state = 0;
	bus->master = master;
	bus->width = width;
	bus->slaves = slaves;
	bus->n_slaves = 0;


	/* The function pointers for the bus structure interface  */
	bus->update = _dev_bus_update;
	bus->tap = _dev_bus_tap;
	bus->connect = _dev_bus_connect;
	bus->destroy = _dev_bus_destroy;
	
	master->bus = bus;
	*ptr = bus;
	return SUCCESS;
}

void debug_print_bus(Bus* bus) {
	printf("Bus: %p\n--------------------\n", bus);
	if (bus == NULL)
		return;
	printf("%-*s %-*s\n--------------------\n", 8, "Field", 8, "Value");
	printf("%-*s %-*d\n", 8, "Bus Id", 8, bus->id);
	printf("%-*s %-*p\n", 8, "Master", 8, bus->master);
	printf("%-*s %-*d\n", 8, "State", 8, bus->state);
	printf("%-*s %-*d\n", 8, "N Slaves", 8, bus->n_slaves);
	printf("> ");
	
	EmInt iter;
	for (iter = 0; iter < bus->n_slaves; iter++) {
		Port* slave = (bus->slaves)[iter];
		printf("| %p |", slave);
	}
	printf("\n");
	printf("%-*s %-*d\n", 8, "Width", 8, bus->width);
	printf("\n");
}

/**
 * Functions for Port Interface
 * -----------------------------------------*/
static EmErr _dev_port_is_slave_of(Bus* bus, Port* port, EmBool* ptr) {
	if (bus == NULL || port == NULL || ptr == NULL)
		return ERR_INV_PTR;

	if (bus->slaves == NULL)
		return ERR_INV_PTR;
	
	EmInt iter;
	for (iter = 0; iter < bus->n_slaves; iter++) {
		Port* slave = (bus->slaves)[iter];
		if (slave == port) {
			*ptr = TRUE;
			return SUCCESS;
		}
	}
	*ptr = FALSE;
	return SUCCESS;
}

EmErr _dev_port_update(Port* port, EmState data) {

	if (port == NULL)
		return ERR_INV_PTR;

	/* Case when the port is output port, update the bus subsequently   */
	if (port->type == TYPE_PORT_OUTPUT) {
		port->state = data;
		Bus* bus = port->bus;
		if (bus == NULL)
			return SUCCESS;
		EmErr err = bus->update(bus);
		return err;
	}
	/* Case when the port is input port, update the current port state based on the bus state [data is unused]   */

	port->state = data;
	CElem* parent = port->parent;

	if (parent == NULL) 
		return ERR_INV_PTR;

	if (parent->type == TYPE_CIRC_ELEM_NSEQ) {
		/* Instantaneously Propogate the changes through the non-sequential element   */
		return parent->transition(parent);
	}

	return SUCCESS;
}

static EmErr _dev_port_connect(Port* port, Bus* bus) {	/* Connect INPUT port to a bus. */
	/* Note: Connect is not for OUTPUT port as Bus does not exist without master Port which is OUTPUT port */

	if (port == NULL || bus == NULL)
		return ERR_INV_PTR;

	if (port->width != bus->width)
		return ERR_QOS_MIS;

	if (port->type == TYPE_PORT_OUTPUT)
		return ERR_USP_PTY;

	port->bus = bus;
	EmErr err = bus->connect(bus, port);	/* Insert the port into slaves of the bus */
	if (err != SUCCESS)
		port->bus = NULL;

	return err;
}

EmErr _dev_port_inspect(Port* port, EmState* ptr) {
	if (port == NULL || ptr == NULL)
		return ERR_INV_PTR;

	*ptr = port->state;
	return SUCCESS;
}

static void _dev_port_destroy(Port* port) {
	if (port == NULL)
		return;

	free(port);
}

EmErr dev_new_port(EmName name, EmId port_id, EmType type, EmSize width, CElem* parent, Port** ptr) {
	if (parent == NULL || ptr == NULL)
		return ERR_INV_PTR;

	Port* port = (Port*)malloc(sizeof(Port));
	if (port == NULL)
		return ERR_MEM_ALLOC;

	port->name = name;
	port->port_id = port_id;
	port->type = type;
	port->width = width;
	port->parent = parent;
	port->state = 0;
	port->bus = NULL;

	port->update 	= _dev_port_update;
	port->inspect = _dev_port_inspect;
	port->connect = _dev_port_connect;
	port->destroy = _dev_port_destroy;

	*ptr = port;

	return SUCCESS;
}

void debug_print_port(Port* port) {
	printf("Port %p\n--------------------\n", port);
	if (port == NULL)
		return;

	printf("%-*s %-*s\n--------------------\n", 8, "Field", 8, "Value");
	printf("%-*s %-*d\n", 8, "Name", 8, port->name);
	printf("%-*s %-*d\n", 8, "Type", 8, port->type);
	printf("%-*s %-*d\n", 8, "Id", 8, port->port_id);
	printf("%-*s %-*d\n", 8, "State", 8, port->state);
	printf("%-*s %-*d\n", 8, "Width", 8, port->width);
	printf("%-*s %-*p\n", 8, "Bus", 8, port->bus);
	printf("%-*s %-*p\n", 8, "Parent", 8, port->parent);
	printf("\n");
}

/**
 * Functions for Circuit Element Interface
 * -----------------------------------------*/
static EmErr _dev_celem_add_port(CElem* celem, EmType type, EmId port_id, EmName name, EmSize width) {
	if (celem == NULL)
		return ERR_INV_PTR;

	if (type == TYPE_PORT_INPUT) {
		/* If the new port is input port  */
		if (celem->num_input_ports >= LIM_PORT_NUMBER)
			return ERR_PRT_LME;
		
		Port* port;
		EmErr err = dev_new_port(name, port_id, type, width, celem, &port);
		if (err != SUCCESS)
			return err;
		Port** input_ports = celem->input_ports;
		input_ports[celem->num_input_ports++] = port;

		return SUCCESS;
	} else if (type == TYPE_PORT_OUTPUT) {
		/* If the new port is output port  */
		if (celem->num_output_ports >= LIM_PORT_NUMBER)
			return ERR_PRT_LME;
		Port* port;
		EmErr err = dev_new_port(name, port_id, type, width, celem, &port);
		if (err != SUCCESS)
			return err;
		Port** output_ports = celem->output_ports;
		output_ports[celem->num_output_ports++] = port;

		return SUCCESS;
	}
	return ERR_USP_PTY;
}

static EmErr _dev_celem_get_port(CElem* celem, EmType type, EmId port_id, Port** ptr) {
	if (celem == NULL || ptr == NULL)
		return ERR_INV_PTR;

	EmInt iter;

	if (type == TYPE_PORT_INPUT) {	/* If looking for input ports   */
		Port** input_ports = celem->input_ports;

		for (iter = 0; iter < celem->num_input_ports; iter++) {
			Port* port = input_ports[iter];

			if (port->port_id == port_id) {
				*ptr = port;
				return SUCCESS;
			}
		}
		*ptr = NULL;
		return SUCCESS;

	} else if (type == TYPE_PORT_OUTPUT) {	/* If looking for output ports   */
		Port** output_ports = celem->output_ports;

		for (iter = 0; iter < celem->num_output_ports; iter++) {
			Port* port = output_ports[iter];
			
			if (port->port_id == port_id) {
				*ptr = port;
				return SUCCESS;
			}
		}
		*ptr = NULL;
		return SUCCESS;
	}

	return ERR_USP_PTY;
}

static void _dev_celem_destroy(CElem* celem) {
	if (celem == NULL)
		return;

	if (celem->input_ports)
		free(celem->input_ports);

	if (celem->output_ports)
		free(celem->output_ports);
	
	free(celem);
}

EmErr dev_new_celem(EmType type, CElem** ptr) {
	if (ptr == NULL)
		return ERR_INV_PTR;

	CElem* celem = (CElem*)malloc(sizeof(CElem));
	if (celem == NULL)
		return ERR_MEM_ALLOC;

	EmInt iter;
	Port** input_ports = (Port**)malloc(sizeof(Port*) * LIM_PORT_NUMBER);
	if (input_ports == NULL)
		return ERR_MEM_ALLOC;

	for (iter = 0; iter < LIM_PORT_NUMBER; iter++) {
		input_ports[iter] = NULL;
	}

	Port** output_ports = (Port**)malloc(sizeof(Port*) * LIM_PORT_NUMBER);
	if (output_ports == NULL)
		return ERR_MEM_ALLOC;

	for (iter = 0; iter < LIM_PORT_NUMBER; iter++) {
		output_ports[iter] = NULL;
	}

	celem->type = type;
	celem->input_ports = input_ports;
	celem->num_input_ports = 0;
	celem->output_ports = output_ports;
	celem->num_output_ports = 0;

	celem->transition = NULL;
	celem->propogate = NULL;
	celem->add_port = _dev_celem_add_port;
	celem->get_port = _dev_celem_get_port;
	celem->destroy = _dev_celem_destroy;

	*ptr = celem;

	return SUCCESS;
}

void debug_print_celem(CElem* celem) {
	printf("Circuit Element %p\n--------------------\n", celem);
	if (celem == NULL)
		return;

	printf("%-*s %-*s\n--------------------\n", 8, "Field", 8, "Value");
	printf("%-*s %-*d\n", 8, "Type", 8, celem->type);
	printf("%-*s %-*d\n", 8, "N In", 8, celem->num_input_ports);
	printf("%-*s %-*p\n", 8, "Inp Prt", 8, (void*)(celem->input_ports));
	printf("> ");
	
	EmInt iter;
	for (iter = 0; iter < celem->num_input_ports; iter++) {
		Port* port = (celem->input_ports)[iter];
		printf("| %p |", (void*)port);
	}
	printf("\n");
	printf("%-*s %-*d\n", 8, "N Out", 8, celem->num_output_ports);
	printf("%-*s %-*p\n", 8, "Out Prt", 8, (void*)(celem->output_ports));
	printf("> ");

	for (iter = 0; iter < celem->num_output_ports; iter++) {
		Port* port = (celem->output_ports)[iter];
		printf("| %p |", (void*)port);
	}
	printf("\n\n");
}

/**
 * Definations for  Register Component
 * -----------------------------------------*/

static EmErr _dev_register_tf(CElem* celem) {	/* Register Transition Function  */

	if (celem == NULL)
		return ERR_INV_PTR;	

	Port* wen;
	EmErr err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &wen);
	if (err != SUCCESS)
		return err;

	Port* din;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &din);
	if (err != SUCCESS)
		return err;

	Port* dout;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &dout);
	if (err != SUCCESS)
		return err;
	
	if (wen == NULL || din == NULL || dout == NULL)
		return ERR_INV_PTR;

	EmState wen_state;
	err = wen->inspect(wen, &wen_state);
	if (err != SUCCESS)
		return err;
	
	EmState data;
	if (wen_state == ENABLE) {
		err = din->inspect(din, &data);		
		if (err != SUCCESS)
			return err;
		
		dout->state = data;		
	}

	return SUCCESS;
}

static EmErr  _dev_register_pf(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;

	Port* dout;
	EmErr err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &dout);
	if (err != SUCCESS)
		return err;

	if (dout == NULL)
		return ERR_INV_PTR;

	err = dout->update(dout, dout->state);
	return err;
}

EmErr dev_new_register(EmName name, CElem** ptr) {
	if (ptr == NULL)
		return ERR_INV_PTR;
	
	CElem* celem;
	EmErr err = dev_new_celem(TYPE_CIRC_ELEM_SEQ, &celem);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_REG_WEN, NAME_PORT_WEN, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_REG_DIN, NAME_PORT_INDAT, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, NAME_PORT_OUTDAT, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	
	celem->name = name;

	celem->transition = _dev_register_tf;
	celem->propogate = _dev_register_pf;

	*ptr = celem;

	return SUCCESS;
}

/**
 *	Definations for Multiplexer Circuit Component
 * -----------------------------------------------*/
static EmErr _dev_mux_tf_2x1(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;
	
	Port* ctrl;
	EmErr err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &ctrl);
	if (err != SUCCESS)
		return err;

	if (ctrl == NULL)
		return ERR_INV_PTR;

	EmState ctrl_value;
	err =	ctrl->inspect(ctrl, &ctrl_value);
	if (err != SUCCESS)
		return err;

	EmState result;
	if (ctrl_value == 0) {
		Port* port;
		err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &port);
		if (err != SUCCESS)
			return err;

		if (port == NULL)
			return ERR_INV_PTR;
		
		err = port->inspect(port, &result);
		if (err != SUCCESS)
			return err;

	} else if (ctrl_value == 1) {
			Port* port;
			err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, &port);
			if (err != SUCCESS)
				return err;
	
			if (port == NULL)
				return ERR_INV_PTR;
			
			err = port->inspect(port, &result);
			if (err != SUCCESS)
				return err;
	} else return ERR_MUX_OVF;

	Port* out;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &out);
	if (err != SUCCESS)
		return err;
	
	err = out->update(out, result);
	return err;
}

static EmErr _dev_mux_tf_4x1(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;
	
	Port* ctrl;
	EmErr err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_CTR, &ctrl);
	if (err != SUCCESS)
		return err;

	if (ctrl == NULL)
		return ERR_INV_PTR;

	EmState ctrl_value;
	err =	ctrl->inspect(ctrl, &ctrl_value);
	if (err != SUCCESS)
		return err;

	EmState result;
	if (ctrl_value == 0) {
		Port* port;
		err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INA, &port);
		if (err != SUCCESS)
			return err;

		if (port == NULL)
			return ERR_INV_PTR;
		
		err = port->inspect(port, &result);
		if (err != SUCCESS)
			return err;

	} else if (ctrl_value == 1) {
			Port* port;
			err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INB, &port);
			if (err != SUCCESS)
				return err;
	
			if (port == NULL)
				return ERR_INV_PTR;
			
			err = port->inspect(port, &result);
			if (err != SUCCESS)
				return err;
	} else if (ctrl_value == 2) {
			Port* port;
			err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INC, &port);
			if (err != SUCCESS)
				return err;
	
			if (port == NULL)
				return ERR_INV_PTR;
			
			err = port->inspect(port, &result);
			if (err != SUCCESS)
				return err;

	} else if (ctrl_value == 3) {
			Port* port;
			err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_IND, &port);
			if (err != SUCCESS)
				return err;
	
			if (port == NULL)
				return ERR_INV_PTR;
			
			err = port->inspect(port, &result);
			if (err != SUCCESS)
				return err;

	} else return ERR_MUX_OVF;

	Port* out;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MUX_4X1_OUT, &out);
	if (err != SUCCESS)
		return err;
	
	err = out->update(out, result);
	return err;
}

EmErr dev_new_mux(EmName name, EmSize ctrl_bits, CElem** ptr) {
	if (ptr == NULL)
		return ERR_INV_PTR;
	
	if (ctrl_bits > LIM_MUX_CTRL)
		return ERR_MUX_OVF;

	CElem* celem;
	EmErr err = dev_new_celem(TYPE_CIRC_ELEM_NSEQ, &celem);
	if (err != SUCCESS)
		return err;
	
	if (ctrl_bits == SIZE_MUX_2X1) {
		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, NAME_MUX_INPUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, NAME_MUX_INPUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, NAME_MUX_CTRL, WIDTH_MUX_CTRL_2X1);
		if (err != SUCCESS)
			return err;
		err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, NAME_MUX_OUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;
		
		celem->transition = _dev_mux_tf_2x1;
			
	} else if (ctrl_bits == SIZE_MUX_4X1) {
		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INA, NAME_MUX_INPUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INB, NAME_MUX_INPUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INC, NAME_MUX_INPUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_IND, NAME_MUX_INPUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_CTR, NAME_MUX_CTRL, WIDTH_MUX_CTRL_4X1);
		if (err != SUCCESS)
			return err;

		err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MUX_4X1_OUT, NAME_MUX_OUT, WIDTH_DATA);
		if (err != SUCCESS)
			return err;

		celem->transition = _dev_mux_tf_4x1;
	} else return ERR_MUX_OVF;
	
	celem->name = name;
	celem->type = TYPE_CIRC_ELEM_NSEQ;
	
	*ptr = celem;
	return SUCCESS;
}

/**
 * Definations for Memory Element
 * ---------------------------------*/
static EmErr _dev_mem_manager(CElem* celem, EmSignal signal, EmData *data, EmData addr, EmType dump, EmData** ptr) {

	static EmData* mem = NULL;

	if (dump == TYPE_MEM_DUMP) {
		if (mem == NULL)
			return ERR_INV_PTR;

		*ptr = mem;
		return SUCCESS;
	}

	if (signal == SIGNAL_MEM_INIT) {
		if (mem != NULL)
			free(mem);

		mem = (EmData*)malloc(sizeof(EmData) * SIZE_MEM);
		if (mem == NULL)
			return ERR_MEM_ALLOC;

		memset(mem, 0, SIZE_MEM*sizeof(EmData));
		return SUCCESS;
	}

	if (signal == SIGNAL_MEM_RESET) {
		if (mem == NULL)
			return ERR_INV_PTR;

		memset(mem, 0, SIZE_MEM*sizeof(EmData));
		return SUCCESS;
	}

	if (signal == SIGNAL_MEM_WRITE) {
		if ((addr >= 0) && (addr < SIZE_MEM)) {
			if (mem == NULL)
				return ERR_INV_PTR;
			mem[addr] = *data;
			return SUCCESS;
		}

		return ERR_MEM_IOB;	/* Out of bounds error   */
	}
	
	if (signal == SIGNAL_MEM_READ) {
		if ((addr >= 0) && (addr < SIZE_MEM)) {
			if (mem == NULL)
				return ERR_INV_PTR;

			*data = mem[addr];
			return SUCCESS;
		}
		
		return ERR_MEM_IOB;
	}

	if (signal == SIGNAL_MEM_BURN) {
		if (mem != NULL)
			free(mem);

		return SUCCESS;
	}

	return ERR_MEM_IVS;
}

static EmBool _dev_valid_mem_addr(EmData addr) {
	if ((addr >= 0) && (addr < SIZE_MEM))
		return TRUE;
	return FALSE;
}

static EmErr _dev_mem_tf(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;

	Port* reset;
	EmErr err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, &reset);
	if (err != SUCCESS)
		return err;
	
	EmState reset_state;
	err = reset->inspect(reset, &reset_state);
	if (err != SUCCESS)
		return err;
	
	if (reset_state == ENABLE) {
		err = _dev_mem_manager(celem, SIGNAL_MEM_RESET, NULL, 0, TYPE_MEM_NODUMP, NULL);
		if (err != SUCCESS)
			return err;
	}

	Port* wen;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, &wen);
	if (err != SUCCESS)
		return err;
	
	EmState wen_state;
	err = wen->inspect(wen, &wen_state);
	if (err != SUCCESS)
		return err;
	
	if ((wen_state == ENABLE) && (reset_state != ENABLE)) {
		Port* din;
		err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &din);
		if (err != SUCCESS)
			return err;
		
		Port* waddr;
		err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, &waddr);
		if (err != SUCCESS)
			return err;
		
		EmData data;
		err = din->inspect(din, &data);
		if (err != SUCCESS)
			return err;
		
		EmData addr;
		err = waddr->inspect(waddr, &addr);
		if (err != SUCCESS)
			return err;
		
		err = _dev_mem_manager(celem, SIGNAL_MEM_WRITE, &data, addr, TYPE_MEM_NODUMP, NULL);
		if (err != SUCCESS)
			return err;
	}

	Port* raddr_a;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_A, &raddr_a);
	if (err != SUCCESS)
		return err;
	
	Port* raddr_b;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_B, &raddr_b);
	if (err != SUCCESS)
		return err;
	
	Port* dout_a;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &dout_a);
	if (err != SUCCESS)
		return err;
	
	Port* dout_b;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &dout_b);
	if (err != SUCCESS)
		return err;
	
	EmData addr_a;
	err = raddr_a->inspect(raddr_a, &addr_a);
	if (err != SUCCESS)
		return err;
	
	EmData addr_b;
	err = raddr_b->inspect(raddr_b, &addr_b);
	if (err != SUCCESS)
		return err;
	
	if (_dev_valid_mem_addr(addr_a) == TRUE) {
		EmData data_a;
		err = _dev_mem_manager(celem, SIGNAL_MEM_READ, &data_a, addr_a, TYPE_MEM_NODUMP, NULL);
		if (err != SUCCESS)
			return err;
		
		dout_a->state = data_a;
	}


	if (_dev_valid_mem_addr(addr_b) == TRUE) {
		EmData data_b;
		err = _dev_mem_manager(celem, SIGNAL_MEM_READ, &data_b, addr_b, TYPE_MEM_NODUMP, NULL);
		if (err != SUCCESS)
			return err;

		err = dout_b->update(dout_b, data_b);
		if (err != SUCCESS)
			return err;
	}

	return SUCCESS;
}

static EmErr _dev_mem_propogate(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;

	Port* dout_a;
	EmErr err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &dout_a);
	if (err != SUCCESS)
		return err;
	
	Port* dout_b;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &dout_b);
	if (err != SUCCESS)
		return err;
	
	if (dout_a == NULL || dout_b == NULL)
		return ERR_INV_PTR;

	err = dout_a->update(dout_a, dout_a->state);
	if (err != SUCCESS)
		return err;

	err = dout_b->update(dout_b, dout_b->state);
	if (err != SUCCESS)
		return err;

	return SUCCESS;
}

static EmErr _dev_mem_dump(CElem* celem, EmData** ptr) {
	if (celem == NULL || ptr == NULL)
		return ERR_INV_PTR;

	EmErr err = _dev_mem_manager(celem, 0, NULL, 0, TYPE_MEM_DUMP, ptr);
	return err;
}

EmErr dev_new_memory(EmName name, CElem** ptr) {
	if (ptr == NULL)
		return ERR_INV_PTR;

	CElem* celem;
	EmErr err = dev_new_celem(TYPE_CIRC_ELEM_SEQ, &celem);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, NAME_PORT_WEN, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, NAME_PORT_WEN, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, NAME_PORT_OUTDAT, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, NAME_PORT_OUTDAT, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, NAME_PORT_WADDR, WIDTH_ADDR);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_A, NAME_PORT_RADDR, WIDTH_ADDR);
	if (err != SUCCESS)
		return err;
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_B, NAME_PORT_RADDR, WIDTH_ADDR);
	if (err != SUCCESS)
		return err;	
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, NAME_PORT_RESET, WIDTH_EN);
	if (err != SUCCESS)
		return err;

	_dev_mem_manager(celem, SIGNAL_MEM_INIT, NULL, 0, TYPE_MEM_NODUMP, NULL);
	
	celem->name = name;
	celem->transition = _dev_mem_tf;
	celem->propogate = _dev_mem_propogate;
	celem->dump_memory = _dev_mem_dump;

	*ptr = celem;

	return SUCCESS;
}

/**
 * Definations for ALU Element
 * ---------------------------------*/
static EmErr _dev_alu_tf(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;

	Port* op;
	EmErr err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_ALU_OP, &op);
	if (err != SUCCESS)
		return err;
	
	Port* ina;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_ALU_INA, &ina);
	if (err != SUCCESS)
		return err;
	
	Port* inb;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_ALU_INB, &inb);
	if (err != SUCCESS)
		return err;
	
	Port* out;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_OUT, &out);
	if (err != SUCCESS)
		return err;
	
	Port* zero;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_ZERO, &zero);
	if (err != SUCCESS)
		return err;
	
	Port* neg;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_NEG, &neg);
	if (err != SUCCESS)
		return err;

	Port* carry;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_CARRY, &carry);
	if (err != SUCCESS)
		return err;
	
	if (op == NULL || ina == NULL || inb == NULL || out == NULL || zero == NULL || neg == NULL || carry == NULL)
		return ERR_INV_PTR;

	EmState op_state;
	err = op->inspect(op, &op_state);
	if (err != SUCCESS)
		return err;
	
	EmData ina_state;
	err = ina->inspect(ina, &ina_state);
	if (err != SUCCESS)
		return err;
	
	EmData inb_state;
	err = inb->inspect(inb, &inb_state);
	if (err != SUCCESS)
		return err;
	
	EmData data_out = 0;
	EmState zero_out = DISABLE;
	EmState neg_out = DISABLE;
	EmState carry_out = DISABLE;

	switch (op_state) {
		case ALU_OP_ADD:
			data_out = ina_state + inb_state;
			break;
		case ALU_OP_SUB:
			data_out = inb_state - ina_state;
			break;
		case ALU_OP_SL:
			data_out = inb_state << ina_state;
			break;
		case ALU_OP_SR:
			data_out = inb_state >> ina_state;
			break;
		case ALU_OP_AND:
			data_out = ina_state & inb_state;
			break;
		case ALU_OP_OR:
			data_out = ina_state | inb_state;
			break;
		case ALU_OP_XOR:
			data_out = ina_state ^ inb_state;
			break;
		case ALU_OP_NOT:
			data_out = ~ina_state;
			break;
		default:
			return ERR_ALU_OVF;
	}

	zero_out = (data_out == 0) ? ENABLE : DISABLE;
	neg_out = (data_out < 0) ? ENABLE : DISABLE;
	carry_out = (data_out > MAX_DATA) ? ENABLE : DISABLE;

	err = out->update(out, data_out);
	if (err != SUCCESS)
		return err;
	
	err = zero->update(zero, zero_out);
	if (err != SUCCESS)
		return err;
	
	err = neg->update(neg, neg_out);
	if (err != SUCCESS)
		return err;
	
	err = carry->update(carry, carry_out);
	if (err != SUCCESS)
		return err;
		
	return SUCCESS;
}

EmErr dev_new_alu(EmName name, CElem** ptr) {

	CElem* celem;
	EmErr err = dev_new_celem(TYPE_CIRC_ELEM_NSEQ, &celem);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_ALU_OP, NAME_ALU_OP, WIDTH_ALU_OP);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_ALU_INA, NAME_ALU_INA, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_ALU_INB, NAME_ALU_INB, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_OUT, NAME_ALU_OUT, WIDTH_DATA);
	if (err != SUCCESS)
		return err;

	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_ZERO, NAME_ALU_ZERO, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_NEG, NAME_ALU_NEG, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ALU_CARRY, NAME_ALU_CARRY, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	
	celem->name = name;
	celem->transition = _dev_alu_tf;

	*ptr = celem;
	
	return SUCCESS;
}

static EmErr _dev_adder_tf(CElem* celem) {
	if (celem == NULL)
		return ERR_INV_PTR;

	Port* ina;
	EmErr err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_ADDER_INA, &ina);
	if (err != SUCCESS)
		return err;

	Port* inb;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_ADDER_INB, &inb);
	if (err != SUCCESS)
		return err;
	
	Port* out;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ADDER_OUT, &out);
	if (err != SUCCESS)
		return err;

	Port* carry;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ADDER_CARRY, &carry);
	if (err != SUCCESS)
		return err;
	
	Port* zero;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ADDER_ZERO, &zero);
	if (err != SUCCESS)
		return err;
	
	Port* neg;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_ADDER_NEG, &neg);
	if (err != SUCCESS)
		return err;
	
	if (ina == NULL || inb == NULL || out == NULL || carry == NULL || zero == NULL || neg == NULL)
		return ERR_INV_PTR;

	EmState ina_state;
	err = ina->inspect(ina, &ina_state);
	if (err != SUCCESS)
		return err;
	
	EmState inb_state;
	err = inb->inspect(inb, &inb_state);
	if (err != SUCCESS)
		return err;
	
	EmData data_out = (EmInt)ina_state + (EmInt)inb_state;
	EmState zero_out = (data_out == 0) ? ENABLE : DISABLE;
	EmState neg_out = (data_out < 0) ? ENABLE : DISABLE;
	EmState carry_out = (data_out > MAX_DATA) ? ENABLE : DISABLE;

	err = out->update(out, data_out);
	if (err != SUCCESS)
		return err;
	
	err = zero->update(zero, zero_out);
	if (err != SUCCESS)
		return err;
	
	err = neg->update(neg, neg_out);
	if (err != SUCCESS)
		return err;
	
	err = carry->update(carry, carry_out);
	if (err != SUCCESS)
		return err;
	
	return SUCCESS;
}

EmErr dev_new_adder(EmName name, CElem** ptr) {
	
	CElem* adder;

	EmErr err = dev_new_celem(TYPE_CIRC_ELEM_NSEQ, &adder);
	if (err != SUCCESS)
		return err;
	
	err = adder->add_port(adder, TYPE_PORT_INPUT, ID_PORT_ADDER_INA, NAME_ADDER_INA, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	
	err = adder->add_port(adder, TYPE_PORT_INPUT, ID_PORT_ADDER_INB, NAME_ADDER_INB, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	
	err = adder->add_port(adder, TYPE_PORT_OUTPUT, ID_PORT_ADDER_OUT, NAME_ADDER_OUT, WIDTH_DATA);
	if (err != SUCCESS)
		return err;
	
	err = adder->add_port(adder, TYPE_PORT_OUTPUT, ID_PORT_ADDER_CARRY, NAME_ADDER_CARRY, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	
	err = adder->add_port(adder, TYPE_PORT_OUTPUT, ID_PORT_ADDER_ZERO, NAME_ADDER_ZERO, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	
	err = adder->add_port(adder, TYPE_PORT_OUTPUT, ID_PORT_ADDER_NEG, NAME_ADDER_NEG, WIDTH_EN);
	if (err != SUCCESS)
		return err;
	
	adder->name = name;
	adder->transition = _dev_adder_tf;

	*ptr = adder;

	return SUCCESS;

}