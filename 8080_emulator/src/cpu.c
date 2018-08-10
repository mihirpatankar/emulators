#include "cpu.h"

void cpu_init(){
  state = (cpu_state*)malloc(sizeof(cpu_state));
  init_regs(state);
  init_flags(state);
}

void init_regs(cpu_state* state){
  PC=0xF800;
}

void init_flags(cpu_state* state){
  CY = 0;
  S = 0;
  Z = 0;
  AC = 0;
  P = 0;
  UN1 = 1;
  UN3 = 0;
  UN5 = 0;
}

void store_flags(cpu_state* state){

}

void get_flags(cpu_state* state){

}

