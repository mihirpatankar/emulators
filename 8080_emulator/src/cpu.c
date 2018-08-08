#include "cpu.h"

void set_status_register_flag(struct cpu_state* state, uint8_t mask){
  state->registers.status_register |= mask;
}

void clear_status_register_flag(struct cpu_state* state, uint8_t mask){
  state->registers.status_register &= ~(mask);
}
