
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

static EmErr _api_get_memory(DP* dp, EmData* buffer_1, EmData* buffer_2) {
    if (dp == NULL || dp->mem_code == NULL || dp->mem_data == NULL)
        return ERR_INV_PTR;
    
    Port* port_a;
    EmErr err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &port_a);
    if (err != SUCCESS)
        return err;

    err = port_a->inspect(port_a, buffer_1);
    if (err != SUCCESS)
        return err;
    
    Port* port_b;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &port_b);
    if (err != SUCCESS)
        return err;
    
    err = port_b->inspect(port_b, buffer_2);
    if (err != SUCCESS)
        return err;
    
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
            err = _api_get_memory(api->_dp, buffer, buffer + 1);
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
    api->restart = NULL;
    api->get = _api_get;
    api->dump_mem = _api_dump_memory;
    api->clock = _api_clock;
    api->destroy = _api_destroy;

    *ptr = api;

    return SUCCESS;
}
