#include "disassembler.h"

uint8_t disassemble_opcode(uint8_t* code_buffer, uint16_t pc){
  uint8_t opcode_bytes = 1;
  uint8_t* opcode = &code_buffer[pc];
  
  switch(*opcode){
    case 0x00: printf("NOP"); break;
    case 0x01: printf("LXI    B,#$%02x%02x", opcode[2], opcode[1]); opcode_bytes=3; break;
    case 0x02: printf("STAX   B"); break;
    case 0x03: printf("INX    B"); break;
    case 0x04: printf("INR    B"); break;
    case 0x05: printf("DCR    B"); break;
    case 0x06: printf("MVI    B,#$%02x", opcode[1]); opcode_bytes=2; break;
    case 0x07: printf("RLC"); break;
    case 0x08: printf("NOP"); break;
    case 0x09: printf("DAD    B"); break;
    case 0x0a: printf("LDAX   B"); break;
    case 0x0b: printf("DCX    B"); break;
    case 0x0c: printf("INR    C"); break;
    case 0x0d: printf("DCR    C"); break;
    case 0x0e: printf("MVI    C,#$%02x", opcode[1]); opcode_bytes = 2;	break;
    case 0x0f: printf("RRC"); break;

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
    case 0xc2: printf("JNZ    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xc3: printf("JMP    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xc4: printf("CNZ    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xc5: printf("PUSH   B"); break;
    case 0xc6: printf("ADI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xc7: printf("RST    0"); break;
    case 0xc8: printf("RZ"); break;
    case 0xc9: printf("RET"); break;
    case 0xca: printf("JZ     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xcb: printf("JMP    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xcc: printf("CZ     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xcd: printf("CALL   $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xce: printf("ACI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xcf: printf("RST    1"); break;

    case 0xd0: printf("RNC"); break;
    case 0xd1: printf("POP    D"); break;
    case 0xd2: printf("JNC    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xd3: printf("OUT    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xd4: printf("CNC    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xd5: printf("PUSH   D"); break;
    case 0xd6: printf("SUI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xd7: printf("RST    2"); break;
    case 0xd8: printf("RC");  break;
    case 0xd9: printf("RET"); break;
    case 0xda: printf("JC     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xdb: printf("IN     #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xdc: printf("CC     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xdd: printf("CALL   $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xde: printf("SBI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xdf: printf("RST    3"); break;

    case 0xe0: printf("RPO"); break;
    case 0xe1: printf("POP    H"); break;
    case 0xe2: printf("JPO    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xe3: printf("XTHL");break;
    case 0xe4: printf("CPO    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xe5: printf("PUSH   H"); break;
    case 0xe6: printf("ANI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xe7: printf("RST    4"); break;
    case 0xe8: printf("RPE"); break;
    case 0xe9: printf("PCHL");break;
    case 0xea: printf("JPE    $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xeb: printf("XCHG"); break;
    case 0xec: printf("CPE     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xed: printf("CALL   $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xee: printf("XRI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xef: printf("RST    5"); break;

    case 0xf0: printf("RP");  break;
    case 0xf1: printf("POP    PSW"); break;
    case 0xf2: printf("JP     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xf3: printf("DI");  break;
    case 0xf4: printf("CP     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xf5: printf("PUSH   PSW"); break;
    case 0xf6: printf("ORI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xf7: printf("RST    6"); break;
    case 0xf8: printf("RM");  break;
    case 0xf9: printf("SPHL");break;
    case 0xfa: printf("JM     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xfb: printf("EI");  break;
    case 0xfc: printf("CM     $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xfd: printf("CALL   $%02x%02x",opcode[2],opcode[1]); opcode_bytes = 3; break;
    case 0xfe: printf("CPI    #$%02x",opcode[1]); opcode_bytes = 2; break;
    case 0xff: printf("RST    7"); break;
  }

  return opcode_bytes;
}

void emulate_instruction(struct cpu_state* state){
    

    uint8_t* opcode = &state->memory[state->registers.PC];
    uint8_t opcode_bytes = disassemble_opcode(state->memory, state->registers.PC);
    
    switch(*opcode){
      //NOP
      case 0x00: break;
      case 0x01: state->registers.C = opcode[1];
        state->registers.B = opcode[2];
        break;
      case 0x02: set_data_pointed_by(state, state->registers.B,
          state->registers.C, state->registers.A); break;
      case 0x03:
        {
          uint16_t data = append_registers(state->registers.B, state->registers.C);
          assign_data_to_registers(&state->registers.B, &state->registers.C, (data+1));
          break;
        }
      case 0x04: unimplemented_instruction(state); break;
      case 0x05: unimplemented_instruction(state); break;
      case 0x06: state->registers.B = opcode[1];
        break;
      case 0x07: unimplemented_instruction(state); break;
      case 0x08: unimplemented_instruction(state); break;
      case 0x09: unimplemented_instruction(state); break;
      case 0x0a: unimplemented_instruction(state); break;
      case 0x0b: unimplemented_instruction(state); break;
      case 0x0c: unimplemented_instruction(state); break;
      case 0x0d: unimplemented_instruction(state); break;
      case 0x0e: state->registers.C = opcode[1];
        break;
      case 0x0f: unimplemented_instruction(state); break;
      case 0x10: unimplemented_instruction(state); break;
      case 0x11: state->registers.E = opcode[1];
        state->registers.D = opcode[2];
        break;
      case 0x12: set_data_pointed_by(state, state->registers.D,
          state->registers.E, state->registers.A); break;
      case 0x13: state->registers.E++;
        if (state->registers.E == 0){
          state->registers.D++;
        }
        break;
      case 0x14: unimplemented_instruction(state); break;
      case 0x15: unimplemented_instruction(state); break;
      case 0x16: unimplemented_instruction(state); break;
      case 0x17: unimplemented_instruction(state); break;
      case 0x18: unimplemented_instruction(state); break;
      case 0x19: unimplemented_instruction(state); break;
      case 0x1a: unimplemented_instruction(state); break;
      case 0x1b: unimplemented_instruction(state); break;
      case 0x1c: unimplemented_instruction(state); break;
      case 0x1d: unimplemented_instruction(state); break;
      case 0x1e: unimplemented_instruction(state); break;
      case 0x1f: unimplemented_instruction(state); break;

      case 0x20: unimplemented_instruction(state); break;
      case 0x21: state->registers.L = opcode[1];
        state->registers.H = opcode[2];
        break;
      case 0x22: unimplemented_instruction(state); break;
      case 0x23: state->registers.L++;
        if (state->registers.L == 0){
          state->registers.H++;
        }
        break;
      case 0x24: unimplemented_instruction(state); break;
      case 0x25: unimplemented_instruction(state); break;
      case 0x26: state->registers.H = opcode[1];
        break;
      case 0x27: unimplemented_instruction(state); break;
      case 0x28: unimplemented_instruction(state); break;
      case 0x29: unimplemented_instruction(state); break;
      case 0x2a: unimplemented_instruction(state); break;
      case 0x2b: unimplemented_instruction(state); break;
      case 0x2c: unimplemented_instruction(state); break;
      case 0x2d: unimplemented_instruction(state); break;
      case 0x2e: unimplemented_instruction(state); break;
      case 0x2f: unimplemented_instruction(state); break;
      case 0x30: unimplemented_instruction(state); break;
      case 0x31: state->registers.SP = append_registers(opcode[2], opcode[1]);
        break;
      case 0x32:
        {
          uint16_t address = append_registers(opcode[2], opcode[1]);
          state->memory[address] = state->registers.A;
          break;
        }
      case 0x33: unimplemented_instruction(state); break;
      case 0x34: unimplemented_instruction(state); break;
      case 0x35: unimplemented_instruction(state); break;
      case 0x36:
        {
          uint16_t address = append_registers(state->registers.H, state->registers.L);
          state->memory[address] = opcode[1];
          break;
        }
      case 0x37: unimplemented_instruction(state); break;
      case 0x38: unimplemented_instruction(state); break;
      case 0x39: unimplemented_instruction(state); break;
      case 0x3a:
        {
          uint16_t address = append_registers(opcode[2], opcode[1]);
          state->registers.A = state->memory[address];
          break;
        }
      case 0x3b: unimplemented_instruction(state); break;
      case 0x3c: unimplemented_instruction(state); break;
      case 0x3d: unimplemented_instruction(state); break;
      case 0x3e: state->registers.A = opcode[1];
        break;
      case 0x3f: unimplemented_instruction(state); break;
      //Data transfer instructions
      case 0x40: unimplemented_instruction(state); break;
      case 0x41: state->registers.B = state->registers.C; break;
      case 0x42: state->registers.B = state->registers.D; break;
      case 0x43: state->registers.B = state->registers.E; break;
      case 0x44: state->registers.B = state->registers.H; break;
      case 0x45: state->registers.B = state->registers.L; break;
      case 0x46: state->registers.B =
        get_data_pointed_by(state, state->registers.H, state->registers.L);
        break;
      case 0x47: state->registers.B = state->registers.A; break;
      case 0x48: state->registers.C = state->registers.B; break;
      case 0x49: unimplemented_instruction(state); break;
      case 0x4a: state->registers.C = state->registers.D; break;
      case 0x4b: state->registers.C = state->registers.E; break;
      case 0x4c: state->registers.C = state->registers.H; break;
      case 0x4d: state->registers.C = state->registers.L; break;
      case 0x4e: state->registers.C =
        get_data_pointed_by(state, state->registers.H, state->registers.L);
        break;
      case 0x4f: state->registers.C = state->registers.A; break;
      case 0x50: state->registers.D = state->registers.B; break;
      case 0x51: state->registers.D = state->registers.C; break;
      case 0x52: unimplemented_instruction(state); break;
      case 0x53: state->registers.D = state->registers.E; break;
      case 0x54: state->registers.D = state->registers.H; break;
      case 0x55: state->registers.D = state->registers.L; break;
      case 0x56: state->registers.D =
          get_data_pointed_by(state, state->registers.H, state->registers.L);
          break;
      case 0x57: state->registers.D = state->registers.A; break;
      case 0x58: state->registers.E = state->registers.B; break;
      case 0x59: state->registers.E = state->registers.C; break;
      case 0x5a: state->registers.E = state->registers.D; break;
      case 0x5b: unimplemented_instruction(state); break;
      case 0x5c: state->registers.E = state->registers.H; break;
      case 0x5d: state->registers.E = state->registers.L; break;
      case 0x5e: state->registers.E =
          get_data_pointed_by(state, state->registers.H, state->registers.L);
          break;
      case 0x5f: state->registers.E = state->registers.A; break;
      case 0x60: state->registers.H = state->registers.B; break;
      case 0x61: state->registers.H = state->registers.C; break;
      case 0x62: state->registers.H = state->registers.D; break;
      case 0x63: state->registers.H = state->registers.E; break;
      case 0x64: unimplemented_instruction(state); break;
      case 0x65: state->registers.H = state->registers.L; break;
      case 0x66: state->registers.H =
          get_data_pointed_by(state, state->registers.H, state->registers.L);
          break;
      case 0x67: state->registers.H = state->registers.A; break;
      case 0x68: state->registers.L = state->registers.B; break;
      case 0x69: state->registers.L = state->registers.C; break;
      case 0x6a: state->registers.L = state->registers.D; break;
      case 0x6b: state->registers.L = state->registers.E; break;
      case 0x6c: state->registers.L = state->registers.H; break;
      case 0x6d: unimplemented_instruction(state); break;
      case 0x6e: state->registers.L =
          get_data_pointed_by(state, state->registers.H, state->registers.L);
          break;
      case 0x6f: state->registers.L = state->registers.A; break;
      case 0x70: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.B);
        break;
      case 0x71: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.C);
        break;
      case 0x72: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.D);
        break;
      case 0x73: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.E);
        break;
      case 0x74: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.H);
        break;
      case 0x75: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.L);
        break;
      case 0x76: unimplemented_instruction(state); break;
      case 0x77: set_data_pointed_by(state, state->registers.H, state->registers.L,
          state->registers.A);
        break;
      case 0x78: state->registers.A = state->registers.B; break;
      case 0x79: state->registers.A = state->registers.C; break;
      case 0x7a: state->registers.A = state->registers.D;  break;
      case 0x7b: state->registers.A = state->registers.E;  break;
      case 0x7c: state->registers.A = state->registers.H; break;
      case 0x7d: state->registers.A = state->registers.L; break;
      case 0x7e: state->registers.A =
          get_data_pointed_by(state, state->registers.H, state->registers.L);
          break;
      case 0x7f: unimplemented_instruction(state); break;
    }

    state->registers.PC += opcode_bytes;
}

void unimplemented_instruction(struct cpu_state* state){
  printf("Unimplemented instruction\n");
  uint8_t opcode_bytes = disassemble_opcode(state->memory, state->registers.PC);
  printf("Opcode bytes in the instruction : %u\n", opcode_bytes);
  exit(1);
}

uint8_t get_data_pointed_by(struct cpu_state* state, uint8_t register_high, uint8_t register_low){
  uint16_t address = append_registers(register_high, register_low);
  return state->memory[address];
}

void set_data_pointed_by(struct cpu_state* state, uint8_t register_high, uint8_t register_low, uint8_t data){
  uint16_t address = append_registers(register_high, register_low);
  state->memory[address] = data;
}
