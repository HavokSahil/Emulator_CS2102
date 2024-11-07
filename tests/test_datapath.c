#include <stdio.h>
#include <common_types.h>
#include <err_codes.h>
#include <datapath.h>

int test_data_path() {
	DP* dp;
	EmErr err = dp_get_datapath(&dp);
	if (err != SUCCESS) 
		return err;
	
	return SUCCESS;
}


static void print_register_staus(DP* dp) {
	EmState stateA;
	
	EmErr err = dp->inspect(dp, NAME_DP_REG_A, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &stateA);
	if (err != SUCCESS)
		return err;
	
	EmState stateB;
	err = dp->inspect(dp, NAME_DP_REG_B, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &stateB);
	if (err != SUCCESS)
		return err;
	
	EmState statePC;
	err = dp->inspect(dp, NAME_DP_PC, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &statePC);
	if (err != SUCCESS)
		return err;

	EmState stateSP;
	err = dp->inspect(dp, NAME_DP_SP, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &stateSP);
	if (err != SUCCESS)
		return err;

	printf("State of Register A: %d\n", stateA);
	printf("State of Register B: %d\n", stateB);
	printf("State of Program Counter: %d\n", statePC);
	printf("State of Stack Pointer: %d\n", stateSP);
}

static void print_bus(DP* dp) {
	if (dp == NULL)
		return;
	
	debug_print_bus(dp->bus_pc_adder);
	debug_print_bus(dp->bus_pc);
	debug_print_bus(dp->bus_ra);
	debug_print_bus(dp->bus_rb);
	debug_print_bus(dp->bus_sp);
	debug_print_bus(dp->bus_alu);
	debug_print_bus(dp->bus_alu_zero);
	debug_print_bus(dp->bus_alu_neg);
	debug_print_bus(dp->bus_cmem);
	debug_print_bus(dp->bus_dmem);
	debug_print_bus(dp->bus_mux_a_in);
	debug_print_bus(dp->bus_mux_mem_in);
	debug_print_bus(dp->bus_mux_pc_in);
	debug_print_bus(dp->bus_mux_br);
	debug_print_bus(dp->bus_mux_br_fine);
	debug_print_bus(dp->bus_mux_bz_pc);
	debug_print_bus(dp->bus_mux_bneg_pc);
	debug_print_bus(dp->bus_mux_alu_a);
	debug_print_bus(dp->bus_mux_alu_b);
}

void print_status(DP* dp) {
	dp_print_program_counter(dp);
	dp_print_cu(dp);
	dp_print_register_a(dp);
	dp_print_register_b(dp);
	dp_print_stack_pointer(dp);
	dp_print_mem_comp(dp);
	dp_print_adder(dp);
}

void dump_memory(DP* dp) {

	EmData* data;
	EmErr err = dp->mem_code->dump_memory(dp->mem_code, &data);
	if (err != SUCCESS)
		return err;
	
	if (data == NULL) {
		printf("EMPTY\n");
		return;
	}

	FILE* file = fopen("mem_dump.txt", "w");
	if (file == NULL) {
		printf("Error opening file\n");
		return;
	}
	
	EmSize iter;
	for (iter = 0; iter < SIZE_MEM; iter++) {
		fprintf(file,  "%08X %08X\n", iter, data[iter]);
	}

	fclose(file);
}

void print_buses(DP* dp) {
	if (dp == NULL)
		return;

	printf("Buses\n------------------------\n");
	printf("Bus PC Adder\n");
	debug_print_bus(dp->bus_pc_adder);
	printf("Bus PC\n");
	debug_print_bus(dp->bus_pc);
	printf("Bus RA\n");
	debug_print_bus(dp->bus_ra);
	printf("Bus RB\n");
	debug_print_bus(dp->bus_rb);
	printf("Bus SP\n");
	debug_print_bus(dp->bus_sp);
	printf("Bus ALU\n");
	debug_print_bus(dp->bus_alu);
	printf("Bus ALU Zero\n");
	debug_print_bus(dp->bus_alu_zero);
	printf("Bus ALU Neg\n");
	debug_print_bus(dp->bus_alu_neg);
	printf("Bus CMEM\n");
	debug_print_bus(dp->bus_cmem);
	printf("Bus DMEM\n");
	debug_print_bus(dp->bus_dmem);
	printf("Bus MUX A IN\n");
	debug_print_bus(dp->bus_mux_a_in);
	printf("Bus MUX MEM IN\n");
	debug_print_bus(dp->bus_mux_mem_in);
	printf("Bus MUX PC IN\n");
	debug_print_bus(dp->bus_mux_pc_in);
	printf("Bus MUX BR\n");
	debug_print_bus(dp->bus_mux_br);
	printf("Bus MUX BR Fine\n");
	debug_print_bus(dp->bus_mux_br_fine);
	printf("Bus MUX BZ PC\n");
	debug_print_bus(dp->bus_mux_bz_pc);
	printf("Bus MUX BNEG PC\n");
	debug_print_bus(dp->bus_mux_bneg_pc);
	printf("Bus MUX ALU A\n");
	debug_print_bus(dp->bus_mux_alu_a);
	printf("Bus MUX ALU B\n");
	debug_print_bus(dp->bus_mux_alu_b);
}

int test_get_data_path() {
	DP* dp;
	EmErr err = dp_get_datapath(&dp);
	if (err != SUCCESS)
		return err;
	

	EmData data[4] = {
		0x00000A00,
		0x00000B00,
		0x00000C00,
		0x00000D00
	};

	err = dp->load(dp, data, 4);
	if (err != SUCCESS)
		return err;

	print_status(dp);
	err = dp->clock(dp);
	if (err != SUCCESS)
		return err;
	print_status(dp);
	err = dp->clock(dp);
	if (err != SUCCESS)
		return err;
	print_status(dp);
	err = dp->clock(dp);
	if (err != SUCCESS)
		return err;
	print_status(dp);

	return SUCCESS;
}


int main() {
	
	EmErr err = test_data_path();
	if (err != SUCCESS)
		return err;
	
	err = test_get_data_path();
	if (err != SUCCESS)
		return err;
	
	return 0;
}
