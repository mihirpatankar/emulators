#ifndef _DISASSEMBLER_H
#define _DISASSEMBLER_H

#include "common.h"

#define OPCODE_MIN 0x00
#define OPCODE_MAX 0xFF

uint8_t get_opcode_bytes(uint8_t opcode);
uint8_t emulate_instruction(uint8_t opcode);
void unimplemented_instruction(uint8_t opcode);

#endif //DISASSEMBLER_H
