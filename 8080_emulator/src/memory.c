#include "memory.h"

void init_memory(){
  memory = (uint8_t*)malloc(TOTAL_MEMORY);
}

uint16_t memory_read_word(uint16_t addr){
  uint8_t low_byte = memory_read_byte(addr);
  uint8_t high_byte = memory_read_byte(addr+1);
  uint16_t word = (high_byte << BYTE) | low_byte;
  return word;
}

void memory_write_word(uint16_t addr, uint16_t word){
  uint8_t low_byte = word & LOW_BYTE_MASK;
  uint8_t high_byte = (word & HIGH_BYTE_MASK) >> BYTE;
  memory_write_byte(addr, low_byte);
  memory_write_byte(addr + 1, high_byte);
}

uint8_t memory_read_byte(uint16_t addr){
  return memory[addr];
}

void memory_write_byte(uint16_t addr, uint16_t byte){
  memory[addr] = byte;
}

