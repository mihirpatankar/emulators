#include "common.h"
#include "cpu.h"

uint8_t disassemble_opcode(uint8_t* code_buffer, uint16_t pc);
void emulate_instruction(struct cpu_state* state);
void unimplemented_instruction(struct cpu_state* state);
