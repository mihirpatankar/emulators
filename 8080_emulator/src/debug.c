#include <debug.h>

void debug_print_regs(void) {
    printf("Cycles: %u PC:0x%04x A:0x%02x B:0x%02x C:0x%02x D:0x%02x E:0x%02x H:0x%02x L:0x%02x SP:0x%04x Flag:0x%02x IFF:0x%02x\n", CYCLES, PC, A, B, C, D, E, H, L, F_REG, IFF);
}

void print_memory(void) {
    uint32_t i = 0;
    for(i = 0; i < 0x10000; i += 0x10) {
        printf("%d: %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d\n", i, memory[i], memory[i+1], memory[i+2], memory[i+3], memory[i+4], memory[i+5], memory[i+6], memory[i+7], memory[i+8], memory[i+9], memory[i+10], memory[i+11], memory[i+12], memory[i+13], memory[i+14], memory[i+15]);
    }
}
