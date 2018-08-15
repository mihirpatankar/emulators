#ifndef __CPU_8080_H__
#define __CPU_8080_H__

/*
 * Register Pairs were defined as a union to get access to each 
 * register separately as well as together conveniently
 */
typedef union {
    struct {
        uint8_t l;
        uint8_t h;
    } b;
    uint16_t w;
} register_pair;

/*
 * Status Flags defined as bitfields based on the 8080/8085 Assembly Language
 * Programmer's Manual Link:
 * http://www.nj7p.org/Manuals/PDFs/Intel/9800301D.pdf
 * Page: 3-45
 */
typedef struct {
    uint8_t carry_flag  :1;
    uint8_t undef_bit1  :1;
    uint8_t parity_flag :1;
    uint8_t undef_bit3  :1;
    uint8_t aux_carry   :1;
    uint8_t undef_bit5  :1;
    uint8_t zero_flag   :1;
    uint8_t sign_flag   :1;
} condition_reg;

/*
 * The 8080 can be defined by these attributes
 */
typedef struct {
    uint32_t cycle_count;
    register_pair psw, bc, de, hl;
    register_pair sp, pc;
    condition_reg c;
    uint8_t iff; //interrupt flip flop - for EI DI instructions    
} i8080;

#define FLAGS   cpu.c
#define PSW     cpu.psw.w
#define BC      cpu.bc.w
#define DE      cpu.de.w
#define HL      cpu.hl.w
#define SP      cpu.sp.w
#define PC      cpu.pc.w
#define A       cpu.psw.b.h
#define F       cpu.psw.b.l
#define B       cpu.bc.b.h
#define C       cpu.bc.b.l
#define D       cpu.de.b.h
#define E       cpu.de.b.l
#define H       cpu.hl.b.h
#define L       cpu.hl.b.l
#define HSP     cpu.sp.b.h
#define LSP     cpu.sp.b.l
#define HPC     cpu.pc.b.h
#define LPC     cpu.pc.b.l
#define IFF     cpu.iff
#define CYCLES  cpu.cycle_count

#define C_FLAG  FLAGS.carry_flag
#define UN1     FLAGS.undef_bit1
#define P_FLAG  FLAGS.parity_flag
#define UN3     FLAGS.undef_bit3
#define A_FLAG  FLAGS.aux_carry
#define UN5     FLAGS.undef_bit5
#define Z_FLAG  FLAGS.zero_flag
#define S_FLAG  FLAGS.sign_flag

/*
 * Opcode cycles
 */
static uint8_t opcode_cycles[] = {
    4,  10, 7,  5,  5,  5,  7,  4,  4,  10, 7,  5,  5,  5,  7,  4, 
    4,  10, 7,  5,  5,  5,  7,  4,  4,  10, 7,  5,  5,  5,  7,  4,  
    4,  10, 16, 5,  5,  5,  7,  4,  4,  10, 16, 5,  5,  5,  7,  4,  
    4,  10, 13, 5,  10, 10, 10, 4,  4,  10, 13, 5,  5,  5,  7,  4,  
    5,  5,  5,  5,  5,  5,  7,  5,  5,  5,  5,  5,  5,  5,  7,  5,  
    5,  5,  5,  5,  5,  5,  7,  5,  5,  5,  5,  5,  5,  5,  7,  5,  
    5,  5,  5,  5,  5,  5,  7,  5,  5,  5,  5,  5,  5,  5,  7,  5,  
    7,  7,  7,  7,  7,  7,  7,  7,  5,  5,  5,  5,  5,  5,  7,  5,  
    4,  4,  4,  4,  4,  4,  7,  4,  4,  4,  4,  4,  4,  4,  7,  4,  
    4,  4,  4,  4,  4,  4,  7,  4,  4,  4,  4,  4,  4,  4,  7,  4,  
    4,  4,  4,  4,  4,  4,  7,  4,  4,  4,  4,  4,  4,  4,  7,  4,  
    4,  4,  4,  4,  4,  4,  7,  4,  4,  4,  4,  4,  4,  4,  7,  4,  
    5,  10, 10, 10, 11, 11, 7,  11, 5,  10, 10, 10, 11, 11, 7,  11, 
    5,  10, 10, 10, 11, 11, 7,  11, 5,  10, 10, 10, 11, 11, 7,  11, 
    5,  10, 10, 18, 11, 11, 7,  11, 5,  5,  10, 5,  11, 11, 7,  11, 
    5,  10, 10, 4,  11, 11, 7,  11, 5,  5,  10, 4,  11, 11, 7,  11 
};


/*
 * Parity of all 8-bit values.
 * Having a static table is better than wasting cycles at run-time.
 */
static uint8_t parity[] = {
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  0-15    */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  16-31   */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  32-47   */
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  48-63   */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  64-79   */
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  80-95   */
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  96-111  */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  112-127 */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  128-143 */    
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  144-159 */
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  160-175 */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  176-191 */
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  192-207 */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  208-223 */
    0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, /*  224-239 */
    1, 0, 0, 1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 0, 1, /*  240-255 */
};

/* Aux Carry Truth table for addition
 *  |   Op1 |   Op2 |   Sum |   ACy | 
 *  |-------|-------|-------|-------|
 *  |   0   |   0   |   0   |   0   |
 *  |   0   |   0   |   1   |   0   |
 *  |   0   |   1   |   0   |   1   |
 *  |   0   |   1   |   1   |   0   |
 *  |   1   |   0   |   0   |   1   |
 *  |   1   |   0   |   1   |   0   |
 *  |   1   |   1   |   0   |   1   |
 *  |   1   |   1   |   1   |   1   |
 */
static uint8_t aux_carry_add[] = {0, 0, 1, 0, 1, 0, 1, 1};

/* Aux Carry Truth table for subtration
 *  |   Op1 |   Op2 |   Sum |   ACy | 
 *  |-------|-------|-------|-------|
 *  |   0   |   0   |   0   |   0   |
 *  |   0   |   0   |   1   |   1   |
 *  |   0   |   1   |   0   |   1   |
 *  |   0   |   1   |   1   |   1   |
 *  |   1   |   0   |   0   |   0   |
 *  |   1   |   0   |   1   |   0   |
 *  |   1   |   1   |   0   |   0   |
 *  |   1   |   1   |   1   |   1   |
 */
static uint8_t aux_carry_subtract[] = {0, 1, 1, 1, 0, 0, 0, 1};


/*
 * Working registers for temporary calculations
 */
static uint32_t temp32_reg = 0;
static uint16_t temp16_reg = 0; 
static uint8_t  temp8_reg = 0;
static uint8_t  temp_data_reg = 0;

/*
 * Need the following for DAA
 */
static uint8_t  ls_nibble, ms_nibble, temp_carry;

#define ADD(v, c)                                   \
    do {                                            \
        temp16_reg = (uint16_t) A + (v) + (c & C_FLAG);  \
        temp8_reg = ((A & 0x8) >> 1)                \
                    | ((v & 0x8) >> 2)              \
                    | ((temp16_reg & 0x8) >> 3);    \
        A = temp16_reg & 0xFF;                      \
        C_FLAG = ((temp16_reg & 0x100) >> 8);       \
        P_FLAG = parity[A];                         \
        A_FLAG = aux_carry_add[temp8_reg];          \
        Z_FLAG = (A == 0);                          \
        S_FLAG = ((A & 0x80) != 0);                 \
    } while(0)                                      \

#define SUB(v, c)                                   \
    do {                                            \
        temp16_reg = (uint16_t) A - (v) - (c & C_FLAG);  \
        temp8_reg = ((A & 0x8) >> 1)                \
                    | ((v & 0x8) >> 2)              \
                    | ((temp16_reg & 0x8) >> 3);    \
        A = temp16_reg & 0xFF;                      \
        C_FLAG = ((temp16_reg & 0x100) >> 8);       \
        P_FLAG = parity[A];                         \
        A_FLAG = !aux_carry_subtract[temp8_reg];    \
        Z_FLAG = (A == 0);                          \
        S_FLAG = ((A & 0x80) != 0);                 \
    } while(0)                                      \

#define INR(reg)                                    \
    do {                                            \
        ++(reg);                                    \
        P_FLAG = parity[reg];                       \
        A_FLAG = ((reg & 0xF) == 0x0);              \
        Z_FLAG = (reg == 0);                        \
        S_FLAG = ((reg & 0x80) != 0);               \
    } while(0)                                      \

#define DCR(reg)                                    \
    do {                                            \
        --(reg);                                    \
        P_FLAG = parity[reg];                       \
        A_FLAG = ((reg & 0xF) != 0xF);              \
        Z_FLAG = (reg == 0);                        \
        S_FLAG = ((reg & 0x80) != 0);               \
    } while(0)                                      \

#define DAD(rp)                                     \
    do {                                            \
        temp32_reg = (uint32_t)HL + (rp);           \
        HL = temp32_reg & 0xFFFF;                   \
        C_FLAG = ((temp32_reg &0x10000) >> 16);     \
    } while(0)

/*
 * Auxiliary carry is affected by AND operation in 8080.
 * It is the value of OR of the 3rd bit of the values being AND'ed
 */

#define ANA(v)                                      \
    do {                                            \
        A_FLAG = (((A | v) & 0x08) == 0);           \
        A &= v;                                     \
        C_FLAG = 0;                                 \
        P_FLAG = parity[A];                         \
        Z_FLAG = (A==0);                            \
        S_FLAG = ((A & 0x80) != 0);                 \
    } while(0)

#define XRA(v)                                      \
    do {                                            \
        A ^= v;                                     \
        C_FLAG = 0;                                 \
        P_FLAG = parity[A];                         \
        A_FLAG = 0;                                 \
        Z_FLAG = (A==0);                            \
        S_FLAG = ((A & 0x80) != 0);                 \
    } while(0)

#define ORA(v)                                      \
    do {                                            \
        A |= v;                                     \
        C_FLAG = 0;                                 \
        P_FLAG = parity[A];                         \
        A_FLAG = 0;                                 \
        Z_FLAG = (A==0);                            \
        S_FLAG = ((A & 0x80) != 0);                 \
    } while(0)

#define CMP(v)                                      \
    do {                                            \
        temp16_reg = (uint16_t) A - (v);            \
        temp8_reg = ((A & 0x8) >> 1)                \
                    | ((v & 0x8) >> 2)              \
                    | ((temp16_reg & 0x8) >> 3);    \
        C_FLAG = (A) < (v);                         \
        P_FLAG = parity[temp16_reg & 0xFF];         \
        A_FLAG = !aux_carry_subtract[temp8_reg];    \
        Z_FLAG = (A == v);                          \
        S_FLAG = ((temp16_reg & 0x80) != 0);        \
    } while(0)

/*
 * Initialize the CPU for operation. This involves setting the PC to the value
 * passed and presetting the bits of the status/condition register
 */
void i8080_init(uint16_t pc);

/*
 * Runs the opcode at PC and increments PC
 * Returns the cycles taken in this instruction
 * 
 * Note: Total cycle count is updated directly. 
 *       DO NOT USE the returned value for updating CYCLES
 */
int i8080_run_insn(void);


#endif
