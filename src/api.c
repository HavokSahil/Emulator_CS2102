
#include <api.h>

static EmErr _check_lsd(FILE* fp, EmBool* result) {
    if (fp == NULL)
        return ERR_INV_PTR;

    fseek(fp, 0, SEEK_SET);

    EmByte buffer[3];
    fread(buffer, 1, 3, fp);

    if (strncmp(buffer, "LSD", 3) == 0)
        *result = TRUE;
    else
        *result = FALSE;
    
    return SUCCESS;
}

static EmErr _is_data_available(FILE* file, EmBool* bool) {
    if (file == NULL)
        return ERR_INV_PTR;
    
    fseek(file, 3, SEEK_SET);

    EmByte buffer;

    fread(&buffer, 1, 1, file);

    if (buffer & 0x80)
        *bool = TRUE;
    else
        *bool = FALSE;
    
    return SUCCESS;
}

static EmErr _size_data_section(FILE* file, EmSize* size) {
    if (file == NULL)
        return ERR_INV_PTR;
    
    EmByte buffer[4];
    fseek(file, 8, SEEK_SET);
    fread(buffer, 1, 4, file);
    
    *size = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    *size = *size / 4; 
    return SUCCESS;
}

static EmErr _size_code_section(FILE* file, EmSize* size) {
    if (file == NULL)
        return ERR_INV_PTR;
    
    EmByte buffer[4];

    fread(buffer, 1, 4, file);

    if (strncmp(buffer, "TEXT", 4) != 0)
        return ERR_INV_FILE;
    
    fread(buffer, 1, 4, file);

    *size = (buffer[0] << 24) | (buffer[1] << 16) | (buffer[2] << 8) | buffer[3];
    *size = *size / 4;
    return SUCCESS;
}

static EmErr _get_data_section(FILE* file, EmSize size, EmData* buffer) {
    if (file == NULL)
        return ERR_INV_PTR;
    
    fseek(file, 12, SEEK_SET);

    EmSize iter;
    for (iter = 0; iter < size; iter++) {
        EmByte data[4];
        fread(data, 1, 4, file);
        buffer[iter] = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    }

    return SUCCESS;
}

static EmErr _get_code_section(FILE* file, EmSize size, EmData* buffer) {
    if (file == NULL)
        return ERR_INV_PTR;
    
    EmSize iter;
    for (iter = 0; iter < size; iter++) {
        EmByte data[4];
        fread(data, 1, 4, file);
        buffer[iter] = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
    }

    return SUCCESS;
}


static EmErr _api_load(API* api, FILE* fp) {
    
    if (api == NULL)
        return ERR_INV_PTR;
    
    if (fp == NULL)
        return ERR_INV_PTR;

    if (api->_dp == NULL)
        return ERR_INV_PTR;

    EmData* container;

    EmErr err = api->_dp->mem_data->dump_memory(api->_dp->mem_data, &container);
    if (err != SUCCESS)
        return err;
    
    memset(container, 0, SIZE_MEM * sizeof(EmData));
    
    EmBool bool;
    err = _check_lsd(fp, &bool);
    if (err != SUCCESS)
        return err;
    
    if (bool == FALSE) {
        free(api->_dp);
        return ERR_INV_FILE;
    }

    err = _is_data_available(fp, &bool);
    if (err != SUCCESS)
        return err;
    
    if (bool == FALSE) {
        free(api->_dp);
        return ERR_INV_FILE;
    }

    EmSize size;
    err = _size_data_section(fp, &size);
    if (err != SUCCESS)
        return err;
    
    EmData* buffer = (EmData*)malloc(size * sizeof(EmData));
    if (buffer == NULL) {
        free(api->_dp);
        return ERR_MEM_ALLOC;
    }

    err = _get_data_section(fp, size, buffer);
    if (err != SUCCESS) {
        free(buffer);
        free(api->_dp);
        return err;
    }

    EmSize iter;
    
    /* Write data section into the memory */
    for (iter = 0; iter < size; iter++) {
        container[iter + MEM_BEG_DATA_SEG] = buffer[iter];
    }

    free(buffer);

    err = _size_code_section(fp, &size);
    if (err != SUCCESS)
        return err;
    
    buffer = (EmData*)malloc(size * sizeof(EmData));
    if (buffer == NULL) {
        free(api->_dp);
        return ERR_MEM_ALLOC;
    }

    err = _get_code_section(fp, size, buffer);
    if (err != SUCCESS) {
        free(buffer);
        free(api->_dp);
        return err;
    }

    /* Write code section into the memory */
    for (iter = 0; iter < size; iter++) {
        EmData opcode = buffer[iter] & 0xFF;
        EmData operand = buffer[iter] >> 8;
        if (opcode == INSTR_LDL || opcode == INSTR_STL || opcode == INSTR_LDNL || opcode == INSTR_STNL) {
            container[iter] = opcode | (operand + MEM_BEG_DATA_SEG)<<8;
        }
        else
            container[iter] = buffer[iter];
    }

    free(buffer);

    return SUCCESS; 
}

static EmErr _api_dump_memory(API* api, FILE* fp) {
    if (api == NULL || fp == NULL || api->_dp == NULL)
        return ERR_INV_PTR;
    
    EmData *buffer;
    EmErr err = api->_dp->mem_code->dump_memory(api->_dp->mem_code, &buffer);
    if (err != SUCCESS)
        return err;

    EmSize iter;
    for (iter = 0; iter < SIZE_MEM; iter++) {
        fprintf(fp, "%08X %08X\n", iter, buffer[iter]);
    }
    
    return SUCCESS;
}

static EmErr _api_clock(API* api, EmSize cycles) {
    if (api == NULL || api->_dp == NULL)
        return ERR_INV_PTR;
    
    EmSize iter;
    for (iter = 0; iter < cycles; iter++) {
        EmErr err = api->_dp->clock(api->_dp);

        if (err != SUCCESS)
            return err;
    }

    return SUCCESS;
}

static EmErr _api_get_ra(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;

    if (dp->regA == NULL)
        return ERR_INV_PTR;

    Port* port;
    EmErr err = dp->regA->get_port(dp->regA, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &port);
    if (err != SUCCESS)
        return err;
    
    err = port->inspect(port, buffer);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _api_get_rb(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->regB == NULL)
        return ERR_INV_PTR;
    
    Port* port;
    EmErr err = dp->regB->get_port(dp->regB, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &port);
    if (err != SUCCESS)
        return err;

    err = port->inspect(port, buffer);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _api_get_pc(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->pc == NULL)
        return ERR_INV_PTR;
    
    Port* port;
    EmErr err = dp->pc->get_port(dp->pc, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &port);
    if (err != SUCCESS)
        return err;

    err = port->inspect(port, buffer);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _api_get_sp(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->sp == NULL)
        return ERR_INV_PTR;
    
    Port* port;
    EmErr err = dp->sp->get_port(dp->sp, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &port);
    if (err != SUCCESS)
        return err;

    err = port->inspect(port, buffer);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}


static EmErr _api_get_cu(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->cu == NULL)
        return ERR_INV_PTR;

    CElem* cu = dp->cu;
    
    Port* instr;
    EmErr err = cu->get_port(cu, TYPE_PORT_INPUT, ID_PORT_CU_INSTR, &instr);
    if (err != SUCCESS)
        return err;
    
    Port* mux_br;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_BR, &mux_br);
    if (err != SUCCESS)
        return err;
    
    Port* mux_br_fine;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_BR_FINE, &mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    Port* w_en_sp;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_SP, &w_en_sp);
    if (err != SUCCESS)
        return err;
    
    Port* w_en_b;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_B, &w_en_b);
    if (err != SUCCESS)
        return err;
    
    Port* w_en_a;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_A, &w_en_a);
    if (err != SUCCESS)
        return err;
    
    Port* mux_pc_in;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_PC_IN, &mux_pc_in);
    if (err != SUCCESS)
        return err;
    
    Port* w_en_pc;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_PC, &w_en_pc);
    if (err != SUCCESS)
        return err;
    
    Port* mux_alu_a;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_ALU_A, &mux_alu_a);
    if (err != SUCCESS)
        return err;

    Port* mux_alu_b;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_ALU_B, &mux_alu_b);
    if (err != SUCCESS)
        return err;

    Port* mux_a_in;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_A_IN, &mux_a_in);
    if (err != SUCCESS)
        return err;
    
    Port* mux_mem_in;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_MEM_IN, &mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    Port* w_en_mem;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_MEM, &w_en_mem);
    if (err != SUCCESS)
        return err;

    Port* alu_sel;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_ALU_SEL, &alu_sel);
    if (err != SUCCESS)
        return err;

    Port* imm;
    err = cu->get_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_IMM, &imm);
    if (err != SUCCESS)
        return err;

    EmState instr_val;
    err = instr->inspect(instr, &instr_val);
    if (err != SUCCESS)
        return err;

    EmState opcode = instr_val & 0x00FF;
    EmState imm_val = (instr_val & 0xFFFFFFF0)>>8;
    /* Handle negative imm val case */
    if (imm_val & (1<<23)) {
        imm_val = imm_val | 0xFFFF0000;
    }


    buffer[INDEX_PORT_CU_OPCODE] = opcode;
    buffer[INDEX_PORT_CU_INSTR] = instr_val;
    buffer[INDEX_PORT_CU_W_EN_SP] = w_en_sp->state;
    buffer[INDEX_PORT_CU_W_EN_B] = w_en_b->state;
    buffer[INDEX_PORT_CU_W_EN_A] = w_en_a->state;
    buffer[INDEX_PORT_CU_W_EN_PC] = w_en_pc->state;
    buffer[INDEX_PORT_CU_W_EN_MEM] = w_en_mem->state;
    buffer[INDEX_PORT_CU_MUX_PC_IN] = mux_pc_in->state;
    buffer[INDEX_PORT_CU_MUX_MEM_IN] = mux_mem_in->state;
    buffer[INDEX_PORT_CU_MUX_A_IN] = mux_a_in->state;
    buffer[INDEX_PORT_CU_MUX_BR] = mux_br->state;
    buffer[INDEX_PORT_CU_MUX_BR_FINE] = mux_br_fine->state;
    buffer[INDEX_PORT_CU_MUX_ALU_A] = mux_alu_a->state;
    buffer[INDEX_PORT_CU_MUX_ALU_B] = mux_alu_b->state;
    buffer[INDEX_PORT_CU_MUX_MEM_IN] = mux_mem_in->state;
    buffer[INDEX_PORT_CU_ALU_SEL] = alu_sel->state;
    buffer[INDEX_PORT_CU_IMM] = imm_val;
    
    return SUCCESS;
}

static EmErr _api_get_alu(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->alu == NULL)
        return ERR_INV_PTR;

    CElem* alu = dp->alu;
    
    Port* a;
    EmErr err = alu->get_port(alu, TYPE_PORT_INPUT, ID_PORT_ALU_INA, &a);
    if (err != SUCCESS)
        return err;
    
    Port* b;
    err = alu->get_port(alu, TYPE_PORT_INPUT, ID_PORT_ALU_INB, &b);
    if (err != SUCCESS)
        return err;
    
    Port* sel;
    err = alu->get_port(alu, TYPE_PORT_INPUT, ID_PORT_ALU_OP, &sel);
    if (err != SUCCESS)
        return err;
    
    
    Port* out;
    err = alu->get_port(alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_OUT, &out);
    if (err != SUCCESS)
        return err;
    
    buffer[0] = a->state;
    buffer[1] = b->state;
    buffer[2] = sel->state;
    buffer[3] = out->state;
    
    return SUCCESS;
}

static EmErr _api_get_memory(DP* dp, EmData* buffer) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->mem_code == NULL || dp->mem_data == NULL)
        return ERR_INV_PTR;

    Port* a;
    EmErr err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &a);
    if (err != SUCCESS)
        return err;
    
    Port* b;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &b);
    if (err != SUCCESS)
        return err;
    
    Port* in;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &in);
    if (err != SUCCESS)
        return err;
    
    Port* w_en;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, &w_en);
    if (err != SUCCESS)
        return err;
    
    Port* addr;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, &addr);
    if (err != SUCCESS)
        return err;

    Port* raddr_a;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_A, &raddr_a);
    if (err != SUCCESS)
        return err;
    
    Port* raddr_b;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_B, &raddr_b);
    if (err != SUCCESS)
        return err;

    buffer[INDEX_PORT_MEM_DOUT_A] = a->state;
    buffer[INDEX_PORT_MEM_DOUT_B] = b->state;
    buffer[INDEX_PORT_MEM_DIN] = in->state;
    buffer[INDEX_PORT_MEM_WEN] = w_en->state;
    buffer[INDEX_PORT_MEM_WADDR] = addr->state;
    buffer[INDEX_PORT_MEM_RADDR_A] = raddr_a->state;
    buffer[INDEX_PORT_MEM_RADDR_B] = raddr_b->state;

    return SUCCESS;
}


static EmErr _api_get(API* api, EmType type, EmByte* buffer) {
    if (api == NULL || api->_dp == NULL)
        return ERR_INV_PTR;
    
    EmErr err;
    switch (type) {
        case TYPE_CELEM_RA:
            err = _api_get_ra(api->_dp, buffer);
            break;
        case TYPE_CELEM_RB:
            err = _api_get_rb(api->_dp, buffer);
            break;
        case TYPE_CELEM_PC:
            err = _api_get_pc(api->_dp, buffer);
            break;
        case TYPE_CELEM_SP:
            err = _api_get_sp(api->_dp, buffer);
            break;
        case TYPE_CELEM_MEM:
            err = _api_get_memory(api->_dp, buffer);
            break;
        case TYPE_CELEM_ALU:
            err = _api_get_alu(api->_dp, buffer);
            break; 
        case TYPE_CELEM_CU:
            err = _api_get_cu(api->_dp, buffer);
            break;
        default:
            return ERR_INV_PTR;
    }

    return SUCCESS;
}

void _api_destroy(API* api) {
    if (api == NULL)
        return ;
    
    if (api->_dp != NULL)
        api->_dp->destroy(api->_dp);
    
    free(api);

    return;
}

static EmErr _api_reset(API* api) {
    if (api == NULL)
        return ERR_INV_PTR;
    
    if (api->_dp == NULL)
        return ERR_INV_PTR;
    
    EmErr err = api->_dp->restart(api->_dp);
    if (err != SUCCESS)
        return err;
    
    return err;
}

EmErr get_api(API** ptr) {
    
    if (ptr == NULL)
        return ERR_INV_PTR;
    
    API* api = (API*)malloc(sizeof(API));
    if (api == NULL)
        return ERR_MEM_ALLOC;
    
    DP* dp;
    EmErr err = dp_get_datapath(&dp);
    if (err != SUCCESS) {
        free(api);
        return err;
    }

    api->_dp = dp;
    api->reset = NULL;
    api->load = _api_load;
    api->restart = _api_reset;
    api->get = _api_get;
    api->dump_mem = _api_dump_memory;
    api->clock = _api_clock;
    api->destroy = _api_destroy;

    *ptr = api;

    return SUCCESS;
}
