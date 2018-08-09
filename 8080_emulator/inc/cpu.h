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

#define C_FLAG  FLAGS.carry_flag
#define UN1     FLAGS.undef_bit1
#define P_FLAG  FLAGS.parity_flag
#define UN3     FLAGS.undef_bit3
#define A_FLAG  FLAGS.aux_carry
#define UN5     FLAGS.undef_bit5
#define Z_FLAG  FLAGS.zero_flag
#define S_FLAG  FLAGS.sign_flag

/*
 * Initialize the CPU for operation. This involves setting the PC to the value
 * passed and presetting the bits of the status/condition register
 */
void i8080_init(uint16_t pc);



#endif
