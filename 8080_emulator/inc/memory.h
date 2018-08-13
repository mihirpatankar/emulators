#ifndef _MEMORY_H
#define _MEMORY_H

#include "common.h"

#define TOTAL_MEMORY 0x10000

#define RD_BYTE(addr) memory_read_byte(addr)
#define RD_WORD(addr) memory_read_word(addr)

#define WR_BYTE(addr, value) memory_write_byte(addr, value)
#define WR_WORD(addr, value) memory_write_word(addr, value)

uint8_t* memory;
FILE* file_pointer;
uint32_t file_size;
uint8_t* code_buffer;

void init_memory();
uint16_t memory_read_word(uint16_t addr);
void memory_write_word(uint16_t addr, uint16_t word);
uint8_t memory_read_byte(uint16_t addr);
void memory_write_byte(uint16_t addr, uint16_t byte);
void read_rom_into_memory(char* file_name);
#endif //MEMORY_H
