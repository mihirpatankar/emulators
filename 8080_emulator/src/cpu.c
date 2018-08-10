#include "cpu.h"

static i8080 cpu;

void i8080_init(uint16_t pc) {
    C_FLAG  = 0;
    UN1     = 1;
    P_FLAG  = 0;
    UN3     = 0;
    A_FLAG  = 0;
    UN5     = 0;
    Z_FLAG  = 0;
    S_FLAG  = 0;

    PC = pc;
}

void UnimplementedInstruction(void);


/*
 * Can probably return clock cycles
 */
int i8080_run_insn(void) {
    uint8_t opcode = read_byte(PC++);
    switch(opcode)
    {
        // Data Transfer
        case 0x40: // MOV (B, B); 
                   break;
        case 0x41: B = C; break;
        case 0x42: B = D; break;
        case 0x43: B = E; break;
        case 0x44: B = H; break;
        case 0x45: B = L; break;
        case 0x46: B = read_byte(HL); break;
        case 0x47: B = A; break;
        
        case 0x48: C = B; break;
        case 0x49: // MOV(C, C); 
                   break;
        case 0x4A: C = D; break;
        case 0x4B: C = E; break;
        case 0x4C: C = H; break;
        case 0x4D: C = L; break;
        case 0x4E: C = read_byte(HL); break;
        case 0x4F: C = A; break;

        case 0x50: D = B; break;
        case 0x51: D = C; break;
        case 0x52: // MOV (D, D); 
                   break;
        case 0x53: D = E; break;
        case 0x54: D = H; break;
        case 0x55: D = L; break;
        case 0x56: D = read_byte(HL); break;
        case 0x57: D = A; break;

        case 0x58: E = B; break;
        case 0x59: E = C; break;
        case 0x5A: E = D; break;
        case 0x5B: // MOV (E, E); 
                   break;
        case 0x5C: E = H; break;
        case 0x5D: E = L; break;
        case 0x5E: E = read_byte(HL); break;
        case 0x5F: E = A; break;

        case 0x60: H = B; break;
        case 0x61: H = C; break;
        case 0x62: H = D; break;
        case 0x63: H = E; break;
        case 0x64: // MOV (H, H); 
                   break;
        case 0x65: H = L; break;
        case 0x66: H = read_byte(HL); break;
        case 0x67: H = A; break;

        case 0x68: L = B; break;
        case 0x69: L = C; break;
        case 0x6A: L = D; break;
        case 0x6B: L = E; break;
        case 0x6C: L = H; break;
        case 0x6D: // MOV (L, L); 
                   break;
        case 0x6E: L = read_byte(HL); break;
        case 0x6F: L = A; break;

        case 0x70: write_byte(HL, B); break;
        case 0x71: write_byte(HL, C); break;
        case 0x72: write_byte(HL, D); break;
        case 0x73: write_byte(HL, E); break;
        case 0x74: write_byte(HL, H); break;
        case 0x75: write_byte(HL, L); break;
        case 0x77: write_byte(HL, A); break;

        case 0x78: A = B; break;
        case 0x79: A = C; break;
        case 0x7A: A = D; break;
        case 0x7B: A = E; break;
        case 0x7C: A = H; break;
        case 0x7D: A = L; break;
        case 0x7E: A = read_byte(HL); break;
        case 0x7F: // MOV (A, A); 
                   break;

        case 0x06: B = read_byte(PC++); break;
        case 0x0E: C = read_byte(PC++); break;
        case 0x16: D = read_byte(PC++); break;
        case 0x1E: E = read_byte(PC++); break;
        case 0x26: H = read_byte(PC++); break;
        case 0x2E: L = read_byte(PC++); break;
        case 0x36: write_byte(HL, read_byte(PC++)); break;
        case 0x3E: A = read_byte(PC++); break;

        case 0x01: BC = read_word(PC); PC += 2; break;
        case 0x11: DE = read_word(PC); PC += 2; break;
        case 0x21: HL = read_word(PC); PC += 2; break;
        case 0x31: SP = read_word(PC); PC += 2; break;
    
        case 0x3A: A = read_byte(read_word(PC)); PC += 2; break;
        case 0x32: write_byte(read_word(PC), A); PC += 2; break;
        case 0x2A: HL = read_word(read_word(PC)); PC += 2; break;
        case 0x22: write_word(read_word(PC), HL); PC += 2; break;

        case 0x0A: A = read_byte(BC); break;
        case 0x1A: A = read_byte(DE); break;
        case 0x02: write_byte(BC, A); break;
        case 0x12: write_byte(DE, A); break;

        case 0xEB: DE = DE ^ HL; HL = DE ^ HL; DE = DE ^ HL; /* XOR swap */ break;








        case 0x00:
        default: UnimplementedInstruction(); break;   
    }
    return 0; 
}


