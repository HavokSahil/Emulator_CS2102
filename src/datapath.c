#include <datapath.h>
#include <err_codes.h>
#include <stdlib.h>
#include <common_types.h>


/*give the function to update port for each instruction given in the table and take only those ports as parameter in function that are required*/

static EmErr _dp_control_unit_ldc(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;
    
    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 1);
    if (err != SUCCESS)
        return err;
    
    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;
    
    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;
    
    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;
    
    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;
    
    err = mux_alu_a->update(mux_alu_a, 3);  
    if (err != SUCCESS)
        return err;
    
    err = mux_alu_b->update(mux_alu_b, 0);
    if (err != SUCCESS)
        return err;
    
    err = mux_a_in->update(mux_a_in, 2);
    if (err != SUCCESS)
        return err;
    
    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;
    
    err = alu_sel->update(alu_sel, 0);  
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_control_unit_adc(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;
    
    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;
    
    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;
    
    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;
    
    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;
    
    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;
    
    err = mux_alu_a->update(mux_alu_a, 1);  
    if (err != SUCCESS)
        return err;
    
    err = mux_alu_b->update(mux_alu_b, 0);  
    if (err != SUCCESS)
        return err;
    
    err = mux_a_in->update(mux_a_in, 2);  
    if (err != SUCCESS)
        return err;
    
    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;
    
    err = alu_sel->update(alu_sel, 0);  
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_control_unit_ldl(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;
    
    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;
    
    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;
    
    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;
    
    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;
    
    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;
    
    err = mux_alu_a->update(mux_alu_a, 2);  
    if (err != SUCCESS)
        return err;
    
    err = mux_alu_b->update(mux_alu_b, 0);  
    if (err != SUCCESS)
        return err;
    
    err = mux_a_in->update(mux_a_in, 2);  
    if (err != SUCCESS)
        return err;
    
    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;
    
    err = alu_sel->update(alu_sel, 0);  
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_control_unit_stl(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, Port* mux_mem_in, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 1); 
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 0); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0); 
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_ldnl(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 0);
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1);
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0);
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2);
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_stnl(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, Port* mux_mem_in, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 1); 
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 0); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0); 
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_add(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 1);  
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);  
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1);  
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1);  
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0);  
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2);  
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0);  
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_sub(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 1); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_shl(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 2); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_shr(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 1);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1);  
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0);  
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2);  
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 3);  
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_adj(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 1); 
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 4); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_a2sp(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 1); 
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0); 
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 0); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0); 
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_sp2a(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);  
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);  
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);  
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 1);  
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);  
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 0);  
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);  
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 0);  
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0);  
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 3);  
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);  
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0);  
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_call(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 1); 
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 0); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 2); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 5); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_return(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 1);  
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);  
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);  
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0);  
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);  
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1);  
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);  
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1);  
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0);  
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 3);  
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 0);  
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 4);  
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_brz(Port* mux_br, Port* mux_br_fine, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 1);
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0);
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0);
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1);
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val);
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1);
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0);
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 1);
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 1);
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_brlz(Port* mux_br, Port* mux_br_fine, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 1); 
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0); 
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 1); 
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 1); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_br(Port* mux_br, Port* w_en_sp, Port* w_en_b, Port* w_en_a, Port* w_en_mem, Port* pc_w_en, Port* imm, Port* mux_alu_a, Port* mux_alu_b, Port* mux_a_in, Port* mux_pc_in, Port* alu_sel, EmState imm_val) {
    if (mux_br == NULL || w_en_sp == NULL || w_en_b == NULL || w_en_a == NULL || w_en_mem == NULL || pc_w_en == NULL || imm == NULL || mux_alu_a == NULL || mux_alu_b == NULL || mux_a_in == NULL || mux_pc_in == NULL || alu_sel == NULL)
        return ERR_INV_PTR;

    /* Update the ports */
    EmErr err = mux_br->update(mux_br, 1); 
    if (err != SUCCESS)
        return err;

    err = w_en_sp->update(w_en_sp, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_b->update(w_en_b, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_a->update(w_en_a, 0); 
    if (err != SUCCESS)
        return err;

    err = w_en_mem->update(w_en_mem, 0); 
    if (err != SUCCESS)
        return err;

    err = pc_w_en->update(pc_w_en, 1); 
    if (err != SUCCESS)
        return err;

    err = imm->update(imm, imm_val); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_a->update(mux_alu_a, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_alu_b->update(mux_alu_b, 0); 
    if (err != SUCCESS)
        return err;

    err = mux_a_in->update(mux_a_in, 1); 
    if (err != SUCCESS)
        return err;

    err = mux_pc_in->update(mux_pc_in, 1); 
    if (err != SUCCESS)
        return err;

    err = alu_sel->update(alu_sel, 0); 
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_control_unit_tf(CElem* cu) {

    if (cu == NULL)
        return ERR_INV_PTR;

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

    EmState opcode = instr_val & 0x000F;
    printf("The opcode value is %d\n", opcode);
    EmState imm_val = (instr_val & 0xFFF0)>>8;
    printf("The imm value is %d\n", imm_val);
    
    switch (opcode) {
        case INSTR_LDC:
            return _dp_control_unit_ldc(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_ADC:
            return _dp_control_unit_adc(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_LDL:
            return _dp_control_unit_ldl(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_STL:
            return _dp_control_unit_stl(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, mux_mem_in, imm_val);
        
        case INSTR_LDNL:
            return _dp_control_unit_ldnl(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_STNL:
            return _dp_control_unit_stnl(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, mux_mem_in, imm_val);
        
        case INSTR_ADD:
            return _dp_control_unit_add(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_SUB:
            return _dp_control_unit_sub(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_SHL:
            return _dp_control_unit_shl(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_SHR:
            return _dp_control_unit_shr(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_ADJ:
            return _dp_control_unit_adj(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_A2SP:
            return _dp_control_unit_a2sp(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_SP2A:
            return _dp_control_unit_sp2a(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_CALL:
            return _dp_control_unit_call(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_RETURN:
            return _dp_control_unit_return(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, TYPE_INSTR_IMM_NONE);
        
        case INSTR_BRZ:
            return _dp_control_unit_brz(mux_br, mux_br_fine, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_BRLZ:
            return _dp_control_unit_brlz(mux_br, mux_br_fine, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        case INSTR_BR:
            return _dp_control_unit_br(mux_br, w_en_sp, w_en_b, w_en_a, w_en_mem, w_en_pc, imm, mux_alu_a, mux_alu_b, mux_a_in, mux_pc_in, alu_sel, imm_val);
        
        default:
            return ERR_INV_INSTR; 
    }
    
    return ERR_INV_INSTR;
}

static EmErr _dp_get_control_unit(CElem** ptr) {

    if (ptr == NULL)
        return ERR_INV_PTR;
    
    CElem* cu;
    EmErr err = dev_new_celem(TYPE_CIRC_ELEM_NSEQ, &cu);
    if (err != SUCCESS)
        return err;

    err = cu->add_port(cu, TYPE_PORT_INPUT, ID_PORT_CU_INSTR, NAME_CU_OUT, WIDTH_PORT_CU_INSTR);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_BR, NAME_CU_OUT, WIDTH_PORT_CU_MUX_BR);
    if (err != SUCCESS)
        return  err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_BR_FINE, NAME_CU_OUT, WIDTH_PORT_CU_MUX_BR_FINE);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_SP, NAME_CU_OUT, WIDTH_PORT_CU_W_EN_SP);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_B, NAME_CU_OUT, WIDTH_PORT_CU_W_EN_B);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_A, NAME_CU_OUT, WIDTH_PORT_CU_W_EN_A);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_PC_IN, NAME_CU_OUT, WIDTH_PORT_CU_MUX_PC_IN);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_PC, NAME_CU_OUT, WIDTH_PORT_CU_W_EN_PC);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_ALU_A, NAME_CU_OUT, WIDTH_PORT_CU_MUX_ALU_A);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_ALU_B, NAME_CU_OUT, WIDTH_PORT_CU_MUX_ALU_B);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_MEM_IN, NAME_CU_OUT, WIDTH_PORT_CU_MUX_MEM_IN);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_MEM, NAME_CU_OUT, WIDTH_PORT_CU_W_EN_MEM);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_IMM, NAME_CU_OUT, WIDTH_PORT_CU_IMM);
    if (err != SUCCESS)
        return err;
    
    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_A_IN, NAME_CU_OUT, WIDTH_PORT_CU_MUX_A_IN);
    if (err != SUCCESS)
        return err;

    err = cu->add_port(cu, TYPE_PORT_OUTPUT, ID_PORT_CU_ALU_SEL, NAME_CU_OUT, WIDTH_PORT_CU_ALU_SEL);
    if (err != SUCCESS)
        return err;
    
    cu->transition = _dp_control_unit_tf;
    *ptr = cu;

    return SUCCESS;

}

static EmErr _dp_create_elements(DP* dp) {
    
    if (dp == NULL)
        return ERR_INV_PTR;

    /* Create the Control Unit */
    EmErr err = _dp_get_control_unit(&(dp->cu));
    if (err != SUCCESS)
        return err;

    /* Create the Register A Element */
    err = dev_new_register(NAME_DP_REG_A, &(dp->regA));
    if (err != SUCCESS)
        return err;

    /* Create the Register B Element */
    err = dev_new_register(NAME_DP_REG_B, &(dp->regB));
    if (err != SUCCESS)
        return err;
    
    /* Create the ALU Element */
    err = dev_new_alu(NAME_DP_ALU, &(dp->alu));
    if (err != SUCCESS)
        return err;
    
    /* Create the Memory Element */
    err = dev_new_memory(NAME_DP_MEM_CODE, &(dp->mem_code));
    if (err != SUCCESS)
        return err;

    dp->mem_data = dp->mem_code;
    
    /* Create the Program Counter Element */
    err = dev_new_register(NAME_DP_PC, &(dp->pc));
    if (err != SUCCESS)
        return err;
    
    /* Create the Stack Pointer Element */
    err = dev_new_register(NAME_DP_SP, &(dp->sp));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux A Input Element */
    err = dev_new_mux(NAME_DP_MUX_A_IN, SIZE_MUX_4X1, &(dp->mux_a_in));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux Memory Input Element */
    err = dev_new_mux(NAME_DP_MUX_MEM_IN, SIZE_MUX_2X1, &(dp->mux_mem_in));
    if (err != SUCCESS)
        return err;

    /* Create the Mux PC Input Element */
    err = dev_new_mux(NAME_DP_MUX_PC_IN, SIZE_MUX_2X1, &(dp->mux_pc_in));
    if (err != SUCCESS)
        return err;

    /* Create the Mux Branch Element */
    err = dev_new_mux(NAME_DP_MUX_BR, SIZE_MUX_2X1, &(dp->mux_br));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux Branch Fine Element */
    err = dev_new_mux(NAME_DP_MUX_BR_FINE, SIZE_MUX_2X1, &(dp->mux_br_fine));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux Branch Zero PC Element */
    err = dev_new_mux(NAME_DP_MUX_BZ_PC, SIZE_MUX_2X1, &(dp->mux_bz_pc));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux Branch Negative PC Element */
    err = dev_new_mux(NAME_DP_MUX_BNEG_PC, SIZE_MUX_2X1, &(dp->mux_bneg_pc));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux ALU A Element */
    err = dev_new_mux(NAME_DP_MUX_ALU_A, SIZE_MUX_4X1, &(dp->mux_alu_a));
    if (err != SUCCESS)
        return err;
    
    /* Create the Mux ALU B Element */
    err = dev_new_mux(NAME_DP_MUX_ALU_B, SIZE_MUX_4X1, &(dp->mux_alu_b));
    if (err != SUCCESS)
        return err;

    /* Create the PC Adder Element */
    err = dev_new_adder(NAME_DP_PC_ADDER, &(dp->pc_adder));
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

/* For each output ports in the circuit, define a function to connect to all its input slaves */

static EmErr _dp_connect_pc_out(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;

    Port* pc_out;
    EmErr err = dp->pc->get_port(dp->pc, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &pc_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(pc_out, pc_out->width, BUS_PC ,&bus);
    if (err != SUCCESS)
        return err;

    dp->bus_pc = bus;

    /* Gather all the slave Devices */
    if (dp->mux_a_in == NULL || dp->mux_alu_a == NULL || dp->pc_adder == NULL || dp->mem_code == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_a_in;
    err = dp->mux_a_in->get_port(dp->mux_a_in, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INA, &sl_mux_a_in);
    if (err != SUCCESS)
        return err;

    Port* sl_mux_alu_a;
    err = dp->mux_alu_a->get_port(dp->mux_alu_a, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INA, &sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    Port* sl_pc_adder;
    err = dp->pc_adder->get_port(dp->pc_adder, TYPE_PORT_INPUT, ID_PORT_ADDER_INA, &sl_pc_adder);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mem_code;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_A, &sl_mem_code);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_pc_adder);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mem_code);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_pc_adder(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* pc_adder_out;
    EmErr err = dp->pc_adder->get_port(dp->pc_adder, TYPE_PORT_OUTPUT, ID_PORT_ADDER_OUT, &pc_adder_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(pc_adder_out, pc_adder_out->width, BUS_PC_ADDER, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_pc_adder = bus;

    /* Gather all the slave Devices */
    if (dp->mux_pc_in == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_pc_in;
    err = dp->mux_pc_in->get_port(dp->mux_pc_in, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &sl_mux_pc_in);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_pc_in);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_connect_ra(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* ra_out;
    EmErr err = dp->regA->get_port(dp->regA, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &ra_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(ra_out, ra_out->width, BUS_RA, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_ra = bus;

    /* Gather all the slave Devices */
    if (dp->mux_alu_a == NULL || dp->mux_alu_b == NULL || dp->regB == NULL || dp->mux_mem_in == NULL)
        return ERR_INV_PTR;

    /* Gather Slave Ports */
    Port* sl_mux_alu_a;
    err = dp->mux_alu_a->get_port(dp->mux_alu_a, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INB, &sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_alu_b;
    err = dp->mux_alu_b->get_port(dp->mux_alu_b, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_IND, &sl_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    Port* sl_regB;
    err = dp->regB->get_port(dp->regB, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &sl_regB);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_mem_in;
    err = dp->mux_mem_in->get_port(dp->mux_mem_in, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, &sl_mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_regB);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_rb(DP* dp) {

    if (dp->regB == NULL)
        return ERR_INV_PTR;
    
    Port* rb_out;
    EmErr err = dp->regB->get_port(dp->regB, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &rb_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(rb_out, rb_out->width, BUS_RB, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_rb = bus;

    /* Gather all the slave Devices */
    if (dp->mux_a_in == NULL || dp->mux_alu_b == NULL || dp->mux_mem_in == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_a_in;
    err = dp->mux_a_in->get_port(dp->mux_a_in, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_IND, &sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_alu_b;
    err = dp->mux_alu_b->get_port(dp->mux_alu_b, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INB, &sl_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_mem_in;
    err = dp->mux_mem_in->get_port(dp->mux_mem_in, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &sl_mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_sp(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* sp_out;
    EmErr err = dp->sp->get_port(dp->sp, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &sp_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(sp_out, sp_out->width, BUS_SP, &bus);
    if (err != SUCCESS)
        return err;

    dp->bus_sp = bus;

    /* Gather all the slave Devices */
    if (dp->mux_alu_a == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_alu_a;
    err = dp->mux_alu_a->get_port(dp->mux_alu_a, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INC, &sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_alu(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;

    Port* alu_out;
    EmErr err = dp->alu->get_port(dp->alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_OUT, &alu_out);
    if (err != SUCCESS)
        return err;

    Port* alu_carry;
    err = dp->alu->get_port(dp->alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_CARRY, &alu_carry);
    if (err != SUCCESS)
        return err;
    
    Port* alu_zero;
    err = dp->alu->get_port(dp->alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_ZERO, &alu_zero);
    if (err != SUCCESS)
        return err;
    
    Port* alu_neg;
    err = dp->alu->get_port(dp->alu, TYPE_PORT_OUTPUT, ID_PORT_ALU_NEG, &alu_neg);
    if (err != SUCCESS)
        return err;
    
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(alu_out, alu_out->width, BUS_ALU, &bus);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_alu_zero = NULL;
    err = dev_new_bus(alu_zero, alu_zero->width, BUS_ALU_ZERO, &bus_alu_zero);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_alu_neg = NULL;
    err = dev_new_bus(alu_neg, alu_neg->width, BUS_ALU_NEG, &bus_alu_neg);
    if (err != SUCCESS)
        return err;
    
    dp->bus_alu = bus;
    dp->bus_alu_zero = bus_alu_zero;
    dp->bus_alu_neg = bus_alu_neg;

    /* Gather all the slave Devices */
    if (dp->mux_a_in == NULL || dp->mem_data == NULL || dp->sp == NULL || dp->mux_pc_in == NULL || dp->mem_data == NULL)
        return ERR_INV_PTR;

    if (dp->mux_bz_pc == NULL || dp->mux_bneg_pc == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_a_in;
    err = dp->mux_a_in->get_port(dp->mux_a_in, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INC, &sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mem_data;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &sl_mem_data);
    if (err != SUCCESS)
        return err;
    
    Port* sl_sp;
    err = dp->regB->get_port(dp->sp, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &sl_sp);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_pc_in;
    err = dp->mux_pc_in->get_port(dp->mux_pc_in, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, &sl_mux_pc_in);
    if (err != SUCCESS)
        return err;

    Port* sl_mux_bz_pc;
    err = dp->mux_bz_pc->get_port(dp->mux_bz_pc, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &sl_mux_bz_pc);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_bneg_pc;
    err = dp->mux_bneg_pc->get_port(dp->mux_bneg_pc, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &sl_mux_bneg_pc);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mem_wadd;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, &sl_mem_wadd);
    if (err != SUCCESS)
        return err;

    Port* sl_mem_rb;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_B, &sl_mem_rb);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mem_data);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_sp);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mux_pc_in);
    if (err != SUCCESS)
        return err;
    
    err = bus_alu_zero->connect(bus_alu_zero, sl_mux_bz_pc);
    if (err != SUCCESS)
        return err;
    
    err = bus_alu_neg->connect(bus_alu_neg, sl_mux_bneg_pc);
    if (err != SUCCESS)
        return err;

    err = bus->connect(bus, sl_mem_wadd);
    if (err != SUCCESS)
        return err;
    
    err = bus->connect(bus, sl_mem_rb);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_cmem(DP* dp) {
    
    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mem;
    EmErr err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &mem);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mem, mem->width, BUS_CMEM, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_cmem = bus;

    /* Gather all the slave Devices */
    if (dp->cu == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_cu;

    err = dp->cu->get_port(dp->cu, TYPE_PORT_INPUT, ID_PORT_CU_INSTR, &sl_cu);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_cu);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_connect_dmem(DP* dp) {
    
    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mem;
    EmErr err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &mem);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mem, mem->width, BUS_DMEM, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_dmem = bus;

    /* Gather all the slave Devices */
    if (dp->mux_a_in == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_a_in;
    err = dp->mux_a_in->get_port(dp->mux_a_in, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INB, &sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_a_in);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_connect_mux_a_in(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;

    Port* mux_a_in_out;
    EmErr err = dp->mux_a_in->get_port(dp->mux_a_in, TYPE_PORT_OUTPUT, ID_PORT_MUX_4X1_OUT, &mux_a_in_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_a_in_out, mux_a_in_out->width, BUS_MUX_A_IN, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_a_in = bus;

    /* Gather all the slave Devices */
    if (dp->regA == NULL)
        return ERR_INV_PTR;

    /* Gather Slave Ports */
    Port* sl_regA;
    err = dp->regA->get_port(dp->regA, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &sl_regA);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_regA);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_mem_in(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_mem_in_out;
    EmErr err = dp->mux_mem_in->get_port(dp->mux_mem_in, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &mux_mem_in_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_mem_in_out, mux_mem_in_out->width, BUS_MUX_MEM_IN, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_mem_in = bus;

    /* Gather all the slave Devices */
    if (dp->mem_data == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mem_data;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &sl_mem_data);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mem_data);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_pc_in(DP* dp) {
    
    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_pc_in_out;
    EmErr err = dp->mux_pc_in->get_port(dp->mux_pc_in, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &mux_pc_in_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_pc_in_out, mux_pc_in_out->width, BUS_MUX_PC_IN, &bus);    
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_pc_in = bus;

    /* Gather all the slave Devices */
    if (dp->pc == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_pc;
    err = dp->pc->get_port(dp->pc, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &sl_pc);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_pc);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_br(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_br_out;
    EmErr err = dp->mux_br->get_port(dp->mux_br, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &mux_br_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_br_out, mux_br_out->width, BUS_MUX_BR, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_br = bus;
    
    /* Gather all the slave Devices */
    if (dp->pc_adder == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_pc_adder;
    err = dp->pc_adder->get_port(dp->pc_adder, TYPE_PORT_INPUT, ID_PORT_ADDER_INB, &sl_pc_adder);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_pc_adder);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_br_fine(DP* dp) {
    
    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_br_fine_out;
    EmErr err = dp->mux_br_fine->get_port(dp->mux_br_fine, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &mux_br_fine_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_br_fine_out, mux_br_fine_out->width, BUS_MUX_BR_FINE, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_br_fine = bus;

    /* Gather all the slave Devices */
    if (dp->mux_br == NULL)
        return ERR_INV_PTR;

    /* Gather Slave Ports */
    Port* sl_mux_br;
    err = dp->mux_br->get_port(dp->mux_br, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &sl_mux_br);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_br);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_bz_pc(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_bz_out;
    EmErr err = dp->mux_bz_pc->get_port(dp->mux_bz_pc, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &mux_bz_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_bz_out, mux_bz_out->width, BUS_MUX_BZ_PC, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_bz_pc = bus;

    /* Gather all the slave Devices */
    if (dp->mux_br_fine == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_br_fine;
    err = dp->mux_br_fine->get_port(dp->mux_br_fine, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &sl_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_bneg(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;

    Port* mux_bneg_out;
    EmErr err = dp->mux_bneg_pc->get_port(dp->mux_bneg_pc, TYPE_PORT_OUTPUT, ID_PORT_MUX_2X1_OUT, &mux_bneg_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_bneg_out, mux_bneg_out->width, BUS_MUX_BNEG_PC, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_bneg_pc = bus;

    /* Gather all the slave Devices */
    if (dp->mux_br_fine == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_br_fine;
    err = dp->mux_br_fine->get_port(dp->mux_br_fine, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, &sl_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_alu_a(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_alu_a_out;
    EmErr err = dp->mux_alu_a->get_port(dp->mux_alu_a, TYPE_PORT_OUTPUT, ID_PORT_MUX_4X1_OUT, &mux_alu_a_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_alu_a_out, mux_alu_a_out->width, BUS_MUX_ALU_A, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_alu_a = bus;

    /* Gather all the slave Devices */
    if (dp->alu == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_alu_a;
    err = dp->alu->get_port(dp->alu, TYPE_PORT_INPUT, ID_PORT_ALU_INA, &sl_alu_a);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_alu_a);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_mux_alu_b(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    Port* mux_alu_b_out;
    EmErr err = dp->mux_alu_b->get_port(dp->mux_alu_b, TYPE_PORT_OUTPUT, ID_PORT_MUX_4X1_OUT, &mux_alu_b_out);
    if (err != SUCCESS)
        return err;
    
    /* Create the bus */
    Bus* bus = NULL;
    err = dev_new_bus(mux_alu_b_out, mux_alu_b_out->width, BUS_MUX_ALU_B, &bus);
    if (err != SUCCESS)
        return err;
    
    dp->bus_mux_alu_b = bus;

    /* Gather all the slave Devices */
    if (dp->alu == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_alu_b;
    err = dp->alu->get_port(dp->alu, TYPE_PORT_INPUT, ID_PORT_ALU_INB, &sl_alu_b);
    if (err != SUCCESS)
        return err;
    
    /* Connect the bus to the slave ports */
    err = bus->connect(bus, sl_alu_b);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_connect_control_element(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;

    Port* cu_mux_br;
    EmErr err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_BR, &cu_mux_br);
    if (err != SUCCESS)
        return err;
    
    Port* cu_mux_br_fine;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_BR_FINE, &cu_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    Port* cu_w_en_sp;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_SP, &cu_w_en_sp);
    if (err != SUCCESS)
        return err;
    
    Port* cu_w_en_b;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_B, &cu_w_en_b);
    if (err != SUCCESS)
        return err;
    
    Port* cu_w_en_a;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_A, &cu_w_en_a);
    if (err != SUCCESS)
        return err;
    
    Port* cu_mux_pc_in;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_PC_IN, &cu_mux_pc_in);
    if (err != SUCCESS)
        return err;
    
    Port* cu_w_en_pc;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_PC, &cu_w_en_pc);
    if (err != SUCCESS)
        return err;
    
    Port* cu_mux_alu_a;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_ALU_A, &cu_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    Port* cu_mux_a_in;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_A_IN, &cu_mux_a_in);
    if (err != SUCCESS)
        return err;

    Port* cu_alu_sel;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_ALU_SEL, &cu_alu_sel);
    if (err != SUCCESS)
        return err;
    
    Port* cu_mux_alu_b;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_ALU_B, &cu_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    Port* cu_mux_mem_in;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_MUX_MEM_IN, &cu_mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    Port* cu_w_en_mem;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_W_EN_MEM, &cu_w_en_mem);
    if (err != SUCCESS)
        return err;
    
    Port* cu_imm;
    err = dp->cu->get_port(dp->cu, TYPE_PORT_OUTPUT, ID_PORT_CU_IMM, &cu_imm);
    if (err != SUCCESS)
        return err;


    /* Create the bus */
    Bus* bus_cu_mux_br = NULL;
    err = dev_new_bus(cu_mux_br, cu_mux_br->width, BUS_CU_MUX_BR, &bus_cu_mux_br);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_mux_br_fine = NULL;
    err = dev_new_bus(cu_mux_br_fine, cu_mux_br_fine->width, BUS_CU_MUX_BR_FINE, &bus_cu_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_w_en_sp = NULL;
    err = dev_new_bus(cu_w_en_sp, cu_w_en_sp->width, BUS_CU_W_EN_SP, &bus_cu_w_en_sp);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_w_en_b = NULL;
    err = dev_new_bus(cu_w_en_b, cu_w_en_b->width, BUS_CU_W_EN_B, &bus_cu_w_en_b);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_w_en_a = NULL;
    err = dev_new_bus(cu_w_en_a, cu_w_en_a->width, BUS_CU_W_EN_A, &bus_cu_w_en_a);
    if (err != SUCCESS)
        return err;

    Bus* bus_cu_mux_pc_in = NULL;
    err = dev_new_bus(cu_mux_pc_in, cu_mux_pc_in->width, BUS_CU_MUX_PC_IN, &bus_cu_mux_pc_in);
    if (err != SUCCESS)
        return err;

    Bus* bus_cu_w_en_pc = NULL;
    err = dev_new_bus(cu_w_en_pc, cu_w_en_pc->width, BUS_CU_W_EN_PC, &bus_cu_w_en_pc);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_mux_alu_a = NULL;
    err = dev_new_bus(cu_mux_alu_a, cu_mux_alu_a->width, BUS_CU_MUX_ALU_A, &bus_cu_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_mux_a_in = NULL;
    err = dev_new_bus(cu_mux_a_in, cu_mux_a_in->width, BUS_CU_MUX_A_IN, &bus_cu_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_alu_sel = NULL;
    err = dev_new_bus(cu_alu_sel, cu_alu_sel->width, BUS_CU_ALU_SEL, &bus_cu_alu_sel);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_mux_alu_b = NULL;
    err = dev_new_bus(cu_mux_alu_b, cu_mux_alu_b->width, BUS_CU_MUX_ALU_B, &bus_cu_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_mux_mem_in = NULL;
    err = dev_new_bus(cu_mux_mem_in, cu_mux_mem_in->width, BUS_CU_MUX_MEM_IN, &bus_cu_mux_mem_in);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_w_en_mem = NULL;
    err = dev_new_bus(cu_w_en_mem, cu_w_en_mem->width, BUS_CU_W_EN_MEM, &bus_cu_w_en_mem);
    if (err != SUCCESS)
        return err;
    
    Bus* bus_cu_imm = NULL;
    err = dev_new_bus(cu_imm, cu_imm->width, BUS_CU_IMM, &bus_cu_imm);
    if (err != SUCCESS)
        return err;
    

    /* Gather all slave element */
    if (dp->mux_br == NULL || dp->mux_br_fine == NULL || dp->sp == NULL || dp->regB == NULL)
        return ERR_INV_PTR;
    
    if (dp->pc == NULL || dp->mux_alu_a == NULL || dp->mux_a_in == NULL || dp->alu == NULL)
        return ERR_INV_PTR;
    
    if (dp->mux_alu_b == NULL || dp->mem_data == NULL || dp->mux_mem_in == NULL)
        return ERR_INV_PTR;
    
    if (dp->mux_bz_pc == NULL || dp->mux_bneg_pc == NULL)
        return ERR_INV_PTR;
    
    /* Gather Slave Ports */
    Port* sl_mux_br;
    err = dp->mux_br->get_port(dp->mux_br, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &sl_mux_br);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_br_fine;
    err = dp->mux_br_fine->get_port(dp->mux_br_fine, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &sl_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    Port* sl_sp;
    err = dp->sp->get_port(dp->sp, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &sl_sp);
    if (err != SUCCESS)
        return err;
    
    Port* sl_regB;
    err = dp->regB->get_port(dp->regB, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &sl_regB);
    if (err != SUCCESS)
        return err;
    
    Port* sl_regA;
    err = dp->regA->get_port(dp->regA, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &sl_regA);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_pc_in;
    err = dp->mux_pc_in->get_port(dp->mux_pc_in, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &sl_mux_pc_in);
    if (err != SUCCESS)
        return err;
    
    Port* sl_w_en_pc;
    err = dp->pc->get_port(dp->pc, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &sl_w_en_pc);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_alu_a;
    err = dp->mux_alu_a->get_port(dp->mux_alu_a, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_CTR, &sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_a_in;
    err = dp->mux_a_in->get_port(dp->mux_a_in, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_CTR, &sl_mux_a_in);
    if (err != SUCCESS)
        return err;
    
    Port* alu_sel;
    err = dp->cu->get_port(dp->alu, TYPE_PORT_INPUT, ID_PORT_ALU_OP, &alu_sel);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mux_alu_b;
    err = dp->mux_alu_b->get_port(dp->mux_alu_b, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_CTR, &sl_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    Port* sl_mem_in;
    err = dp->mux_mem_in->get_port(dp->mux_mem_in, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_CTR, &sl_mem_in);
    if (err != SUCCESS)
        return err;
    
    Port* sl_w_en_mem;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, &sl_w_en_mem);
    if (err != SUCCESS)
        return err;

    Port* sl_imm;
    err = dp->mux_alu_b->get_port(dp->mux_alu_b, TYPE_PORT_INPUT, ID_PORT_MUX_4X1_INA, &sl_imm);
    if (err != SUCCESS)
        return err;

    Port* sl_mux_bz_pc;
    err = dp->mux_bz_pc->get_port(dp->mux_bz_pc, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, &sl_mux_bz_pc);
    if (err != SUCCESS)
        return err;

    Port* sl_mux_bneg_pc;
    err = dp->mux_bneg_pc->get_port(dp->mux_bneg_pc, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INB, &sl_mux_bneg_pc);
    if (err != SUCCESS)
        return err;
 
    
    /* Connect the bus to the slave ports */
    err = bus_cu_mux_br->connect(bus_cu_mux_br, sl_mux_br);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_mux_br_fine->connect(bus_cu_mux_br_fine, sl_mux_br_fine);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_w_en_sp->connect(bus_cu_w_en_sp, sl_sp);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_w_en_b->connect(bus_cu_w_en_b, sl_regB);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_w_en_a->connect(bus_cu_w_en_a, sl_regA);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_mux_pc_in->connect(bus_cu_mux_pc_in, sl_mux_pc_in);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_w_en_pc->connect(bus_cu_w_en_pc, sl_w_en_pc);
    if (err != SUCCESS)
        return err;

    err = bus_cu_mux_alu_a->connect(bus_cu_mux_alu_a, sl_mux_alu_a);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_mux_a_in->connect(bus_cu_mux_a_in, sl_mux_a_in);
    if (err != SUCCESS)
        return err;

    err = bus_cu_alu_sel->connect(bus_cu_alu_sel, alu_sel);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_mux_alu_b->connect(bus_cu_mux_alu_b, sl_mux_alu_b);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_mux_mem_in->connect(bus_cu_mux_mem_in, sl_mem_in);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_w_en_mem->connect(bus_cu_w_en_mem, sl_w_en_mem);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_imm->connect(bus_cu_imm, sl_imm);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_imm->connect(bus_cu_imm, sl_mux_bz_pc);
    if (err != SUCCESS)
        return err;
    
    err = bus_cu_imm->connect(bus_cu_imm, sl_mux_bneg_pc);
    if (err != SUCCESS)
        return err;

    
    return SUCCESS;
}

static EmErr _dp_connect_element(DP* dp) {

    EmErr err = _dp_connect_pc_out(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_pc_adder(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_ra(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_rb(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_sp(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_alu(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_cmem(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_dmem(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_mux_a_in(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_mux_mem_in(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_mux_pc_in(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_mux_br(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_mux_br_fine(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_mux_bz_pc(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_mux_bneg(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_mux_alu_a(dp);
    if (err != SUCCESS)
        return err;
    
    err = _dp_connect_mux_alu_b(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_control_element(dp);
    if (err != SUCCESS)
        return err;
    
    return SUCCESS;
}

static EmErr _dp_load_constants(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;

    if (dp->mux_bz_pc == NULL || dp->mux_bneg_pc == NULL || dp->mux_br == NULL)
        return ERR_INV_PTR;

    Port* mux_bz_pc_in;
    EmErr err = dp->mux_bz_pc->get_port(dp->mux_bz_pc, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &mux_bz_pc_in);
    if (err != SUCCESS)
        return err;
    
    Port* mux_bneg_pc_in;
    err = dp->mux_bneg_pc->get_port(dp->mux_bneg_pc, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &mux_bneg_pc_in);
    if (err != SUCCESS)
        return err;

    Port* mux_br_in;
    err = dp->mux_br->get_port(dp->mux_br, TYPE_PORT_INPUT, ID_PORT_MUX_2X1_INA, &mux_br_in);
    if (err != SUCCESS)
        return err;
    
    /* Load the constants */
    mux_bz_pc_in->state = 1;
    mux_bneg_pc_in->state = 1;
    mux_br_in->state = 1;

    return SUCCESS;
}

static EmErr _dp_load(DP* dp, EmData* data, EmSize size) {
    if (dp == NULL || data == NULL)
        return ERR_INV_PTR;

    if (dp->mem_code == NULL)
        return ERR_INV_PTR;
    
    EmInt iter;
    Port* mem_rst;
    EmErr err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, &mem_rst);
    if (err != SUCCESS)
        return err;

    mem_rst->state = ENABLE;
    err = dp->mem_code->transition(dp->mem_code);
    if (err != SUCCESS)
        return err;

    mem_rst->state = DISABLE;

    Port* mem_wen;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, &mem_wen);
    if (err != SUCCESS)
        return err;
    
    mem_wen->state = ENABLE;

    Port* mem_add;
    Port* mem_dat;

    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, &mem_add);
        if (err != SUCCESS)
            return err;
        
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &mem_dat);
    if (err != SUCCESS)
        return err;

    for (iter = 0; iter < size; iter++) {
        EmData d = data[iter];
        
        mem_add->state = iter;
        mem_dat->state = d;

        err = dp->mem_code->transition(dp->mem_code);
        if (err != SUCCESS)
            return err;
    }

    err = dp->mem_code->propogate(dp->mem_code);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_restart(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;
    
    /* Write zero at each register */
    if (dp->regA == NULL || dp->regB == NULL || dp->sp == NULL || dp->pc == NULL)
        return ERR_INV_PTR;
    
    Port* regA_wen;
    EmErr err = dp->regA->get_port(dp->regA, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &regA_wen);
    if (err != SUCCESS)
        return err;
    
    Port* regB_wen;
    err = dp->regB->get_port(dp->regB, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &regB_wen);
    if (err != SUCCESS)
        return err;
    
    Port* sp_wen;
    err = dp->sp->get_port(dp->sp, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &sp_wen);
    if (err != SUCCESS)
        return err;
    
    Port* pc_wen;
    err = dp->pc->get_port(dp->pc, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &pc_wen);
    if (err != SUCCESS)
        return err;

    Port* regA_din;
    err = dp->regA->get_port(dp->regA, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &regA_din);
    if (err != SUCCESS)
        return err;
    
    Port* regB_din;
    err = dp->regB->get_port(dp->regB, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &regB_din);
    if (err != SUCCESS)
        return err;
    
    Port* sp_din;
    err = dp->sp->get_port(dp->sp, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &sp_din);
    if (err != SUCCESS)
        return err;
    
    Port* pc_din;
    err = dp->pc->get_port(dp->pc, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &pc_din);
    if (err != SUCCESS)
        return err;
    
    regA_din->state = 0;
    regB_din->state = 0;
    sp_din->state = 0;
    pc_din->state = 0;
    
    regA_wen->state = ENABLE;
    regB_wen->state = ENABLE;
    sp_wen->state = ENABLE;
    pc_wen->state = ENABLE;

    err = dp->regA->transition(dp->regA);
    if (err != SUCCESS)
        return err;
    
    err = dp->regB->transition(dp->regB);
    if (err != SUCCESS)
        return err;

    err = dp->sp->transition(dp->sp);
    if (err != SUCCESS)
        return err;
    
    err = dp->pc->transition(dp->pc);
    if (err != SUCCESS)
        return err;

    regA_wen->state = ENABLE;
    regB_wen->state = ENABLE;
    sp_wen->state = ENABLE;
    pc_wen->state = ENABLE;
    
    /* Reset the Memory */
    if (dp->mem_data == NULL)
        return ERR_INV_PTR;
    
    Port* mem_rst;
    err = dp->mem_data->get_port(dp->mem_data, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, &mem_rst);
    if (err != SUCCESS)
        return err;
    
    mem_rst->state = ENABLE;

    err = dp->mem_data->transition(dp->mem_data);
    if (err != SUCCESS)
        return err;
    
    mem_rst->state = DISABLE;

    return SUCCESS;
}

static _dp_reset(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;

    EmErr err = _dp_restart(dp);
    if (err != SUCCESS)
        return err;
    
    /* Reset the code memory */
    if (dp->mem_code == NULL)
        return ERR_INV_PTR;

    Port* mem_rst;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, &mem_rst);
    if (err != SUCCESS)
        return err;
    
    mem_rst->state = ENABLE;

    err = dp->mem_code->transition(dp->mem_code);
    if (err != SUCCESS)
        return err;
    
    mem_rst->state = DISABLE;

    return SUCCESS;
}

static EmErr _dp_clock(DP* dp) {
    if (dp == NULL)
        return ERR_INV_PTR;

    if (dp->regA == NULL || dp->regB == NULL || dp->sp == NULL || dp->pc == NULL)
        return ERR_INV_PTR;
    
    if (dp->mem_code == NULL || dp->mem_data == NULL)
        return ERR_INV_PTR;

    
    /* Gather all the SEQ Elems */
    EmErr err = dp->regA->transition(dp->regA);
    if (err != SUCCESS)
        return err;
    
    err = dp->regB->transition(dp->regB);
    if (err != SUCCESS)
        return err;
    
    err = dp->sp->transition(dp->sp);
    if (err != SUCCESS)
        return err;
    
    err = dp->pc->transition(dp->pc);
    if (err != SUCCESS)
        return err;

    
    /* Propogate the signals now */
    err = dp->regA->propogate(dp->regA);
    if (err != SUCCESS)
        return err;
    
    err = dp->regB->propogate(dp->regB);
    if (err != SUCCESS)
        return err;
    
    err = dp->sp->propogate(dp->sp);
    if (err != SUCCESS)
        return err;
    
    err = dp->pc->propogate(dp->pc);
    if (err != SUCCESS)
        return err;

    err = dp->mem_data->transition(dp->mem_data);
    if (err != SUCCESS)
        return err;
    
    err = dp->mem_code->propogate(dp->mem_code);
    if (err != SUCCESS)
        return err;

    return SUCCESS;
}

static EmErr _dp_inspect(DP* dp, EmName name, EmType type, EmId id, EmState* ptr) {

    if (dp == NULL || ptr == NULL)
        return ERR_INV_PTR;

    if (name == NAME_DP_REG_A) {
        if (dp->regA == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->regA->get_port(dp->regA, type, id, &vport);
        if (err != SUCCESS)
            return err;
        
        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_REG_B) {
        if (dp->regB == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->regB->get_port(dp->regB, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_PC) {
        if (dp->pc == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->pc->get_port(dp->pc, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_SP) {
        if (dp->sp == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->sp->get_port(dp->sp, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_ALU) {
        if (dp->alu == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->alu->get_port(dp->alu, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MEM_CODE) {
        if (dp->mem_code == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mem_code->get_port(dp->mem_code, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MEM_DATA) {
        if (dp->mem_data == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mem_data->get_port(dp->mem_data, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_A_IN) {
        if (dp->mux_a_in == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_a_in->get_port(dp->mux_a_in, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_MEM_IN) {
        if (dp->mux_mem_in == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_mem_in->get_port(dp->mux_mem_in, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_PC_IN) {
        if (dp->mux_pc_in == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_pc_in->get_port(dp->mux_pc_in, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_BR) {
        if (dp->mux_br == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_br->get_port(dp->mux_br, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_BR_FINE) {
        if (dp->mux_br_fine == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_br_fine->get_port(dp->mux_br_fine, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_BZ_PC) {
        if (dp->mux_bz_pc == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_bz_pc->get_port(dp->mux_bz_pc, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_BNEG_PC) {
        if (dp->mux_bneg_pc == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_bneg_pc->get_port(dp->mux_bneg_pc, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_ALU_A) {
        if (dp->mux_alu_a == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_alu_a->get_port(dp->mux_alu_a, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_MUX_ALU_B) {
        if (dp->mux_alu_b == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->mux_alu_b->get_port(dp->mux_alu_b, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    } else if (name == NAME_DP_PC_ADDER) {
        if (dp->pc_adder == NULL)
            return ERR_INV_PTR;
        
        Port* vport;
        EmErr err = dp->pc_adder->get_port(dp->pc_adder, type, id, &vport);
        if (err != SUCCESS)
            return err;

        *ptr = vport->state;
        return SUCCESS;
    }

    return ERR_INV_CNAME;
}

EmErr dp_get_datapath(DP** ptr) {

    if (ptr == NULL)
        return ERR_INV_PTR;

    DP* dp = (DP*)malloc(sizeof(DP));
    if (dp == NULL)
        return ERR_MEM_ALLOC;

    dp->cu = NULL;
    dp->regA = NULL;
    dp->regB = NULL;
    dp->alu = NULL;
    dp->mem_code = NULL;
    dp->mem_data = NULL;
    dp->pc = NULL;
    dp->sp = NULL;
    dp->mux_a_in = NULL;
    dp->mux_mem_in = NULL;
    dp->mux_pc_in = NULL;
    dp->mux_br = NULL;
    dp->mux_br_fine = NULL;
    dp->mux_bz_pc = NULL;
    dp->mux_bneg_pc = NULL;
    dp->mux_alu_a = NULL;
    dp->mux_alu_b = NULL;
    dp->pc_adder = NULL;

    dp->load = _dp_load;
    dp->reset = _dp_reset;
    dp->restart = _dp_restart;
    dp->clock = _dp_clock;
    dp->inspect = _dp_inspect;

    EmErr err = _dp_create_elements(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_connect_element(dp);
    if (err != SUCCESS)
        return err;

    err = _dp_load_constants(dp);
    if (err != SUCCESS)
        return err;

    *ptr = dp;
    return SUCCESS;
}

void dp_print_cu(DP* dp) {

    printf("\nControl Unit\n------------------------\n");

    if (dp == NULL)
        return;

    if (dp->cu == NULL)
        return;

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
    

    printf("Instruction: %d\n", instr_val);
    printf("MUX_BR: %d\n", mux_br->state);
    printf("MUX_BR_FINE: %d\n", mux_br_fine->state);
    printf("W_EN_SP: %d\n", w_en_sp->state);
    printf("W_EN_B: %d\n", w_en_b->state);
    printf("W_EN_A: %d\n", w_en_a->state);
    printf("MUX_PC_IN: %d\n", mux_pc_in->state);
    printf("W_EN_PC: %d\n", w_en_pc->state);
    printf("MUX_ALU_A: %d\n", mux_alu_a->state);
    printf("MUX_ALU_B: %d\n", mux_alu_b->state);
    printf("MUX_A_IN: %d\n", mux_a_in->state);
    printf("MUX_MEM_IN: %d\n", mux_mem_in->state);
    printf("W_EN_MEM: %d\n", w_en_mem->state);
    printf("ALU_SEL: %d\n", alu_sel->state);
    printf("IMM: %d\n", imm->state);
}


void dp_print_program_counter(DP* dp) {

    printf("\nProgram Counter\n------------------------\n");

    if (dp == NULL)
        return;

    if (dp->pc == NULL)
        return;

    Port* pc_in;
    EmErr err = dp->pc->get_port(dp->pc, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &pc_in);
    if (err != SUCCESS)
        return err;
    
    Port* pc_out;
    err = dp->pc->get_port(dp->pc, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &pc_out);
    if (err != SUCCESS)
        return err;
    
    Port* w_en;
    err = dp->pc->get_port(dp->pc, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &w_en);
    if (err != SUCCESS)
        return err;
    
    printf("Program Counter Input: %d\n", pc_in->state);
    printf("Program Counter Output: %d\n", pc_out->state);
    printf("Program Counter Write Enable: %d\n", w_en->state);
}

void dp_print_register_a(DP* dp) {

    printf("\nRegister A\n------------------------\n");

    if (dp == NULL)
        return;

    if (dp->regA == NULL)
        return;

    Port* reg_in;
    EmErr err = dp->regA->get_port(dp->regA, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &reg_in);
    if (err != SUCCESS)
        return err;
    
    Port* reg_out;
    err = dp->regA->get_port(dp->regA, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &reg_out);
    if (err != SUCCESS)
        return err;
    
    Port* w_en;
    err = dp->regA->get_port(dp->regA, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &w_en);
    if (err != SUCCESS)
        return err;
    
    printf("Register A Input: %d\n", reg_in->state);
    printf("Register A Output: %d\n", reg_out->state);
    printf("Register A Write Enable: %d\n", w_en->state);
}

void dp_print_register_b(DP* dp) {

    printf("\nRegister B\n------------------------\n");

    if (dp == NULL)
        return;

    if (dp->regB == NULL)
        return;

    Port* reg_in;
    EmErr err = dp->regB->get_port(dp->regB, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &reg_in);
    if (err != SUCCESS)
        return err;
    
    Port* reg_out;
    err = dp->regB->get_port(dp->regB, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &reg_out);
    if (err != SUCCESS)
        return err;
    
    Port* w_en;
    err = dp->regB->get_port(dp->regB, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &w_en);
    if (err != SUCCESS)
        return err;
    
    printf("Register B Input: %d\n", reg_in->state);
    printf("Register B Output: %d\n", reg_out->state);
    printf("Register B Write Enable: %d\n", w_en->state);
}

void dp_print_stack_pointer(DP* dp) {

    printf("\nStack Pointer\n------------------------\n");

    if (dp == NULL)
        return;

    if (dp->sp == NULL)
        return;

    Port* sp_in;
    EmErr err = dp->sp->get_port(dp->sp, TYPE_PORT_INPUT, ID_PORT_REG_DIN, &sp_in);
    if (err != SUCCESS)
        return err;
    
    Port* sp_out;
    err = dp->sp->get_port(dp->sp, TYPE_PORT_OUTPUT, ID_PORT_REG_DOUT, &sp_out);
    if (err != SUCCESS)
        return err;
    
    Port* w_en;
    err = dp->sp->get_port(dp->sp, TYPE_PORT_INPUT, ID_PORT_REG_WEN, &w_en);
    if (err != SUCCESS)
        return err;
    
    printf("Stack Pointer Input: %d\n", sp_in->state);
    printf("Stack Pointer Output: %d\n", sp_out->state);
    printf("Stack Pointer Write Enable: %d\n", w_en->state);
}

void dp_print_mem_comp(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->mem_code == NULL)
        return ERR_INV_PTR;
    
    Port* mem_rst;
    EmErr err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RESET, &mem_rst);
    if (err != SUCCESS)
        return err;
    
    Port* mem_wen;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_WEN, &mem_wen);
    if (err != SUCCESS)
        return err;
    
    Port* mem_addr;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_WADDR, &mem_addr);
    if (err != SUCCESS)
        return err;
    
    Port* mem_dat;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_DIN, &mem_dat);
    if (err != SUCCESS)
        return err;
    
    Port* mem_raddr_a;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_A, &mem_raddr_a);
    if (err != SUCCESS)
        return err;
    
    Port* mem_raddr_b;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_INPUT, ID_PORT_MEM_RADDR_B, &mem_raddr_b);
    if (err != SUCCESS)
        return err;

    Port* mem_dout_a;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_A, &mem_dout_a);
    if (err != SUCCESS)
        return err;

    Port* mem_dout_b;
    err = dp->mem_code->get_port(dp->mem_code, TYPE_PORT_OUTPUT, ID_PORT_MEM_DOUT_B, &mem_dout_b);
    if (err != SUCCESS)
        return err;
    
    printf("\nCode Memory\n------------------------\n");
    printf("Memory Reset: %d\n", mem_rst->state);
    printf("Memory Write Enable: %d\n", mem_wen->state);
    printf("Memory Write Address: %d\n", mem_addr->state);
    printf("Memory Write Data: %d\n", mem_dat->state);
    printf("Memory Read Address A: %d\n", mem_raddr_a->state);
    printf("Memory Read Address B: %d\n", mem_raddr_b->state);
    printf("Memory Read Data A: %d\n", mem_dout_a->state);
    printf("Memory Read Data B: %d\n", mem_dout_b->state);
}

void dp_print_adder(DP* dp) {

    if (dp == NULL)
        return ERR_INV_PTR;
    
    if (dp->pc_adder == NULL)
        return ERR_INV_PTR;
    
    Port* adder_in_a;
    EmErr err = dp->pc_adder->get_port(dp->pc_adder, TYPE_PORT_INPUT, ID_PORT_ADDER_INA, &adder_in_a);
    if (err != SUCCESS)
        return err;
    
    Port* adder_in_b;
    err = dp->pc_adder->get_port(dp->pc_adder, TYPE_PORT_INPUT, ID_PORT_ADDER_INB, &adder_in_b);
    if (err != SUCCESS)
        return err;
    
    Port* adder_out;
    err = dp->pc_adder->get_port(dp->pc_adder, TYPE_PORT_OUTPUT, ID_PORT_ADDER_OUT, &adder_out);
    if (err != SUCCESS)
        return err;
    
    printf("\nProgram Counter Adder\n------------------------\n");
    printf("Adder Input A: %d\n", adder_in_a->state);
    printf("Adder Input B: %d\n", adder_in_b->state);
    printf("Adder Output: %d\n", adder_out->state);
}