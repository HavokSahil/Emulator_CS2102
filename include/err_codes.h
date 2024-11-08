#ifndef _ERR_CODES_H
#define _ERR_CODES_H

#define SUCCESS	0x00
#define FAILURE		0xFF

#define ERR_MEM_ALLOC   0x01
#define ERR_INV_PTR		0x02
#define ERR_QOS_MIS		0x03
#define ERR_UPD_SLV		0x04	/* Slave update failed */
#define ERR_PRT_LME		0x05	/* Port Limit Exceeded */
#define ERR_USP_PTY		0x06	/* Unsupported Port Type */
#define ERR_MUL_MST		0x07	/* Case of Multiple Master of Bus  */
#define ERR_MUX_OVF		0x08	/* Mux Control Bit Limit Exceeded  */
#define ERR_MEM_IOB		0x09	/* Memory Index out of bound  */
#define ERR_MEM_IVS		0x0A	/* Invalid Signal for Memory Agent  */
#define ERR_ALU_OVF		0x0B	/* ALU result overflow */
#define ERR_INV_INSTR   0x0C    /* Invalid Instruction */
#define ERR_INV_CNAME   0x0D    /* Invalid Circuit Element Name */
#define ERR_INV_FILE    0x0E    /* Invalid File Format */

#endif
