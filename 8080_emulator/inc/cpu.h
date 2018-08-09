#include "common.h"
#include "memory.h"

#define STATUS_REGISTER_MASK_SIGN 0x80
#define STATUS_REGISTER_MASK_ZERO 0x40
#define STATUS_REGISTER_MASK_PARITY 0x04
#define STATUS_REGISTER_MASK_CARRY 0x01
#define STATUS_REGISTER_MASK_AUXILIARY_CARRY 0x10

#define BIT_0_MASK 0x01
#define BIT_1_MASK 0x02
#define BIT_2_MASK 0x04
#define BIT_3_MASK 0x08
#define BIT_4_MASK 0x10
#define BIT_5_MASK 0x20
#define BIT_6_MASK 0x40
#define BIT_7_MASK 0x80

#define HIGH_BYTE_MASK 0xFF00
#define LOW_BYTE_MASK 0x00FF
#define BYTE 8

typedef struct cpu_registers{
 uint8_t A;
 uint8_t status_register;
 uint8_t B;
 uint8_t C;
 uint8_t D;
 uint8_t E;
 uint8_t H;
 uint8_t L;
 uint16_t SP;
 uint16_t PC;
}cpu_registers;

typedef struct cpu_state{
  struct cpu_registers registers;
  uint8_t* memory;
}cpu_state;

void set_bit(uint8_t* data, uint8_t mask);
void clear_bit(uint8_t* data, uint8_t mask);
uint16_t append_registers(uint8_t register_high, uint8_t register_low);
void assign_data_to_registers(uint8_t* register_high, uint8_t* register_low, uint16_t data);
uint8_t get_high_byte(uint16_t data);
uint8_t get_low_byte(uint16_t data);
void update_zero_flag(struct cpu_state* state, uint8_t data);
void update_parity_flag(struct cpu_state* state, uint8_t data);
void update_sign_flag(struct cpu_state* state, uint8_t data);
void update_carry_flag(struct cpu_state* state, uint16_t data);
void update_auxiliary_carry_flag(struct cpu_state* state, uint8_t data);
