#include "hal.h"

uint8_t *memory_init(void) {
    memset(memory, 0, 0x10000);
    return &memory[0];
}

uint16_t read_word(uint16_t address) {
    return read_byte(address) | read_byte(address+1) << 8;
}

uint8_t read_byte(uint16_t address) {
    return memory[address];
}

void write_word(uint16_t address, uint16_t data) {
    write_byte(address, (data & 0xFF));
    write_byte(address + 1, (data>>8) & 0xFF);
}

void write_byte(uint16_t address, uint8_t data) {
    memory[address] = data;
}
