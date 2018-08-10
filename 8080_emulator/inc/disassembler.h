#include "common.h"
#include "cpu.h"

uint8_t disassemble_opcode(uint8_t* code_buffer, uint16_t pc);
uint8_t emulate_instruction(uint8_t opcode);
void unimplemented_instruction(uint8_t opcode);
