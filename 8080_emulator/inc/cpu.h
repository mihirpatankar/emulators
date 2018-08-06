#include "common.h"

#define STATUS_REGISTER_MASK_SIGN 0x80
#define STATUS_REGISTER_MASK_ZERO 0x40
#define STATUS_REGISTER_MASK_PARITY 0x04
#define STATUS_REGISTER_MASK_CARRY 0x01
#define STATUS_REGISTER_MASK_AUXILIARY_CARRY 0x10

typedef struct cpu_registers{
 uint8_t A;
 uint8_t status_register;
 uint8_t B;
 uint8_t C;
 uint8_t D;
 uint8_t H;
 uint8_t L;
 uint16_t SP;
 uint16_t PC;
}cpu_registers;
