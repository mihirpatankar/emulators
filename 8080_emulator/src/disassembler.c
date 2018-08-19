#include "disassembler.h"
#include "cpu.h"
#include "memory.h"


uint8_t get_opcode_bytes(uint8_t opcode){
  uint8_t opcode_bytes = 0;
  //sanity check
  if(opcode < OPCODE_MIN || opcode > OPCODE_MAX){
    printf("Error opcode : %u",opcode);
    return opcode_bytes;
  }
  switch(opcode){
    case 0x01: opcode_bytes=3; break;
    case 0x06: opcode_bytes=2; break;
    case 0x0e: opcode_bytes = 2;  break;
    case 0x11: opcode_bytes=3; break;
    case 0x16: opcode_bytes=2; break;
    case 0x1e: opcode_bytes = 2; break;
    case 0x21: opcode_bytes=3; break;
    case 0x22: opcode_bytes=3; break;
    case 0x26: opcode_bytes=2; break;
    case 0x2a: opcode_bytes=3; break;
    case 0x2e: opcode_bytes = 2; break;
    case 0x31: opcode_bytes=3; break;
    case 0x32: opcode_bytes=3; break;
    case 0x36: opcode_bytes=2; break;
    case 0x3a: opcode_bytes=3; break;
    case 0x3e: opcode_bytes = 2; break;
    case 0xc2: opcode_bytes = 3; break;
    case 0xc3: opcode_bytes = 3; break;
    case 0xc4: opcode_bytes = 3; break;
    case 0xc6: opcode_bytes = 2; break;
    case 0xca: opcode_bytes = 3; break;
    case 0xcb: opcode_bytes = 3; break;
    case 0xcc: opcode_bytes = 3; break;
    case 0xcd: opcode_bytes = 3; break;
    case 0xce: opcode_bytes = 2; break;
    case 0xd2: opcode_bytes = 3; break;
    case 0xd3: opcode_bytes = 2; break;
    case 0xd4: opcode_bytes = 3; break;
    case 0xd6: opcode_bytes = 2; break;
    case 0xda: opcode_bytes = 3; break;
    case 0xdb: opcode_bytes = 2; break;
    case 0xdc: opcode_bytes = 3; break;
    case 0xdd: opcode_bytes = 3; break;
    case 0xde: opcode_bytes = 2; break;
    case 0xe2: opcode_bytes = 3; break;
    case 0xe4: opcode_bytes = 3; break;
    case 0xe6: opcode_bytes = 2; break;
    case 0xea: opcode_bytes = 3; break;
    case 0xec: opcode_bytes = 3; break;
    case 0xed: opcode_bytes = 3; break;
    case 0xee: opcode_bytes = 2; break;
    case 0xf2: opcode_bytes = 3; break;
    case 0xf4: opcode_bytes = 3; break;
    case 0xf6: opcode_bytes = 2; break;
    case 0xfa: opcode_bytes = 3; break;
    case 0xfc: opcode_bytes = 3; break;
    case 0xfd: opcode_bytes = 3; break;
    case 0xfe: opcode_bytes = 2; break;
    default : opcode_bytes = 1;
  }
  return opcode_bytes;
}


uint8_t emulate_instruction(uint8_t opcode){
    
  uint8_t cpu_cycles=-1;
  bool update_PC = true;

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
        increment(&B);
        break;

    case 0x05:            /* dcr b */
        cpu_cycles = 5;
        decrement(&B);
        break;

    case 0x06:            /* mvi b, data8 */
        cpu_cycles = 7;
        B = RD_BYTE(PC+1);
        break;

    case 0x07:            /* rlc */
        cpu_cycles = 4;
        CY = (A & BIT_7_MASK) != 0;
        A = (A << 1) | CY;
        break;

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
        increment(&C);
        break;

    case 0x0D:            /* dcr c */
        cpu_cycles = 5;
        decrement(&C);
        break;

    case 0x0E:            /* mvi c, data8 */
        cpu_cycles = 7;
        C = RD_BYTE(PC+1);
        break;

    case 0x0F:            /* rrc */
        cpu_cycles = 4;
        CY = A & BIT_1_MASK;
        A = (A >> 1) | (CY << 7);
        break;

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
        increment(&D);
        break;

    case 0x15:            /* dcr d */
        cpu_cycles = 5;
        decrement(&D);
        break;

    case 0x16:            /* mvi d, data8 */
        cpu_cycles = 7;
        D = RD_BYTE(PC+1);
        break;

    case 0x17:            /* ral */
        cpu_cycles = 4;
        data8 = CY;
        CY = (A & BIT_7_MASK) != 0;
        A = (A << 1) | data8;
        break;

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
        increment(&E);
        break;

    case 0x1D:            /* dcr e */
        cpu_cycles = 5;
        decrement(&E);
        break;

    case 0x1E:            /* mvi e, data8 */
        cpu_cycles = 7;
        E = RD_BYTE(PC+1);
        break;

    case 0x1F:             /* rar */
        cpu_cycles = 4;
        data8 = CY;
        CY = A & BIT_1_MASK;
        A = (A >> 1) | (data8 << 7);
        break;

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
        increment(&H);
        break;

    case 0x25:            /* dcr h */
        cpu_cycles = 5;
        decrement(&H);
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
        increment(&L);
        break;

    case 0x2D:            /* dcr l */
        cpu_cycles = 5;
        decrement(&L);
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

    case 0x34:            /* inr m */
        cpu_cycles = 10;
        data8 = RD_BYTE(HL);
        increment(&data8);
        WR_BYTE(HL, data8);
        break;

    case 0x35:            /* dcr m */
        cpu_cycles = 10;
        data8 = RD_BYTE(HL);
        decrement(&data8);
        WR_BYTE(HL, data8);
        break;

    case 0x36:            /* mvi m, data8 */
        cpu_cycles = 10;
        WR_BYTE(HL, RD_BYTE(PC+1));
        break;

    case 0x37:            /* stc */
        cpu_cycles = 4;
        SET(CY);
        break;

//    case 0x39:            /* dad sp */
//        cpu_cycles = 10;
//        DAD(SP);
//        break;

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
        increment(&A);
        break;

    case 0x3D:            /* dcr a */
        cpu_cycles = 5;
        decrement(&A);
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

    case 0x80:            /* add b */
        cpu_cycles = 4;
        add(B);
        break;

    case 0x81:            /* add c */
        cpu_cycles = 4;
        add(C);
        break;

    case 0x82:            /* add d */
        cpu_cycles = 4;
        add(D);
        break;

    case 0x83:            /* add e */
        cpu_cycles = 4;
        add(E);
        break;

    case 0x84:            /* add h */
        cpu_cycles = 4;
        add(H);
        break;

    case 0x85:            /* add l */
        cpu_cycles = 4;
        add(L);
        break;

    case 0x86:            /* add m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        add(data8);
        break;

    case 0x87:            /* add a */
        cpu_cycles = 4;
        add(A);
        break;

    case 0x88:            /* adc b */
        cpu_cycles = 4;
        add_with_carry(B);
        break;

    case 0x89:            /* adc c */
        cpu_cycles = 4;
        add_with_carry(C);
        break;

    case 0x8A:            /* adc d */
        cpu_cycles = 4;
        add_with_carry(D);
        break;

    case 0x8B:            /* adc e */
        cpu_cycles = 4;
        add_with_carry(E);
        break;

    case 0x8C:            /* adc h */
        cpu_cycles = 4;
        add_with_carry(H);
        break;

    case 0x8D:            /* adc l */
        cpu_cycles = 4;
        add_with_carry(L);
        break;

    case 0x8E:            /* adc m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        add_with_carry(data8);
        break;

    case 0x8F:            /* adc a */
        cpu_cycles = 4;
        add_with_carry(A);
        break;

    case 0x90:            /* sub b */
        cpu_cycles = 4;
        subtract(B);
        break;

    case 0x91:            /* sub c */
        cpu_cycles = 4;
        subtract(C);
        break;

    case 0x92:            /* sub d */
        cpu_cycles = 4;
        subtract(D);
        break;

    case 0x93:            /* sub e */
        cpu_cycles = 4;
        subtract(E);
        break;

    case 0x94:            /* sub h */
        cpu_cycles = 4;
        subtract(H);
        break;

    case 0x95:            /* sub l */
        cpu_cycles = 4;
        subtract(L);
        break;

    case 0x96:            /* sub m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        subtract(data8);
        break;

    case 0x97:            /* sub a */
        cpu_cycles = 4;
        subtract(A);
        break;

    case 0x98:            /* sbb b */
        cpu_cycles = 4;
        subtract_with_borrow(B);
        break;

    case 0x99:            /* sbb c */
        cpu_cycles = 4;
        subtract_with_borrow(C);
        break;

    case 0x9A:            /* sbb d */
        cpu_cycles = 4;
        subtract_with_borrow(D);
        break;

    case 0x9B:            /* sbb e */
        cpu_cycles = 4;
        subtract_with_borrow(E);
        break;

    case 0x9C:            /* sbb h */
        cpu_cycles = 4;
        subtract_with_borrow(H);
        break;

    case 0x9D:            /* sbb l */
        cpu_cycles = 4;
        subtract_with_borrow(L);
        break;

    case 0x9E:            /* sbb m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        subtract_with_borrow(data8);
        break;

    case 0x9F:            /* sbb a */
        cpu_cycles = 4;
        subtract_with_borrow(A);
        break;

    case 0xA0:            /* ana b */
        cpu_cycles = 4;
        logical_and(B);
        break;

    case 0xA1:            /* ana c */
        cpu_cycles = 4;
        logical_and(C);
        break;

    case 0xA2:            /* ana d */
        cpu_cycles = 4;
        logical_and(D);
        break;

    case 0xA3:            /* ana e */
        cpu_cycles = 4;
        logical_and(E);
        break;

    case 0xA4:            /* ana h */
        cpu_cycles = 4;
        logical_and(H);
        break;

    case 0xA5:            /* ana l */
        cpu_cycles = 4;
        logical_and(L);
        break;

    case 0xA6:            /* ana m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        logical_and(data8);
        break;

    case 0xA7:            /* ana a */
        cpu_cycles = 4;
        logical_and(A);
        break;

    case 0xA8:            /* xra b */
        cpu_cycles = 4;
        logical_xor(B);
        break;

    case 0xA9:            /* xra c */
        cpu_cycles = 4;
        logical_xor(C);
        break;

    case 0xAA:            /* xra d */
        cpu_cycles = 4;
        logical_xor(D);
        break;

    case 0xAB:            /* xra e */
        cpu_cycles = 4;
        logical_xor(E);
        break;

    case 0xAC:            /* xra h */
        cpu_cycles = 4;
        logical_xor(H);
        break;

    case 0xAD:            /* xra l */
        cpu_cycles = 4;
        logical_xor(L);
        break;

    case 0xAE:            /* xra m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        logical_xor(data8);
        break;

    case 0xAF:            /* xra a */
        cpu_cycles = 4;
        logical_xor(A);
        break;

    case 0xB0:            /* ora b */
        cpu_cycles = 4;
        logical_or(B);
        break;

    case 0xB1:            /* ora c */
        cpu_cycles = 4;
        logical_or(C);
        break;

    case 0xB2:            /* ora d */
        cpu_cycles = 4;
        logical_or(D);
        break;

    case 0xB3:            /* ora e */
        cpu_cycles = 4;
        logical_or(E);
        break;

    case 0xB4:            /* ora h */
        cpu_cycles = 4;
        logical_or(H);
        break;

    case 0xB5:            /* ora l */
        cpu_cycles = 4;
        logical_or(L);
        break;

    case 0xB6:            /* ora m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        logical_or(data8);
        break;

    case 0xB7:            /* ora a */
        cpu_cycles = 4;
        logical_or(A);
        break;

    case 0xB8:            /* cmp b */
        cpu_cycles = 4;
        compare(B);
        break;

    case 0xB9:            /* cmp c */
        cpu_cycles = 4;
        compare(C);
        break;

    case 0xBA:            /* cmp d */
        cpu_cycles = 4;
        compare(D);
        break;

    case 0xBB:            /* cmp e */
        cpu_cycles = 4;
        compare(E);
        break;

    case 0xBC:            /* cmp h */
        cpu_cycles = 4;
        compare(H);
        break;

    case 0xBD:            /* cmp l */
        cpu_cycles = 4;
        compare(L);
        break;

    case 0xBE:            /* cmp m */
        cpu_cycles = 7;
        data8 = RD_BYTE(HL);
        compare(data8);
        break;

    case 0xBF:            /* cmp a */
        cpu_cycles = 4;
        compare(A);
        break;

    case 0xC0:            /* rnz */
        cpu_cycles = 5;
        if (!Z) {
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xC1:            /* pop b */
        cpu_cycles = 11;
        pop(&BC);
        break;

    case 0xC2:            /* jnz addr */
        cpu_cycles = 10;
        if (!Z){
            PC = RD_WORD(PC+1);
            update_PC = false;
        }
        break;

    case 0xC3:            /* jmp addr */
    case 0xCB:            /* jmp addr, undocumented */
        cpu_cycles = 10;
        PC = RD_WORD(PC+1);
        update_PC = false;
        break;

    case 0xC4:            /* cnz addr */
        cpu_cycles = 11;
        if(!Z){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xC5:            /* push b */
        cpu_cycles = 11;
        push(BC);
        break;

    case 0xC6:            /* adi data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        add(data8);
        break;

    case 0xC7:            /* rst 0 */
        cpu_cycles = 11;
        reset(0x0000);
        update_PC = false;
        break;

    case 0xC8:            /* rz */
        cpu_cycles = 5;
        if(Z){
            cpu_cycles = 11;
            pop(&PC);
            update_PC=false;
            return cpu_cycles;
        }
        break;

    case 0xC9:            /* ret */
    case 0xD9:            /* ret, undocumented */
        cpu_cycles = 10;
        pop(&PC);
        update_PC = false;
        break;

    case 0xCA:            /* jz addr */
        cpu_cycles = 10;
        if (Z) {
            PC = RD_WORD(PC);
            update_PC = false;
        }
        break;

    case 0xCC:            /* cz addr */
        cpu_cycles = 11;
        if(Z){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xCD:            /* call addr */
    case 0xDD:            /* call, undocumented */
    case 0xED:
    case 0xFD:
        cpu_cycles = 17;
        call();
        update_PC = false;
        break;

    case 0xCE:            /* aci data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        add_with_carry(data8);
        break;

    case 0xCF:            /* rst 1 */
        cpu_cycles = 11;
        reset(0x0008);
        update_PC = false;
        break;

    case 0xD0:            /* rnc */
        cpu_cycles = 5;
        if (!CY) {
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xD1:            /* pop d */
        cpu_cycles = 11;
        pop(&DE);
        break;

    case 0xD2:            /* jnc addr */
        cpu_cycles = 10;
        if (!CY) {
            PC = RD_WORD(PC+1);
            update_PC = false;
        }
        break;

//    case 0xD3:            /* out port8 */
//        cpu_cycles = 10;
//        i8080_hal_io_output(RD_BYTE(PC++), A);
//        break;

    case 0xD4:            /* cnc addr */
        cpu_cycles = 11;
        if (!CY) {
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xD5:            /* push d */
        cpu_cycles = 11;
        push(DE);
        break;

    case 0xD6:            /* sui data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        subtract(data8);
        break;

    case 0xD7:            /* rst 2 */
        cpu_cycles = 11;
        reset(0x0010);
        update_PC = false;
        break;

    case 0xD8:            /* rc */
        cpu_cycles = 5;
        if(CY){
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xDA:            /* jc addr */
        cpu_cycles = 10;
        if(CY){
            PC = RD_WORD(PC+1);
            update_PC = false;
        }
        break;

//    case 0xDB:            /* in port8 */
//        cpu_cycles = 10;
//        A = i8080_hal_io_input(RD_BYTE(PC++));
//        break;

    case 0xDC:            /* cc addr */
        cpu_cycles = 11;
        if(CY){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xDE:            /* sbi data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        subtract_with_borrow(data8);
        break;

    case 0xDF:            /* rst 3 */
        cpu_cycles = 11;
        reset(0x0018);
        update_PC = false;
        break;

    case 0xE0:            /* rpo */
        cpu_cycles = 5;
        if (!P) {
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xE1:            /* pop h */
        cpu_cycles = 11;
        pop(&HL);
        break;

    case 0xE2:            /* jpo addr */
        cpu_cycles = 10;
        if (!P) {
            PC = RD_WORD(PC+1);
            update_PC = false;
        }
        break;

    case 0xE3:            /* xthl */
        cpu_cycles = 18;
        data16 = RD_WORD(SP);
        WR_WORD(SP, HL);
        HL = data16;
        break;

    case 0xE4:            /* cpo addr */
        cpu_cycles = 11;
        if(!P){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xE5:            /* push h */
        cpu_cycles = 11;
        push(HL);
        break;

    case 0xE6:            /* ani data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        logical_and(data8);
        break;

    case 0xE7:            /* rst 4 */
        cpu_cycles = 11;
        reset(0x0020);
        update_PC = false;
        break;

    case 0xE8:            /* rpe */
        cpu_cycles = 5;
        if(P){
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xE9:            /* pchl */
        cpu_cycles = 5;
        PC = HL;
        break;

    case 0xEA:            /* jpe addr */
        cpu_cycles = 10;
        if(P){
            PC = RD_WORD(PC);
            update_PC = false;
        }
        break;

    case 0xEB:            /* xchg */
        cpu_cycles = 4;
        data16 = DE;
        DE = HL;
        HL = data16;
        break;

    case 0xEC:            /* cpe addr */
        cpu_cycles = 11;
        if(P){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xEE:            /* xri data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        logical_xor(data8);
        break;

    case 0xEF:            /* rst 5 */
        cpu_cycles = 11;
        reset(0x0028);
        update_PC = false;
        break;

    case 0xF0:            /* rp */
        cpu_cycles = 5;
        if(!S){
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xF1:            /* pop psw */
        cpu_cycles = 10;
        pop(&AF);
        get_flags();
        break;

    case 0xF2:            /* jp addr */
        cpu_cycles = 10;
        if(!S){
            PC = RD_WORD(PC);
            update_PC = false;
        }
        break;

    case 0xF3:            /* di */
        cpu_cycles = 4;
        IFF = 0;
        handle_iff(IFF);
        break;

    case 0xF4:            /* cp addr */
        cpu_cycles = 11;
        if(!S){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xF5:            /* push psw */
        cpu_cycles = 11;
        store_flags();
        push(AF);
        break;

    case 0xF6:            /* ori data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        logical_or(data8);
        break;

    case 0xF7:            /* rst 6 */
        cpu_cycles = 11;
        reset(0x0030);
        update_PC = false;
        break;

    case 0xF8:            /* rm */
        cpu_cycles = 5;
        if(S){
            cpu_cycles = 11;
            pop(&PC);
            update_PC = false;
        }
        break;

    case 0xF9:            /* sphl */
        cpu_cycles = 5;
        SP = HL;
        break;

    case 0xFA:            /* jm addr */
        cpu_cycles = 10;
        if(S){
            PC = RD_WORD(PC);
            update_PC = false;
        }
        break;

    case 0xFB:            /* ei */
        cpu_cycles = 4;
        IFF = 1;
        handle_iff(IFF);
        break;

    case 0xFC:            /* cm addr */
        cpu_cycles = 11;
        if(S){
            cpu_cycles = 17;
            call();
            update_PC = false;
        }
        break;

    case 0xFE:            /* cpi data8 */
        cpu_cycles = 7;
        data8 = RD_BYTE(PC+1);
        compare(data8);
        break;

    case 0xFF:            /* rst 7 */
        cpu_cycles = 11;
        reset(0x0038);
        update_PC = false;
        break;

    default : break;

  }
  if(update_PC){
    PC += get_opcode_bytes(opcode);
  }

  return cpu_cycles;
}

void unimplemented_instruction(uint8_t opcode){
  printf("Unimplemented instruction, opcode : %u\n", opcode);
  exit(1);
}


