#include "common.h"
#include "cpu.h"
#include "memory.h"
#include "disassembler.h"
#include "debug.h"

int main(int argc, char* argv[]){
  if(argc != 2) {
      printf("Please enter the ROM path\n");
      return 1;
  }

 read_rom_into_memory(argv[1]);
 return 0;
}
