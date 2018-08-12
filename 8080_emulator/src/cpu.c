#include "cpu.h"

void cpu_init(){
  state = (cpu_state*)malloc(sizeof(cpu_state));
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

