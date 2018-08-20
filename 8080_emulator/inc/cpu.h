#ifndef _CPU_H
#define _CPU_H

#include "common.h"
#include "memory.h"

#define MASK_CY 0x01
#define MASK_UN1 0x02
#define MASK_P 0x04
#define MASK_UN3 0x08
#define MASK_AC 0x10
#define MASK_UN5 0x20
#define MASK_Z 0x40
#define MASK_S 0x80

uint8_t data8;
uint16_t data16;
uint32_t data32;

#define CARRY_CHECK_MASK 0x0100

extern uint8_t parity_table[];
extern uint8_t aux_carry_add[];
extern uint8_t aux_carry_sub[];

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
  register_pair af, bc, de, hl;
  register_pair sp, pc, pc_last;
  uint16_t iff;
}cpu_state;

#define A state.af.byte.high
#define F state.af.byte.low
#define B state.bc.byte.high
#define C state.bc.byte.low
#define D state.de.byte.high
#define E state.de.byte.low
#define H state.hl.byte.high
#define L state.hl.byte.low

#define AF state.af.word
#define BC state.bc.word
#define DE state.de.word
#define HL state.hl.word

#define CY state.flag.carry
#define P state.flag.parity
#define AC state.flag.auxiliary_carry
#define Z state.flag.zero
#define S state.flag.sign
#define UN1 state.flag.un1
#define UN3 state.flag.un3
#define UN5 state.flag.un5

#define SP_HIGH state.sp.byte.high
#define SP_LOW state.sp.byte.low
#define PC_HIGH state.pc.byte.high
#define PC_LOW state.pc_last.byte.low
#define PC_LAST state.pc_last.word
#define SP state.sp.word
#define PC state.pc.word

#define IFF state.iff

#define SET(flag) (flag=1)
#define CLR(flag) (flag=0)
#define TGL(flag) (flag=!flag)

cpu_state state;

void cpu_init();
void init_regs();
void init_flags();
void store_flags();
void get_flags();
void handle_iff(uint16_t iff);
void handle_output(uint8_t port, uint8_t data);
uint8_t handle_input(uint8_t port);

uint8_t update_sign_flag(uint8_t reg);
uint8_t update_parity_flag(uint8_t reg);
uint8_t update_zero_flag(uint8_t reg);
uint8_t update_carry_flag(uint16_t reg);

void increment(uint8_t* reg);
void decrement(uint8_t* reg);

void add(uint8_t reg);
void add_with_carry(uint8_t reg);
void double_byte_add(uint16_t reg);
void subtract(uint8_t reg);
void subtract_with_borrow(uint8_t reg);
void compare(uint8_t reg);

void logical_and(uint8_t reg);
void logical_or(uint8_t reg);
void logical_xor(uint8_t reg);

void push(uint16_t reg);
void pop(uint16_t* reg);
void call();
void reset(uint16_t addr);

#endif //_CPU_H
