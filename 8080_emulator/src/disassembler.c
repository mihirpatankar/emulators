/*
 * 8080 Disassembler 
 * Made by following the Intel 8080 Microcomputer Systems User's Manual
 * Chapter 4
 */

#include <stdio.h>
#include <stdint.h>

/*
 * disassemble 
 * buffer:  pointer to the start of the buffer
 * pc:      program counter (offset from the start of the buffer
 *
 * returns:
 *          the number of bytes in the opcode 
 */

uint16_t disassemble(uint8_t *buffer, uint16_t pc)
{
    uint16_t bytes = 1;
    printf("%04x:\t",pc);

    switch(buffer[pc]) {
        // Data Transfer
        case 0x40: printf("MOV B, B"); break;
        case 0x41: printf("MOV B, C"); break;
        case 0x42: printf("MOV B, D"); break;
        case 0x43: printf("MOV B, E"); break;
        case 0x44: printf("MOV B, H"); break;
        case 0x45: printf("MOV B, L"); break;
        case 0x46: printf("MOV B, M"); break;
        case 0x47: printf("MOV B, A"); break;
        
        case 0x48: printf("MOV C, B"); break;
        case 0x49: printf("MOV C, C"); break;
        case 0x4A: printf("MOV C, D"); break;
        case 0x4B: printf("MOV C, E"); break;
        case 0x4C: printf("MOV C, H"); break;
        case 0x4D: printf("MOV C, L"); break;
        case 0x4E: printf("MOV C, M"); break;
        case 0x4F: printf("MOV C, A"); break;

        case 0x50: printf("MOV D, B"); break;
        case 0x51: printf("MOV D, C"); break;
        case 0x52: printf("MOV D, D"); break;
        case 0x53: printf("MOV D, E"); break;
        case 0x54: printf("MOV D, H"); break;
        case 0x55: printf("MOV D, L"); break;
        case 0x56: printf("MOV D, M"); break;
        case 0x57: printf("MOV D, A"); break;

        case 0x58: printf("MOV E, B"); break;
        case 0x59: printf("MOV E, C"); break;
        case 0x5A: printf("MOV E, D"); break;
        case 0x5B: printf("MOV E, E"); break;
        case 0x5C: printf("MOV E, H"); break;
        case 0x5D: printf("MOV E, L"); break;
        case 0x5E: printf("MOV E, M"); break;
        case 0x5F: printf("MOV E, A"); break;

        case 0x60: printf("MOV H, B"); break;
        case 0x61: printf("MOV H, C"); break;
        case 0x62: printf("MOV H, D"); break;
        case 0x63: printf("MOV H, E"); break;
        case 0x64: printf("MOV H, H"); break;
        case 0x65: printf("MOV H, L"); break;
        case 0x66: printf("MOV H, M"); break;
        case 0x67: printf("MOV H, A"); break;

        case 0x68: printf("MOV L, B"); break;
        case 0x69: printf("MOV L, C"); break;
        case 0x6A: printf("MOV L, D"); break;
        case 0x6B: printf("MOV L, E"); break;
        case 0x6C: printf("MOV L, H"); break;
        case 0x6D: printf("MOV L, L"); break;
        case 0x6E: printf("MOV L, M"); break;
        case 0x6F: printf("MOV L, A"); break;

        case 0x70: printf("MOV M, B"); break;
        case 0x71: printf("MOV M, C"); break;
        case 0x72: printf("MOV M, D"); break;
        case 0x73: printf("MOV M, E"); break;
        case 0x74: printf("MOV M, H"); break;
        case 0x75: printf("MOV M, L"); break;
        case 0x77: printf("MOV M, A"); break;

        case 0x78: printf("MOV A, B"); break;
        case 0x79: printf("MOV A, C"); break;
        case 0x7A: printf("MOV A, D"); break;
        case 0x7B: printf("MOV A, E"); break;
        case 0x7C: printf("MOV A, H"); break;
        case 0x7D: printf("MOV A, L"); break;
        case 0x7E: printf("MOV A, M"); break;
        case 0x7F: printf("MOV A, A"); break;

        case 0x06: printf("MVI B, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x0E: printf("MVI C, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x16: printf("MVI D, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x1E: printf("MVI E, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x26: printf("MVI H, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x2E: printf("MVI L, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x36: printf("MVI M, #0x%02x", buffer[pc+1]); bytes++; break;
        case 0x3E: printf("MVI A, #0x%02x", buffer[pc+1]); bytes++; break;

        case 0x01: printf("LXI B, #$%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
        case 0x11: printf("LXI D, #$%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
        case 0x21: printf("LXI H, #$%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
        case 0x31: printf("LXI SP, #$%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
    
        case 0x3A: printf("LDA #%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
        case 0x32: printf("STA #%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
        case 0x2A: printf("LHLD #%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;
        case 0x22: printf("SHLD #%02x%02x", buffer[pc+1], buffer[pc+2]); bytes+=2; break;

        case 0x0A: printf("LDAX B"); break;
        case 0x1A: printf("LDAX D"); break;
        case 0x02: printf("STAX B"); break;
        case 0x12: printf("STAX D"); break;

        case 0xEB: printf("XCHG"); break;

        // Arithmetic
        // Logical
        // Branch
        // Stack, I/O and Machine Control
        case 0x00: printf("NOP"); break;    
    
    
    }

    printf("\n");

    return bytes;
}


int main(int argc, char* argv[])
{


}
