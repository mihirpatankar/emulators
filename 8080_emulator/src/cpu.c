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
