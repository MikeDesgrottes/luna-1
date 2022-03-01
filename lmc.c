
//
// vec.c
//
// Copyright (c) 2013 TJ Holowaychuk <tj@vision-media.ca>
//

#include "math.h"
#include "lmc.h"
#include "vec.h"

/*
 * Alloc and initialize a new array.
 */

lmc_t*
lmc_init(int max){
	lmc_t* computer = malloc(sizeof(lmc_t));
	computer->ram = luna_vec_new();
	computer->acc = 0;
	return computer;	
}

lmc_op_t
opcode(lmc_instruction_t* instr){
	return (instr >> 12);
}
void
execute(lmc_t* self, lmc_instruction_t* instr){

	switch(opcode(instr)){
		case ADD:
			add(self,instr);
			break;	
		case LMC_OP_SUB:
			self->acc -= fetch_data(self->ram,instr->addr);
			break;
		case LMC_OP_STA:
			store_data(self->ram,instr->addr,self->acc);
			break;
		case LMC_OP_LDA:
			self->acc = fetch_data(self->ram,instr->addr);
			break;
		case LMC_OP_BRA:
			self->ip = fetch_data(self->ram,instr->addr);
			break;
		case LMC_OP_BRZ:
			break;
		case LMC_OP_BRP:
			break;
		case LMC_OP_INP:
			break;
		case LMC_OP_OUT:
			break;
		case LMC_OP_HALT:
			break;//
		case LMC_OP_DAT:
			break;
		default: break;
	}
}

uint32_t sign_extend(uint32_t bit, int count){
	if((bit >> (count - 1)) & 1){
		bit |= (0xFFFF >> count);
	}
	return bit;
}

void update_flags(lmc_t *self, uint32_t r){
	if(self->resgisters[r] == 0){
		self->registers[9] = FL_ZERO;
	}else if(self->registers[r] >> 15){
		self-registers[9] = FL_NEG
	}else{
		self->registers[9] = FL_POS;
	}

}
void add(lmc_t* self, lmc_instruction_t* instr) {
	uint32_t src1 = (instr >> 6) & 0x7;
	uint32_t dst = (instr >> 9) & 0x7;
	uint32_t flag = (instr >> 5) & 0x1;
	uint32_t src2 = (instr) & 0x7;
	if(flag){
		uint32_t src3 = sign_extend(src2, 5);
		self->registers[dst] = self->registers[src1] + src3;
	}else{
		self->registers[dst] = self->registers[src1] + self->registers[src2];
	}

	update_flags(self,src1);
}

void ldi(lmc_t* self, lmc_insstruction_t instr){
	uint16_t r0 = (instr >> 9)& 0x7;
	uint16_t pc_offset = sign_extend(instr & 0x1FF, 9);

	self->registers[r0] = self->registers[self->registers[self->ip + pc_offset]];
       update_flags(r0);	
}
