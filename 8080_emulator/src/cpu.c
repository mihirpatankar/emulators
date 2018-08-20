#include "cpu.h"

uint8_t parity_table[] = {
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0,
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1,
};

uint8_t aux_carry_add[] = {0, 0, 1, 0, 1, 0, 1, 1};

uint8_t aux_carry_sub[] = {0, 1, 1, 1, 0, 0, 0, 1};


void cpu_init(){
  init_regs(state);
  init_flags(state);
}

void init_regs(){
  PC=0xF800;
}

void init_flags(){
  CY = 0;
  S = 0;
  Z = 0;
  AC = 0;
  P = 0;
  UN1 = 1;
  UN3 = 0;
  UN5 = 0;
}

void store_flags(){
  if (S) F |= MASK_S;  else F &= ~MASK_S;
  if (Z) F |= MASK_Z;  else F &= ~MASK_Z;
  if (AC) F |= MASK_AC; else F &= ~MASK_AC;
  if (P) F |= MASK_P;  else F &= ~MASK_P;
  if (CY) F |= MASK_CY; else F &= ~MASK_CY;
  F |= MASK_UN1;    // UN1_FLAG is always 1.
  F &= ~MASK_UN3;   // UN3_FLAG is always 0.
  F &= ~MASK_UN5; // UN5_FLAG is always 0.
}

void get_flags(){
  S = F & MASK_S ? 1 : 0;
  Z = F & MASK_Z ? 1 : 0;
  AC = F & MASK_AC ? 1 : 0;
  P = F & MASK_P ? 1 : 0;
  CY = F & MASK_CY ? 1 : 0;
}

void handle_iff(uint16_t iff){
  //Do nothing
}

void handle_output(uint8_t port, uint8_t data){
  //Do nothing
}

uint8_t handle_input(uint8_t port){
  return 0;
}

uint8_t update_sign_flag(uint8_t reg){
  return ((reg & BIT_7_MASK) != 0);
}

uint8_t update_parity_flag(uint8_t reg){
  return parity_table[reg];
}

uint8_t update_zero_flag(uint8_t reg){
  return (reg==0);
}

uint8_t update_carry_flag(uint16_t reg){
  return ((reg & CARRY_CHECK_MASK) != 0);
}

void increment(uint8_t* reg){
  ++(*reg);
  S = update_sign_flag(*reg);
  Z = update_zero_flag(*reg);
  AC = ((*reg) & LOW_NIBBLE_MASK) == 0;
  P = update_parity_flag(*reg);
}

void decrement(uint8_t* reg){
  --(*reg);
  S = update_sign_flag(*reg);
  Z = update_zero_flag(*reg);
  AC= ((*reg) & LOW_NIBBLE_MASK) != 0xF;
  P = update_parity_flag(*reg);
}

void add(uint8_t reg){
  data16 = (uint16_t)A + reg;
  A = data16 & LOW_BYTE_MASK;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  data8 = ((A & BIT_3_MASK) >> 1)
    | ((reg & BIT_3_MASK) >> 2)
    | ((data16 & BIT_3_MASK) >> 3);
  AC = aux_carry_add[data8];
  P = update_parity_flag(A);
  CY = update_carry_flag(data16);
}

void add_with_carry(uint8_t reg){
  data16 = (uint16_t)A + reg + CY;
  A = data16 & LOW_BYTE_MASK;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  data8 = ((A & BIT_3_MASK) >> 1)
    | ((reg & BIT_3_MASK) >> 2)
    | ((data16 & BIT_3_MASK) >> 3);
  AC = aux_carry_add[data8];
  P = update_parity_flag(A);
  CY = update_carry_flag(data16);
}

void double_byte_add(uint16_t reg){
  data32 = (uint32_t)HL + reg;
  HL = data32 & 0xFFFF;
  CY = (data32 & 0x10000L) !=0;
}

#define DAD(reg) \
{                                               \
    work32 = (uns32)HL + (reg);                 \
    HL = work32 & 0xffff;                       \
    C_FLAG = ((work32 & 0x10000L) != 0);        \
}

void subtract(uint8_t reg){
  data16 = (uint16_t)A - reg;
  A = data16 & LOW_BYTE_MASK;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  data8 = ((A & BIT_3_MASK) >> 1)
    | ((reg & BIT_3_MASK) >> 2)
    | ((data16 & BIT_3_MASK) >> 3);
  AC = !aux_carry_sub[data8];
  P = update_parity_flag(A);
  CY = update_carry_flag(data16);
}

void subtract_with_borrow(uint8_t reg){
  data16 = (uint16_t)A - reg - CY;
  A = data16 & LOW_BYTE_MASK;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  data8 = ((A & BIT_3_MASK) >> 1)
    | ((reg & BIT_3_MASK) >> 2)
    | ((data16 & BIT_3_MASK) >> 3);
  AC = !aux_carry_sub[data8];
  P = update_parity_flag(A);
  CY = update_carry_flag(data16);
}

void compare(uint8_t reg){
  data16 = (uint16_t)A - reg;
  data8 = ((A & BIT_3_MASK) >> 1)
    | ((reg & BIT_3_MASK) >> 2)
    | ((data16 & BIT_3_MASK) >> 3);
  AC = !aux_carry_sub[data8];
  data8 = data16 & LOW_BYTE_MASK;
  S = update_sign_flag(data8);
  Z = update_zero_flag(data8);
  P = update_parity_flag(data8);
  CY = update_carry_flag(data16);

}

void logical_and(uint8_t reg){
  A &= reg;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  P = update_parity_flag(A);
  CLR(CY);
  CLR(AC);
}

void logical_or(uint8_t reg){
  A |= reg;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  P = update_parity_flag(A);
  CLR(CY);
  CLR(AC);
}

void logical_xor(uint8_t reg){
  A ^= reg;
  S = update_sign_flag(A);
  Z = update_zero_flag(A);
  //  TODO
  //  update AC
  P = update_parity_flag(A);
  CLR(CY);
}

void push(uint16_t reg){
  SP-=2;
  WR_WORD(SP, reg);
}

void pop(uint16_t* reg){
  (*reg) = RD_WORD(SP);
  SP+=2;
}

void call(){
  push(PC+3);
  PC = RD_WORD(PC+1);
}

void reset(uint16_t addr){
  push(PC+1);
  PC = addr;
}

