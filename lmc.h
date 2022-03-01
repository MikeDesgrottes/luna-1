
//
// opcodes.h
//
// Copyright (c) 2013 TJ Holowaychuk <tj@vision-media.ca>
//

#ifndef LUNA_LMC_H
#define LUNA_LMC_H

#include <stdint.h>
#include "kvec.h"
#include "object.h"
#include "vec.h"
/*
 * Opcodes.
 */

#define MEM 100
#define uint16_t lmc_instruction_t

#define valid(t) (ndigit(cmp->size) + 1 == ndigit(t))
#define LMC_OP_LIST \
  o(ADD, "add") \
  o(AND, "and") \
  o(BR, "br") \
  o(JMP, "jmp") \
  o(JSR, "jsr") \
  o(JSRR, "jsrr") \
  o(LD, "ld") \
  o(LDI, "ldi") \
  o(LDR, "ldr") \
  o(LEA, "lea") \
  o(NOT, "not") \
  o(RET, "ret") \
  o(RTI, "rti") \
  o(ST, "st") \
  o(STR , "str") \
  o(TRAP, "trap") \
  o(RESERVED, "reserved") 



#define en(op,a,b,i,c) \
	(op << 12 \
	 |(a) << 9 \
	 | (b) << 6 \
	 | (i) << 5 \
	 | (c) )


#define OP(i) ((i) >> 12 & 0xFFFF)
#define A(i) ((i) >> 9 & 0x7)
#define B(i) ((i) >> 6 & 0x7)
#define C(i) ((i) & 0xff)
#define flag(i) ((i) & 0x1)
/*
 * Opcodes enum.
 */

typedef enum {
#define o(op, str) op,
LMC_OP_LIST
#undef o
} lmc_op_t;

/*
 * Opcode strings.
 */

static char *lmc_op_strings[] = {
#define o(op, str) str,
LMC_OP_LIST
#undef o
};
typedef enum{
	FL_ZRO,
	FL_NEG,
	FL_POS
} flag;
typedef struct{
	flag fl = FL_ZERO;
	int size;
	int acc;
	int ip = 0;
//	luna_vec_t* mem;
	lmc_instruction_t mem[65536];
	lmc_instruction registers[10] = {0};
} lmc_t;

lmc_t*
lmc_init(int max);

void
decode(luna_op_t opcode,int a, int b, int c, int flag);

int
ndigit(int num);

int
is_instruction(luna_vec_t* vec,int count);

int
fetch_data(luna_vec_t* vec, int count);

void
store_data(luna_vec_t* vec, int count, int data);

void
execute(lmc_t* self, lmc_instruction_t* instr);

void add(lmc_t *self, lmc_instruction_t* instr);
#endif /* LUNA_LMC_H */
