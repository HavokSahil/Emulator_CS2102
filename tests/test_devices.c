#include <stdio.h>
#include <common_types.h>
#include <err_codes.h>
#include <devices.h>

int test_bus() {
	return SUCCESS;
}

int test_port() {
	return SUCCESS;
}

int test_celem() {
	printf("*******************************************\nTesting Circuit Element\n*******************************************\n");
	CElem* celem;
	EmErr err = dev_new_celem(TYPE_CIRC_ELEM_SEQ, &celem);
	if (err != SUCCESS)
		return err;
	
	err = celem->add_port(celem, TYPE_PORT_INPUT, ID_PORT_TEST0, NAME_PORT_WADDR, WIDTH_ADDR);
	if (err != SUCCESS)
		return err;

	err = celem->add_port(celem, TYPE_PORT_OUTPUT, ID_PORT_TEST1, NAME_PORT_RADDR, WIDTH_ADDR);
	if (err != SUCCESS)
		return err;

	debug_print_celem(celem);

	Port* port1;
	err = celem->get_port(celem, TYPE_PORT_INPUT, ID_PORT_TEST0, &port1);
	if (err != SUCCESS)
		return err;

	Port* port2;
	err = celem->get_port(celem, TYPE_PORT_OUTPUT, ID_PORT_TEST1, &port2);
	if (err != SUCCESS)
		return err;
	
	Bus* bus;
	err = dev_new_bus(port2, port2->width, 0, &bus);
	if (err != SUCCESS)
		return err;

	err = port1->connect(port1, bus);
	if (err != SUCCESS)
		return err;
	
	port2->update(port2, 89);
	debug_print_port(port1);
	debug_print_port(port2);
	debug_print_bus(bus);

	return SUCCESS;
}

int test_register() {
		printf("*******************************************\nTesting Register Element\n*******************************************\n");
CElem* regA;
	CElem* regB;
	EmErr err = dev_new_register(1, &regA);
	if (err != SUCCESS)
		return err;
	err = dev_new_register(2, &regB);
	if (err != SUCCESS)
		return err;

	Port* wenA;
	err = regA->get_port(regA, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &wenA);
	if (err != SUCCESS)
		return err;

	Port* wenB;
	err = regB->get_port(regB, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &wenB);
	if (err != SUCCESS)
		return err;

	Port* dinA;
	err = regA->get_port(regA, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &dinA);
	if (err != SUCCESS)
		return err;

	Port* doutA;
	err = regA->get_port(regA, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &doutA);	
	if (err != SUCCESS)
		return err;

	Port* dinB;
	err = regB->get_port(regB, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &dinB);
	if (err != SUCCESS)
		return err;

	Port* doutB;
	err = regB->get_port(regB, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &doutB);
	if (err != SUCCESS)
		return err;

	Bus* dbus;
	err = dev_new_bus(doutA, doutA->width, 0, &dbus);
	if (err != SUCCESS)
		return err;
	
	err = dinB->connect(dinB, dbus);
	if (err != SUCCESS)
		return err;

	wenA->state = DISABLE;
	doutA->state = 100;
	dinA->state = 200;
	wenB->state = ENABLE;
	
	printf("\nClock Pulse\n");
	debug_print_port(dinA);
	debug_print_port(doutA);
	debug_print_port(dinB);
	debug_print_port(doutB);
	
	err = regA->transition(regA);
	if (err != SUCCESS)
		return err;
	
	printf("\nClock Pulse\n");
	debug_print_port(dinA);
	debug_print_port(doutA);
	debug_print_port(dinB);
	debug_print_port(doutB);

	err = regB->transition(regB);
	if (err != SUCCESS)
		return err;

	printf("\nClock Pulse\n");
	debug_print_port(dinA);
	debug_print_port(doutA);
	debug_print_port(dinB);
	debug_print_port(doutB);


	return SUCCESS;
}

int test_mux() {
	printf("*******************************************\nTesting MuxElement Element\n*******************************************\n");
	CElem* mux4;
	EmErr err = dev_new_mux(NAME_MUX_2X1, SIZE_MUX_4X1, &mux4);
	if (err != SUCCESS)
		return err;
	
	debug_print_celem(mux4);

	Port* portA;
	err = mux4->get_port(mux4, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INA, &portA);
	if (err != SUCCESS)
		return err;

	Port* portB;
	err = mux4->get_port(mux4, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INB, &portB);
	if (err != SUCCESS)
		return err;
	
	Port* portC;
	err = mux4->get_port(mux4, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INC, &portC);
	if (err != SUCCESS)
		return err;

	Port* portD;
	err = mux4->get_port(mux4, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_IND, &portD);
	if (err != SUCCESS)
		return err;


	Port* ctrl;
	err = mux4->get_port(mux4, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_CTR, &ctrl);
	if (err != SUCCESS)
		return err;
	
	Port* out;
	err = mux4->get_port(mux4, TYPE_PORT_OUTPUT, ID_PORT_MUX_4X1_OUT, &out);
	if (err != SUCCESS)
		return err;

	
	portA->state = 15;
	portB->state = 15412;
	portC->state = 3253;
	portD->state = 325;
	ctrl->state = 2;
	
	err = mux4->transition(mux4);
	if (err != SUCCESS)
		return err;

	EmState state;
	err = out->inspect(out, &state);
	if (err != SUCCESS)
		return err;
	
	printf("The state is %d\n", state);
	debug_print_port(portA);
	debug_print_port(portB);
	debug_print_port(portC);
	debug_print_port(portD);
	debug_print_port(ctrl);
	debug_print_port(out);
	return SUCCESS;
}

int test_memory() {
	printf("*******************************************\nTesting Memory Element\n*******************************************\n");
	CElem* mem;
	EmErr err = dev_new_memory(NAME_MEM_40K, &mem);
	if (err != SUCCESS)
		return err;
	
	debug_print_celem(mem);

	Port* wen;
	err = mem->get_port(mem, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, &wen);
	if (err != SUCCESS)
		return err;
	
	Port* raddr_a;
	err = mem->get_port(mem, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_A, &raddr_a);
	if (err != SUCCESS)
		return err;
	
	Port* raddr_b;
	err = mem->get_port(mem, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_B, &raddr_b);
	if (err != SUCCESS)
		return err;
	
	Port* waddr;
	err = mem->get_port(mem, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, &waddr);
	if (err != SUCCESS)
		return err;
	
	Port* din;
	err = mem->get_port(mem, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &din);
	if (err != SUCCESS)
		return err;

	Port* dout_a;
	err = mem->get_port(mem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &dout_a);
	if (err != SUCCESS)
		return err;
	
	Port* dout_b;
	err = mem->get_port(mem, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &dout_b);
	if (err != SUCCESS)
		return err;
	
	wen->state = ENABLE;
	raddr_a->state = 0;
	raddr_b->state = 1;
	waddr->state = 0;
	din->state = 0x12345678;

	err = mem->transition(mem);
	if (err != SUCCESS)
		return err;
	
	printf("First Read\n");
	debug_print_port(wen);
	debug_print_port(raddr_a);
	debug_print_port(raddr_b);
	debug_print_port(waddr);
	debug_print_port(din);
	debug_print_port(dout_a);
	debug_print_port(dout_b);

	wen->state = ENABLE;
	waddr->state = 1;
	din->state = 0x87654321;

	err = mem->transition(mem);
	if (err != SUCCESS)
		return err;

	printf("Second Read\n");

	debug_print_port(wen);
	debug_print_port(raddr_a);
	debug_print_port(raddr_b);
	debug_print_port(waddr);
	debug_print_port(din);
	debug_print_port(dout_a);
	debug_print_port(dout_b);

	Port* reset;
	err = mem->get_port(mem, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, &reset);
	if (err != SUCCESS)
		return err;

	reset->state = ENABLE;
	err = mem->transition(mem);
	if (err != SUCCESS)
		return err;

	printf("Reset\n");
	debug_print_port(wen);
	debug_print_port(raddr_a);
	debug_print_port(raddr_b);
	debug_print_port(waddr);
	debug_print_port(din);
	debug_print_port(dout_a);
	debug_print_port(dout_b);	

	return SUCCESS;
}

int test_alu() {

	printf("*******************************************\nTesting ALU Element\n*******************************************\n");

	CElem* alu;
	EmErr err = dev_new_alu(NAME_ALU_OP, &alu);
	if (err != SUCCESS)
		return err;
	
	debug_print_celem(alu);

	Port* op;
	err = alu->get_port(alu, TYPE_PORT_INPUT, ID_PORT_ALU_OP, &op);
	if (err != SUCCESS)
		return err;
	
	Port* ina;
	err = alu->get_port(alu, TYPE_PORT_INPUT, ID_PORT_ALU_INA, &ina);
	if (err != SUCCESS)
		return err;
	
	Port* inb;
	err = alu->get_port(alu, TYPE_PORT_INPUT, ID_PORT_ALU_INB, &inb);
	if (err != SUCCESS)
		return err;
	
	Port* out;
	err = alu->get_port(alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_OUT, &out);
	if (err != SUCCESS)
		return err;
	
	Port* zero;
	err = alu->get_port(alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_ZERO, &zero);
	if (err != SUCCESS)
		return err;
	
	Port* neg;
	err = alu->get_port(alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_NEG, &neg);
	if (err != SUCCESS)
		return err;
	
	Port* carry;
	err = alu->get_port(alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_CARRY, &carry);
	if (err != SUCCESS)
		return err;
	
	op->state = 0;
	ina->state = 0x0FFFFFFF;
	inb->state = 0x01;

	err = alu->transition(alu);
	if (err != SUCCESS)
		return err;
	
	printf("First Operation\n");
	debug_print_port(op);
	debug_print_port(ina);
	debug_print_port(inb);
	debug_print_port(out);
	debug_print_port(zero);
	debug_print_port(neg);
	debug_print_port(carry);

	return SUCCESS;
}

int main() {
	int err = test_celem();
	if (err != SUCCESS)
		return err;
	err = test_register();
	if (err != SUCCESS)
		return err;
	err = test_mux();
	if (err != SUCCESS)
		return err;
	err = test_memory();
	if (err != SUCCESS)
		return err;
	err = test_alu();
	if (err != SUCCESS)
		return err;
	return SUCCESS;
}
