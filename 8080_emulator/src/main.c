#include <stdio.h>
#include <stdlib.h>
#include <cpu.h>
#include <hal.h>

int main(int argc, char** argv) {
    printf("Initializing...\n");
    i8080_init(0x00);
    printf("Initialized\n");
    return 0;
}
