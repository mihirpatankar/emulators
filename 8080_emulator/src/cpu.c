#include "cpu.h"

void set_bit(uint8_t* data, uint8_t mask){
  *data |= mask;
}

void clear_bit(uint8_t* data, uint8_t mask){
  *data &= ~(mask);
}

uint16_t append_registers(uint8_t register_high, uint8_t register_low){
  uint16_t appended_register = (register_high<<8) | register_low;
  return appended_register;
}

void assign_data_to_registers(uint8_t* register_high, uint8_t* register_low, uint16_t data){
  *register_low = get_low_byte(data);
  *register_high = get_high_byte(data);
}

uint8_t get_high_byte(uint16_t data){
  return (uint8_t)((data & HIGH_BYTE_MASK)>>BYTE);
}

uint8_t get_low_byte(uint16_t data){
  return (uint8_t)(data & LOW_BYTE_MASK);
}

void update_zero_flag(struct cpu_state* state, uint8_t data){
  if(data == 0){
    set_bit(&state->registers.status_register, STATUS_REGISTER_MASK_ZERO);
  }
  else{
    clear_bit(&state->registers.status_register, STATUS_REGISTER_MASK_ZERO);
  }
}

void update_parity_flag(struct cpu_state* state, uint8_t data){

}

void update_sign_flag(struct cpu_state* state, uint8_t data){
  if(BIT_7_MASK == (data & BIT_7_MASK)){
    set_bit(&state->registers.status_register, STATUS_REGISTER_MASK_SIGN);
  }
  else{
    clear_bit(&state->registers.status_register, STATUS_REGISTER_MASK_SIGN);
  }
}

void update_carry_flag(struct cpu_state* state, uint16_t data){

}

void update_auxiliary_carry_flag(struct cpu_state* state, uint8_t data){

}
