#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H

#include "common.h"

#define OPCODE_MIN 0x00
#define OPCODE_MAX 0xFF

uint8_t data8;
uint16_t data16;
uint32_t data32;

void print_instruction(uint8_t* code_buffer, uint16_t pc);
uint8_t get_opcode_bytes(uint8_t opcode);
uint8_t emulate_instruction(uint8_t opcode);
void unimplemented_instruction(uint8_t opcode);

void increment(uint8_t reg);
void decrement(uint8_t reg);

void add(uint8_t reg);
void add_with_carry(uint8_t reg);
void subtract(uint8_t reg);
void subtract_with_borrow(uint8_t reg);
void compare(uint8_t reg);

void logical_and(uint8_t reg);
void logical_or(uint8_t reg);
void logical_xor(uint8_t reg);

void push(uint16_t reg);
void pop(uint16_t reg);
void call();

void dummy_execute();
#endif //DISASSEMBLER_H
