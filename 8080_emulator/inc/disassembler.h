#include "common.h"
#include "cpu.h"

uint8_t disassemble_opcode(uint8_t* code_buffer, uint16_t pc);
void emulate_instruction(struct cpu_state* state);
void unimplemented_instruction(struct cpu_state* state);
uint8_t get_data_pointed_by(struct cpu_state* state, uint8_t register_high, uint8_t register_low);
void set_data_pointed_by(struct cpu_state* state, uint8_t register_high, uint8_t register_low, uint8_t data);

