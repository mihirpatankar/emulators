#include "common.h"
#include "memory.h"

#define BIT_0_MASK 0x01
#define BIT_1_MASK 0x02
#define BIT_2_MASK 0x04
#define BIT_3_MASK 0x08
#define BIT_4_MASK 0x10
#define BIT_5_MASK 0x20
#define BIT_6_MASK 0x40
#define BIT_7_MASK 0x80

#define MASK_CY 0x01
#define MASK_UN1 0x02
#define MASK_P 0x04
#define MASK_UN3 0x08
#define MASK_AC 0x10
#define MASK_UN5 0x20
#define MASK_Z 0x40
#define MASK_S 0x80

#define HIGH_BYTE_MASK 0xFF00
#define LOW_BYTE_MASK 0x00FF

#define BYTE 8
#define WORD 16

typedef union register_pair{
  struct {
    uint8_t low, high;
  } byte;
  uint16_t word;
}register_pair;

typedef struct flag_register{
  uint8_t carry;
  uint8_t un1;
  uint8_t parity;
  uint8_t un3;
  uint8_t auxiliary_carry;
  uint8_t un5;
  uint8_t zero;
  uint8_t sign;
}flag_register;

typedef struct cpu_state{
  flag_register flag;
  register_pair AF, BC, DE, HL;
  register_pair SP, PC, PC_LAST;
}cpu_state;

#define A state->AF.byte.high
#define F state->AF.byte.low
#define B state->BC.byte.high
#define C state->BC.byte.low
#define D state->DE.byte.high
#define E state->DE.byte.low
#define H state->HL.byte.high
#define L state->HL.byte.low

#define AF state->AF.word
#define BC state->BC.word
#define DE state->DE.word
#define HL state->HL.word

#define CY state->flag.carry
#define P state->flag.parity
#define AC state->flag.auxiliary_carry
#define Z state->flag.zero
#define S state->flag.sign
#define UN1 state->flag.un1
#define UN3 state->flag.un3
#define UN5 state->flag.un5

#define SP state->SP.word
#define PC state->PC.word
#define PC_LAST state->PC_LAST.word

#define SP_HIGH state->SP.byte.high
#define SP_LOW state->SP.byte.low
#define PC_HIGH state->PC.byte.high
#define PC_LOW state->PC.byte.low

#define SET(flag) (flag=1)
#define CLR(flag) (flag=0)
#define TGL(flag) (flag=!flag);

cpu_state* state;

void cpu_init();

void init_regs(cpu_state* state);
void init_flags(cpu_state* state);
void store_flags(cpu_state* state);
void get_flags(cpu_state* state);
