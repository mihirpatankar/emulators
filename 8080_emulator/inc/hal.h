#ifndef __HAL_8080_H__
#define __HAL_8080_H__

/*
 * The entire addressable memory
 */
static uint8_t memory[0x10000];

/*
 * For reading operations only address is needed
 */
uint16_t read_word(uint16_t address);
uint8_t read_byte(uint16_t address);

/*
 * For writing operations, address and value is needed
 */ 
void write_word(uint16_t address, uint16_t data);
void write_byte(uint16_t address, uint8_t data);

#endif
