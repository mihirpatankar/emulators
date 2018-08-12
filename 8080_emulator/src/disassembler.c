#include "disassembler.h"

void increment(uint8_t reg){
  ++reg;
  S = (reg & BIT_7_MASK) != 0;
  Z = (reg == 0);
  AC = (reg & 0x0f) == 0;
  P = parity_table[reg];
}

void decrement(uint8_t reg){
  --reg;
  S = (reg & BIT_7_MASK) != 0;
  Z = (reg == 0);
  AC = (reg & 0x0f) == 0x0f;
  P = parity_table[reg];

}

uint8_t disassemble_opcode(uint8_t* code_buffer, uint16_t pc){
  uint8_t opcode_bytes = 1;
  
  switch(code_buffer[pc]){
    case 0x00: printf("NOP"); break;
    case 0x01: printf("LXI    B,#$%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x02: printf("STAX   B"); break;
    case 0x03: printf("INX    B"); break;
    case 0x04: printf("INR    B"); break;
    case 0x05: printf("DCR    B"); break;
    case 0x06: printf("MVI    B,#$%02x", code_buffer[pc+1]); opcode_bytes=2; break;
    case 0x07: printf("RLC"); break;
    case 0x08: printf("NOP"); break;
    case 0x09: printf("DAD    B"); break;
    case 0x0a: printf("LDAX   B"); break;
    case 0x0b: printf("DCX    B"); break;
    case 0x0c: printf("INR    C"); break;
    case 0x0d: printf("DCR    C"); break;
    case 0x0e: printf("MVI    C,#$%02x", code_buffer[pc+1]); opcode_bytes = 2;	break;
    case 0x0f: printf("RRC"); break;

    case 0x10: printf("NOP"); break;
    case 0x11: printf("LXI    D,#$%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x12: printf("STAX   D"); break;
    case 0x13: printf("INX    D"); break;
    case 0x14: printf("INR    D"); break;
    case 0x15: printf("DCR    D"); break;
    case 0x16: printf("MVI    D,#$%02x", code_buffer[pc+1]); opcode_bytes=2; break;
    case 0x17: printf("RAL"); break;
    case 0x18: printf("NOP"); break;
    case 0x19: printf("DAD    D"); break;
    case 0x1a: printf("LDAX   D"); break;
    case 0x1b: printf("DCX    D"); break;
    case 0x1c: printf("INR    E"); break;
    case 0x1d: printf("DCR    E"); break;
    case 0x1e: printf("MVI    E,#$%02x", code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0x1f: printf("RAR"); break;

    case 0x20: printf("NOP"); break;
    case 0x21: printf("LXI    H,#$%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x22: printf("SHLD   $%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x23: printf("INX    H"); break;
    case 0x24: printf("INR    H"); break;
    case 0x25: printf("DCR    H"); break;
    case 0x26: printf("MVI    H,#$%02x", code_buffer[pc+1]); opcode_bytes=2; break;
    case 0x27: printf("DAA"); break;
    case 0x28: printf("NOP"); break;
    case 0x29: printf("DAD    H"); break;
    case 0x2a: printf("LHLD   $%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x2b: printf("DCX    H"); break;
    case 0x2c: printf("INR    L"); break;
    case 0x2d: printf("DCR    L"); break;
    case 0x2e: printf("MVI    L,#$%02x", code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0x2f: printf("CMA"); break;

    case 0x30: printf("NOP"); break;
    case 0x31: printf("LXI    SP,#$%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x32: printf("STA    $%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x33: printf("INX    SP"); break;
    case 0x34: printf("INR    M"); break;
    case 0x35: printf("DCR    M"); break;
    case 0x36: printf("MVI    M,#$%02x", code_buffer[pc+1]); opcode_bytes=2; break;
    case 0x37: printf("STC"); break;
    case 0x38: printf("NOP"); break;
    case 0x39: printf("DAD    SP"); break;
    case 0x3a: printf("LDA    $%02x%02x", code_buffer[pc+2], code_buffer[pc+1]); opcode_bytes=3; break;
    case 0x3b: printf("DCX    SP"); break;
    case 0x3c: printf("INR    A"); break;
    case 0x3d: printf("DCR    A"); break;
    case 0x3e: printf("MVI    A,#$%02x", code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0x3f: printf("CMC"); break;

    case 0x40: printf("MOV    B,B"); break;
    case 0x41: printf("MOV    B,C"); break;
    case 0x42: printf("MOV    B,D"); break;
    case 0x43: printf("MOV    B,E"); break;
    case 0x44: printf("MOV    B,H"); break;
    case 0x45: printf("MOV    B,L"); break;
    case 0x46: printf("MOV    B,M"); break;
    case 0x47: printf("MOV    B,A"); break;
    case 0x48: printf("MOV    C,B"); break;
    case 0x49: printf("MOV    C,C"); break;
    case 0x4a: printf("MOV    C,D"); break;
    case 0x4b: printf("MOV    C,E"); break;
    case 0x4c: printf("MOV    C,H"); break;
    case 0x4d: printf("MOV    C,L"); break;
    case 0x4e: printf("MOV    C,M"); break;
    case 0x4f: printf("MOV    C,A"); break;
      
    case 0x50: printf("MOV    D,B"); break;
    case 0x51: printf("MOV    D,C"); break;
    case 0x52: printf("MOV    D,D"); break;
    case 0x53: printf("MOV    D.E"); break;
    case 0x54: printf("MOV    D,H"); break;
    case 0x55: printf("MOV    D,L"); break;
    case 0x56: printf("MOV    D,M"); break;
    case 0x57: printf("MOV    D,A"); break;
    case 0x58: printf("MOV    E,B"); break;
    case 0x59: printf("MOV    E,C"); break;
    case 0x5a: printf("MOV    E,D"); break;
    case 0x5b: printf("MOV    E,E"); break;
    case 0x5c: printf("MOV    E,H"); break;
    case 0x5d: printf("MOV    E,L"); break;
    case 0x5e: printf("MOV    E,M"); break;
    case 0x5f: printf("MOV    E,A"); break;

    case 0x60: printf("MOV    H,B"); break;
    case 0x61: printf("MOV    H,C"); break;
    case 0x62: printf("MOV    H,D"); break;
    case 0x63: printf("MOV    H.E"); break;
    case 0x64: printf("MOV    H,H"); break;
    case 0x65: printf("MOV    H,L"); break;
    case 0x66: printf("MOV    H,M"); break;
    case 0x67: printf("MOV    H,A"); break;
    case 0x68: printf("MOV    L,B"); break;
    case 0x69: printf("MOV    L,C"); break;
    case 0x6a: printf("MOV    L,D"); break;
    case 0x6b: printf("MOV    L,E"); break;
    case 0x6c: printf("MOV    L,H"); break;
    case 0x6d: printf("MOV    L,L"); break;
    case 0x6e: printf("MOV    L,M"); break;
    case 0x6f: printf("MOV    L,A"); break;

    case 0x70: printf("MOV    M,B"); break;
    case 0x71: printf("MOV    M,C"); break;
    case 0x72: printf("MOV    M,D"); break;
    case 0x73: printf("MOV    M.E"); break;
    case 0x74: printf("MOV    M,H"); break;
    case 0x75: printf("MOV    M,L"); break;
    case 0x76: printf("HLT");        break;
    case 0x77: printf("MOV    M,A"); break;
    case 0x78: printf("MOV    A,B"); break;
    case 0x79: printf("MOV    A,C"); break;
    case 0x7a: printf("MOV    A,D"); break;
    case 0x7b: printf("MOV    A,E"); break;
    case 0x7c: printf("MOV    A,H"); break;
    case 0x7d: printf("MOV    A,L"); break;
    case 0x7e: printf("MOV    A,M"); break;
    case 0x7f: printf("MOV    A,A"); break;

    case 0x80: printf("ADD    B"); break;
    case 0x81: printf("ADD    C"); break;
    case 0x82: printf("ADD    D"); break;
    case 0x83: printf("ADD    E"); break;
    case 0x84: printf("ADD    H"); break;
    case 0x85: printf("ADD    L"); break;
    case 0x86: printf("ADD    M"); break;
    case 0x87: printf("ADD    A"); break;
    case 0x88: printf("ADC    B"); break;
    case 0x89: printf("ADC    C"); break;
    case 0x8a: printf("ADC    D"); break;
    case 0x8b: printf("ADC    E"); break;
    case 0x8c: printf("ADC    H"); break;
    case 0x8d: printf("ADC    L"); break;
    case 0x8e: printf("ADC    M"); break;
    case 0x8f: printf("ADC    A"); break;

    case 0x90: printf("SUB    B"); break;
    case 0x91: printf("SUB    C"); break;
    case 0x92: printf("SUB    D"); break;
    case 0x93: printf("SUB    E"); break;
    case 0x94: printf("SUB    H"); break;
    case 0x95: printf("SUB    L"); break;
    case 0x96: printf("SUB    M"); break;
    case 0x97: printf("SUB    A"); break;
    case 0x98: printf("SBB    B"); break;
    case 0x99: printf("SBB    C"); break;
    case 0x9a: printf("SBB    D"); break;
    case 0x9b: printf("SBB    E"); break;
    case 0x9c: printf("SBB    H"); break;
    case 0x9d: printf("SBB    L"); break;
    case 0x9e: printf("SBB    M"); break;
    case 0x9f: printf("SBB    A"); break;

    case 0xa0: printf("ANA    B"); break;
    case 0xa1: printf("ANA    C"); break;
    case 0xa2: printf("ANA    D"); break;
    case 0xa3: printf("ANA    E"); break;
    case 0xa4: printf("ANA    H"); break;
    case 0xa5: printf("ANA    L"); break;
    case 0xa6: printf("ANA    M"); break;
    case 0xa7: printf("ANA    A"); break;
    case 0xa8: printf("XRA    B"); break;
    case 0xa9: printf("XRA    C"); break;
    case 0xaa: printf("XRA    D"); break;
    case 0xab: printf("XRA    E"); break;
    case 0xac: printf("XRA    H"); break;
    case 0xad: printf("XRA    L"); break;
    case 0xae: printf("XRA    M"); break;
    case 0xaf: printf("XRA    A"); break;

    case 0xb0: printf("ORA    B"); break;
    case 0xb1: printf("ORA    C"); break;
    case 0xb2: printf("ORA    D"); break;
    case 0xb3: printf("ORA    E"); break;
    case 0xb4: printf("ORA    H"); break;
    case 0xb5: printf("ORA    L"); break;
    case 0xb6: printf("ORA    M"); break;
    case 0xb7: printf("ORA    A"); break;
    case 0xb8: printf("CMP    B"); break;
    case 0xb9: printf("CMP    C"); break;
    case 0xba: printf("CMP    D"); break;
    case 0xbb: printf("CMP    E"); break;
    case 0xbc: printf("CMP    H"); break;
    case 0xbd: printf("CMP    L"); break;
    case 0xbe: printf("CMP    M"); break;
    case 0xbf: printf("CMP    A"); break;

    case 0xc0: printf("RNZ"); break;
    case 0xc1: printf("POP    B"); break;
    case 0xc2: printf("JNZ    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xc3: printf("JMP    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xc4: printf("CNZ    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xc5: printf("PUSH   B"); break;
    case 0xc6: printf("ADI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xc7: printf("RST    0"); break;
    case 0xc8: printf("RZ"); break;
    case 0xc9: printf("RET"); break;
    case 0xca: printf("JZ     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xcb: printf("JMP    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xcc: printf("CZ     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xcd: printf("CALL   $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xce: printf("ACI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xcf: printf("RST    1"); break;

    case 0xd0: printf("RNC"); break;
    case 0xd1: printf("POP    D"); break;
    case 0xd2: printf("JNC    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xd3: printf("OUT    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xd4: printf("CNC    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xd5: printf("PUSH   D"); break;
    case 0xd6: printf("SUI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xd7: printf("RST    2"); break;
    case 0xd8: printf("RC");  break;
    case 0xd9: printf("RET"); break;
    case 0xda: printf("JC     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xdb: printf("IN     #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xdc: printf("CC     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xdd: printf("CALL   $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xde: printf("SBI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xdf: printf("RST    3"); break;

    case 0xe0: printf("RPO"); break;
    case 0xe1: printf("POP    H"); break;
    case 0xe2: printf("JPO    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xe3: printf("XTHL");break;
    case 0xe4: printf("CPO    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xe5: printf("PUSH   H"); break;
    case 0xe6: printf("ANI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xe7: printf("RST    4"); break;
    case 0xe8: printf("RPE"); break;
    case 0xe9: printf("PCHL");break;
    case 0xea: printf("JPE    $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xeb: printf("XCHG"); break;
    case 0xec: printf("CPE     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xed: printf("CALL   $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xee: printf("XRI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xef: printf("RST    5"); break;

    case 0xf0: printf("RP");  break;
    case 0xf1: printf("POP    PSW"); break;
    case 0xf2: printf("JP     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xf3: printf("DI");  break;
    case 0xf4: printf("CP     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xf5: printf("PUSH   PSW"); break;
    case 0xf6: printf("ORI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xf7: printf("RST    6"); break;
    case 0xf8: printf("RM");  break;
    case 0xf9: printf("SPHL");break;
    case 0xfa: printf("JM     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xfb: printf("EI");  break;
    case 0xfc: printf("CM     $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xfd: printf("CALL   $%02x%02x",code_buffer[pc+2],code_buffer[pc+1]); opcode_bytes = 3; break;
    case 0xfe: printf("CPI    #$%02x",code_buffer[pc+1]); opcode_bytes = 2; break;
    case 0xff: printf("RST    7"); break;
    //never reach here
    default : opcode_bytes = -1;
  }

  return opcode_bytes;
}

uint8_t emulate_instruction(uint8_t opcode){
    
  uint8_t cpu_cycles=-1;

  switch(opcode){
    //nop
    case 0x00:break;
    // undocumented nop.
    case 0x08:break;
    case 0x10:break;
    case 0x18:break;
    case 0x20:break;
    case 0x28:break;
    case 0x30:break;
    case 0x38:break;

    case 0x01:            /* lxi b, data16 */
        cpu_cycles = 10;
        BC = RD_WORD(PC+1);
        break;

    case 0x02:            /* stax b */
        cpu_cycles = 7;
        WR_BYTE(BC, A);//(BC) --> A
        break;

    case 0x03:            /* inx b */
        cpu_cycles = 5;
        BC++;
        break;

    case 0x04:            /* inr b */
        cpu_cycles = 5;
        increment(B);
        break;

    case 0x05:            /* dcr b */
        cpu_cycles = 5;
        decrement(B);
        break;

    case 0x06:            /* mvi b, data8 */
        cpu_cycles = 7;
        B = RD_BYTE(PC+1);
        break;

// TODO
//    case 0x07:            /* rlc */
//        cpu_cycles = 4;
//        C_FLAG = ((A & 0x80) != 0);
//        A = (A << 1) | C_FLAG;
//        break;

//    case 0x09:            /* dad b */
//        cpu_cycles = 10;
//        DAD(BC);
//        break;

    case 0x0A:            /* ldax b */
        cpu_cycles = 7;
        A = RD_BYTE(BC);
        break;

    case 0x0B:            /* dcx b */
        cpu_cycles = 5;
        BC--;
        break;

    case 0x0C:            /* inr c */
        cpu_cycles = 5;
        increment(C);
        break;

    case 0x0D:            /* dcr c */
        cpu_cycles = 5;
        decrement(C);
        break;

    case 0x0E:            /* mvi c, data8 */
        cpu_cycles = 7;
        C = RD_BYTE(PC+1);
        break;

//    case 0x0F:            /* rrc */
//        cpu_cycles = 4;
//        C_FLAG = A & 0x01;
//        A = (A >> 1) | (C_FLAG << 7);
//        break;

    case 0x11:            /* lxi d, data16 */
        cpu_cycles = 10;
        DE = RD_WORD(PC+1);
        break;

    case 0x12:            /* stax d */
        cpu_cycles = 7;
        WR_BYTE(DE, A);
        break;

    case 0x13:            /* inx d */
        cpu_cycles = 5;
        DE++;
        break;

    case 0x14:            /* inr d */
        cpu_cycles = 5;
        increment(D);
        break;

    case 0x15:            /* dcr d */
        cpu_cycles = 5;
        decrement(D);
        break;

    case 0x16:            /* mvi d, data8 */
        cpu_cycles = 7;
        D = RD_BYTE(PC+1);
        break;

//    case 0x17:            /* ral */
//        cpu_cycles = 4;
//        work8 = (uns8)C_FLAG;
//        C_FLAG = ((A & 0x80) != 0);
//        A = (A << 1) | work8;
//        break;

//    case 0x19:            /* dad d */
//        cpu_cycles = 10;
//        DAD(DE);
//        break;

    case 0x1A:            /* ldax d */
        cpu_cycles = 7;
        A = RD_BYTE(DE);
        break;

    case 0x1B:            /* dcx d */
        cpu_cycles = 5;
        DE--;
        break;

    case 0x1C:            /* inr e */
        cpu_cycles = 5;
        increment(E);
        break;

    case 0x1D:            /* dcr e */
        cpu_cycles = 5;
        decrement(E);
        break;

    case 0x1E:            /* mvi e, data8 */
        cpu_cycles = 7;
        E = RD_BYTE(PC+1);
        break;

//    case 0x1F:             /* rar */
//        cpu_cycles = 4;
//        work8 = (uns8)C_FLAG;
//        C_FLAG = A & 0x01;
//        A = (A >> 1) | (work8 << 7);
//        break;

    case 0x21:             /* lxi h, data16 */
        cpu_cycles = 10;
        HL = RD_WORD(PC+1);
        break;

    case 0x22:            /* shld addr */
        cpu_cycles = 16;
        WR_WORD(RD_WORD(PC+1), HL);
        break;

    case 0x23:            /* inx h */
        cpu_cycles = 5;
        HL++;
        break;

    case 0x24:            /* inr h */
        cpu_cycles = 5;
        increment(H);
        break;

    case 0x25:            /* dcr h */
        cpu_cycles = 5;
        decrement(H);
        break;

    case 0x26:            /* mvi h, data8 */
        cpu_cycles = 7;
        H = RD_BYTE(PC+1);
        break;

//    case 0x27:            /* daa */
//        cpu_cycles = 4;
//        carry = (uns8)C_FLAG;
//        add = 0;
//        if (H_FLAG || (A & 0x0f) > 9) {
//            add = 0x06;
//        }
//        if (C_FLAG || (A >> 4) > 9 || ((A >> 4) >= 9 && (A & 0x0f) > 9)) {
//            add |= 0x60;
//            carry = 1;
//        }
//        ADD(add);
//        P_FLAG = PARITY(A);
//        C_FLAG = carry;
//        break;

//    case 0x29:            /* dad hl */
//        cpu_cycles = 10;
//        DAD(HL);
//        break;

    case 0x2A:            /* ldhl addr */
        cpu_cycles = 16;
        HL = RD_WORD(RD_WORD(PC+1));
        break;

    case 0x2B:            /* dcx h */
        cpu_cycles = 5;
        HL--;
        break;

    case 0x2C:            /* inr l */
        cpu_cycles = 5;
        increment(L);
        break;

    case 0x2D:            /* dcr l */
        cpu_cycles = 5;
        decrement(L);
        break;

    case 0x2E:            /* mvi l, data8 */
        cpu_cycles = 7;
        L = RD_BYTE(PC+1);
        break;

    case 0x2F:            /* cma */
        cpu_cycles = 4;
        A ^= 0xFF;
        break;

    case 0x31:            /* lxi sp, data16 */
        cpu_cycles = 10;
        SP = RD_WORD(PC+1);
        break;

    case 0x32:            /* sta addr */
        cpu_cycles = 13;
        WR_BYTE(RD_WORD(PC+1), A);
        break;

    case 0x33:            /* inx sp */
        cpu_cycles = 5;
        SP++;
        break;

//    case 0x34:            /* inr m */
//        cpu_cycles = 10;
//        work8 = RD_BYTE(HL);
//        INR(work8);
//        WR_BYTE(HL, work8);
//        break;
//
//    case 0x35:            /* dcr m */
//        cpu_cycles = 10;
//        work8 = RD_BYTE(HL);
//        DCR(work8);
//        WR_BYTE(HL, work8);
//        break;

    case 0x36:            /* mvi m, data8 */
        cpu_cycles = 10;
        WR_BYTE(HL, RD_BYTE(PC+1));
        break;

    case 0x37:            /* stc */
        cpu_cycles = 4;
        SET(CY);
        break;

    case 0x39:            /* dad sp */
        cpu_cycles = 10;
        DAD(SP);
        break;

    case 0x3A:            /* lda addr */
        cpu_cycles = 13;
        A = RD_BYTE(RD_WORD(PC+1));
        break;

    case 0x3B:            /* dcx sp */
        cpu_cycles = 5;
        SP--;
        break;

    case 0x3C:            /* inr a */
        cpu_cycles = 5;
        increment(A);
        break;

    case 0x3D:            /* dcr a */
        cpu_cycles = 5;
        decrement(A);
        break;

    case 0x3E:            /* mvi a, data8 */
        cpu_cycles = 7;
        A = RD_BYTE(PC+1);
        break;

    case 0x3F:            /* cmc */
        cpu_cycles = 4;
        TGL(CY);
        break;

    case 0x40:            /* mov b, b */
        cpu_cycles = 4;
        break;

    case 0x41:            /* mov b, c */
        cpu_cycles = 5;
        B = C;
        break;

    case 0x42:            /* mov b, d */
        cpu_cycles = 5;
        B = D;
        break;

    case 0x43:            /* mov b, e */
        cpu_cycles = 5;
        B = E;
        break;

    case 0x44:            /* mov b, h */
        cpu_cycles = 5;
        B = H;
        break;

    case 0x45:            /* mov b, l */
        cpu_cycles = 5;
        B = L;
        break;

    case 0x46:            /* mov b, m */
        cpu_cycles = 7;
        B = RD_BYTE(HL);
        break;

    case 0x47:            /* mov b, a */
        cpu_cycles = 5;
        B = A;
        break;

    case 0x48:            /* mov c, b */
        cpu_cycles = 5;
        C = B;
        break;

    case 0x49:            /* mov c, c */
        cpu_cycles = 5;
        break;

    case 0x4A:            /* mov c, d */
        cpu_cycles = 5;
        C = D;
        break;

    case 0x4B:            /* mov c, e */
        cpu_cycles = 5;
        C = E;
        break;

    case 0x4C:            /* mov c, h */
        cpu_cycles = 5;
        C = H;
        break;

    case 0x4D:            /* mov c, l */
        cpu_cycles = 5;
        C = L;
        break;

    case 0x4E:            /* mov c, m */
        cpu_cycles = 7;
        C = RD_BYTE(HL);
        break;

    case 0x4F:            /* mov c, a */
        cpu_cycles = 5;
        C = A;
        break;

    case 0x50:            /* mov d, b */
        cpu_cycles = 5;
        D = B;
        break;

    case 0x51:            /* mov d, c */
        cpu_cycles = 5;
        D = C;
        break;

    case 0x52:            /* mov d, d */
        cpu_cycles = 5;
        break;

    case 0x53:            /* mov d, e */
        cpu_cycles = 5;
        D = E;
        break;

    case 0x54:            /* mov d, h */
        cpu_cycles = 5;
        D = H;
        break;

    case 0x55:            /* mov d, l */
        cpu_cycles = 5;
        D = L;
        break;

    case 0x56:            /* mov d, m */
        cpu_cycles = 7;
        D = RD_BYTE(HL);
        break;

    case 0x57:            /* mov d, a */
        cpu_cycles = 5;
        D = A;
        break;

    case 0x58:            /* mov e, b */
        cpu_cycles = 5;
        E = B;
        break;

    case 0x59:            /* mov e, c */
        cpu_cycles = 5;
        E = C;
        break;

    case 0x5A:            /* mov e, d */
        cpu_cycles = 5;
        E = D;
        break;

    case 0x5B:            /* mov e, e */
        cpu_cycles = 5;
        break;

    case 0x5C:            /* mov c, h */
        cpu_cycles = 5;
        E = H;
        break;

    case 0x5D:            /* mov c, l */
        cpu_cycles = 5;
        E = L;
        break;

    case 0x5E:            /* mov c, m */
        cpu_cycles = 7;
        E = RD_BYTE(HL);
        break;

    case 0x5F:            /* mov c, a */
        cpu_cycles = 5;
        E = A;
        break;

    case 0x60:            /* mov h, b */
        cpu_cycles = 5;
        H = B;
        break;

    case 0x61:            /* mov h, c */
        cpu_cycles = 5;
        H = C;
        break;

    case 0x62:            /* mov h, d */
        cpu_cycles = 5;
        H = D;
        break;

    case 0x63:            /* mov h, e */
        cpu_cycles = 5;
        H = E;
        break;

    case 0x64:            /* mov h, h */
        cpu_cycles = 5;
        break;

    case 0x65:            /* mov h, l */
        cpu_cycles = 5;
        H = L;
        break;

    case 0x66:            /* mov h, m */
        cpu_cycles = 7;
        H = RD_BYTE(HL);
        break;

    case 0x67:            /* mov h, a */
        cpu_cycles = 5;
        H = A;
        break;

    case 0x68:            /* mov l, b */
        cpu_cycles = 5;
        L = B;
        break;

    case 0x69:            /* mov l, c */
        cpu_cycles = 5;
        L = C;
        break;

    case 0x6A:            /* mov l, d */
        cpu_cycles = 5;
        L = D;
        break;

    case 0x6B:            /* mov l, e */
        cpu_cycles = 5;
        L = E;
        break;

    case 0x6C:            /* mov l, h */
        cpu_cycles = 5;
        L = H;
        break;

    case 0x6D:            /* mov l, l */
        cpu_cycles = 5;
        break;

    case 0x6E:            /* mov l, m */
        cpu_cycles = 7;
        L = RD_BYTE(HL);
        break;

    case 0x6F:            /* mov l, a */
        cpu_cycles = 5;
        L = A;
        break;

    case 0x70:            /* mov m, b */
        cpu_cycles = 7;
        WR_BYTE(HL, B);
        break;

    case 0x71:            /* mov m, c */
        cpu_cycles = 7;
        WR_BYTE(HL, C);
        break;

    case 0x72:            /* mov m, d */
        cpu_cycles = 7;
        WR_BYTE(HL, D);
        break;

    case 0x73:            /* mov m, e */
        cpu_cycles = 7;
        WR_BYTE(HL, E);
        break;

    case 0x74:            /* mov m, h */
        cpu_cycles = 7;
        WR_BYTE(HL, H);
        break;

    case 0x75:            /* mov m, l */
        cpu_cycles = 7;
        WR_BYTE(HL, L);
        break;

    case 0x76:            /* hlt */
        cpu_cycles = 4;
        PC--;
        break;

    case 0x77:            /* mov m, a */
        cpu_cycles = 7;
        WR_BYTE(HL, A);
        break;

    case 0x78:            /* mov a, b */
        cpu_cycles = 5;
        A = B;
        break;

    case 0x79:            /* mov a, c */
        cpu_cycles = 5;
        A = C;
        break;

    case 0x7A:            /* mov a, d */
        cpu_cycles = 5;
        A = D;
        break;

    case 0x7B:            /* mov a, e */
        cpu_cycles = 5;
        A = E;
        break;

    case 0x7C:            /* mov a, h */
        cpu_cycles = 5;
        A = H;
        break;

    case 0x7D:            /* mov a, l */
        cpu_cycles = 5;
        A = L;
        break;

    case 0x7E:            /* mov a, m */
        cpu_cycles = 7;
        A = RD_BYTE(HL);
        break;

    case 0x7F:            /* mov a, a */
        cpu_cycles = 5;
        break;

    default : break;

  }

  return cpu_cycles;

}

void unimplemented_instruction(uint8_t opcode){
  printf("Unimplemented instruction, opcode : %u\n", opcode);
  exit(1);
}

