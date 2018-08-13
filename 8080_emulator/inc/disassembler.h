#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H

#include "common.h"

uint8_t disassemble_opcode(uint8_t* code_buffer, uint16_t pc);
uint8_t emulate_instruction(uint8_t opcode);
void unimplemented_instruction(uint8_t opcode);

void increment(uint8_t reg);
void decrement(uint8_t reg);

void dummy_execute();
#endif //DISASSEMBLER_H
