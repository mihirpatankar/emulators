#include "hal.h"
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
    
    CYCLES  = 0;
    PC      = pc;
}

int i8080_run_insn(void) {
    uint8_t opcode = read_byte(PC++);
    CYCLES += opcode_cycles[opcode];
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

        // Arithmetic
        case 0x80: ADD(B, 0); break;
        case 0x81: ADD(C, 0); break;
        case 0x82: ADD(D, 0); break;
        case 0x83: ADD(E, 0); break;
        case 0x84: ADD(H, 0); break;
        case 0x85: ADD(L, 0); break;
        case 0x86: temp_data_reg = read_byte(HL);
                   ADD(temp_data_reg, 0); 
                   break;
        case 0x87: ADD(A, 0); break;
        case 0xC6: temp_data_reg = read_byte(PC++);
                   ADD(temp_data_reg, 0); break;

        case 0x88: ADD(B, 1); break;
        case 0x89: ADD(C, 1); break;
        case 0x8A: ADD(D, 1); break;
        case 0x8B: ADD(E, 1); break;
        case 0x8C: ADD(H, 1); break;
        case 0x8D: ADD(L, 1); break;
        case 0x8E: temp_data_reg = read_byte(HL);
                   ADD(temp_data_reg, 1); break;
        case 0x8F: ADD(A, 1); break;
        case 0xCE: temp_data_reg = read_byte(PC++);
                   ADD(temp_data_reg, 1); break;
                   
        case 0x90: SUB(B, 0); break;
        case 0x91: SUB(C, 0); break;
        case 0x92: SUB(D, 0); break;
        case 0x93: SUB(E ,0); break;
        case 0x94: SUB(H, 0); break;
        case 0x95: SUB(L, 0); break;
        case 0x96: temp_data_reg = read_byte(HL);
                   SUB(temp_data_reg, 0); break;
        case 0x97: SUB(A, 0); break;
        case 0xD6: temp_data_reg = read_byte(PC++);
                   SUB(temp_data_reg, 0); break;

        case 0x98: SUB(B, 1); break;
        case 0x99: SUB(C, 1); break;
        case 0x9A: SUB(D, 1); break;
        case 0x9B: SUB(E, 1); break;
        case 0x9C: SUB(H, 1); break;
        case 0x9D: SUB(L, 1); break;
        case 0x9E: temp_data_reg = read_byte(HL);
                   SUB(temp_data_reg, 1); break;
        case 0x9F: SUB(A, 1); break;
        
        case 0xDE: temp_data_reg = read_byte(PC++);
                   SUB(temp_data_reg, 0); break;

        case 0x04: INR(B); break;
        case 0x0C: INR(C); break;
        case 0x14: INR(D); break;
        case 0x1C: INR(E); break;
        case 0x24: INR(H); break;
        case 0x2C: INR(L); break;
        case 0x34: temp_data_reg = read_byte(HL);
                   INR(temp_data_reg);
                   write_byte(HL, temp_data_reg); break;
        case 0x3C: INR(A); break;

        case 0x05: DCR(B); break;
        case 0x0D: DCR(C); break;
        case 0x15: DCR(D); break;
        case 0x1D: DCR(E); break;
        case 0x25: DCR(H); break;
        case 0x2D: DCR(L); break;
        case 0x35: temp_data_reg = read_byte(HL);
                   DCR(temp_data_reg);
                   write_byte(HL, temp_data_reg); break;
        case 0x3D: DCR(A); break;

        case 0x03: BC++; break;
        case 0x13: DE++; break;
        case 0x23: HL++; break;
        case 0x33: SP++; break;
                   
        case 0x0B: BC--; break;
        case 0x1B: DE--; break;
        case 0x2B: HL--; break;
        case 0x3B: SP--; break;
                   
        case 0x09: DAD(BC); break;
        case 0x19: DAD(DE); break;
        case 0x29: DAD(HL); break;
        case 0x39: DAD(SP); break;
                   
        case 0x27: temp_data_reg  = 0x00;
                   temp_carry = C_FLAG;
                   ls_nibble = (A & 0xF); 
                   ms_nibble = (A>>4) & 0xF;
                   if(A_FLAG || ls_nibble > 9) {
                       temp_data_reg = 0x06;
                   }
                   if(C_FLAG || (ls_nibble > 9 && ms_nibble >= 9) || ms_nibble > 9) {
                       temp_data_reg |= 0x60;
                       temp_carry = 1;         
                   }
                   ADD(temp_data_reg, 0);
                   P_FLAG = parity[A];
                   C_FLAG = temp_carry; break;

        // Logical
        case 0xA0: ANA(B); break;
        case 0xA1: ANA(C); break;
        case 0xA2: ANA(D); break;
        case 0xA3: ANA(E); break;
        case 0xA4: ANA(H); break;
        case 0xA5: ANA(L); break;
        case 0xA6: temp_data_reg = read_byte(HL);
                   ANA(temp_data_reg); break;
        case 0xA7: ANA(A); break;
        
        case 0xE6: temp_data_reg = read_byte(PC++);
                   ANA(temp_data_reg); break;

        case 0xA8: XRA(B); break;
        case 0xA9: XRA(C); break;
        case 0xAA: XRA(D); break;
        case 0xAB: XRA(E); break;
        case 0xAC: XRA(H); break;
        case 0xAD: XRA(L); break;
        case 0xAE: temp_data_reg = read_byte(HL);
                   XRA(temp_data_reg); break;
        case 0xAF: XRA(A); break;
        
        case 0xEE: temp_data_reg = read_byte(PC++);
                   XRA(temp_data_reg); break;
                   
        case 0xB0: ORA(B); break;
        case 0xB1: ORA(C); break;
        case 0xB2: ORA(D); break;
        case 0xB3: ORA(E); break;
        case 0xB4: ORA(H); break;
        case 0xB5: ORA(L); break;
        case 0xB6: temp_data_reg = read_byte(HL);
                   ORA(temp_data_reg); break;
        case 0xB7: ORA(A); break;
        
        case 0xF6: temp_data_reg = read_byte(PC++);
                   ORA(temp_data_reg); break;
        
        case 0xB8: CMP(B); break;
        case 0xB9: CMP(C); break;
        case 0xBA: CMP(D); break;
        case 0xBB: CMP(E); break;
        case 0xBC: CMP(H); break;
        case 0xBD: CMP(L); break;
        case 0xBE: temp_data_reg = read_byte(HL);
                   CMP(temp_data_reg); break;
        case 0xBF: CMP(A); break;
        
        case 0xFE: temp_data_reg = read_byte(PC++);
                   CMP(temp_data_reg); break;

        case 0x07: C_FLAG = ((A & 0x80) != 0);
                   A = (A << 1) | C_FLAG; break;
        case 0x0F: C_FLAG = (A & 0x1); 
                   A = (A >> 1) | (C_FLAG << 7); break;
        case 0x17: temp_data_reg = C_FLAG;
                   C_FLAG = ((A & 0x80) != 0);
                   A = (A << 1) | (temp_data_reg); break;
        case 0x1F: temp_data_reg = C_FLAG;
                   C_FLAG = (A & 0x1);
                   A = (A << 1) | (temp_data_reg << 7); break;
        case 0x2F: A ^= 0xFF; break;
        case 0x3F: C_FLAG = !C_FLAG; break;
        case 0x37: C_FLAG = 1; break;






        case 0x00:
        default: break;   
    }
    return opcode_cycles[opcode]; 
}


