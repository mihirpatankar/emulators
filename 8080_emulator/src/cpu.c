#include "cpu.h"

void set_status_register_flag(struct cpu_state* state, uint8_t mask){
  state->registers.status_register |= mask;
}

void clear_status_register_flag(struct cpu_state* state, uint8_t mask){
  state->registers.status_register &= ~(mask);
}

uint16_t append_registers(uint8_t register_high, uint8_t register_low){
  uint16_t appended_register = (register_high<<8) | register_low;
  return appended_register;
}
