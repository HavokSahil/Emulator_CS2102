#include <stdio.h>
#include <common_types.h>
#include <err_codes.h>
#include <api.h>

EmErr print_values(API* api) {
	EmData buffer[2];

	EmErr err = api->get(api, TYPE_CELEM_PC, buffer);
	if (err != SUCCESS)
		return err;
	
	printf("Program Counter: %08X\n", buffer[0]);
	
	err = api->get(api, TYPE_CELEM_SP, buffer);
	if (err != SUCCESS)
		return err;

	printf("Stack Pointer: %08X\n", buffer[0]);
	
	err = api->get(api, TYPE_CELEM_RA, buffer);
	if (err != SUCCESS)
		return err;

	printf("Register A: %08X\n", buffer[0]);
	
	err = api->get(api, TYPE_CELEM_RB, buffer);
	if (err != SUCCESS)
		return err;

	printf("Register B: %08X\n", buffer[0]);

	err = api->get(api, TYPE_CELEM_MEM, buffer);
	if (err != SUCCESS)
		return err;	

	printf("Memory A: %08X\n", buffer[0]);
	printf("Memory B: %08X\n", buffer[1]);

	return SUCCESS;
}

int test_api() {

	API* api;
	EmErr err = get_api(&api);
	if (err != SUCCESS)
		return err;
	
	FILE* file = fopen("machine.bin", "r");
	if (file == NULL)
		return ERR_INV_FILE;
	
	err = api->load(api, file);
	if (err != SUCCESS)
		return err;


	FILE* dump = fopen("dump.bin", "w");
	err = api->dump_mem(api, dump);
	if (err != SUCCESS)
		return err;

	fclose(file);
	fclose(dump);

	EmSize iter;
	for (iter = 0; iter < 100; iter++) {
		printf("\nClock: %d\n------------------------------\n", iter);

		err = api->clock(api, 1);

		if (err == STATUS_PROG_HALT){
			err = print_values(api);
			if (err != SUCCESS)
				return err;
			printf("Program End\n");
			break;
		}

		if (err != SUCCESS)
			return err;

		err = print_values(api);
		if (err != SUCCESS)
			return err;
	}

	EmData buffer;
	

	return SUCCESS;
}

int main() {
	EmErr err;
	err = test_api();
	if (err != SUCCESS)
		return err;

	return SUCCESS;
}
