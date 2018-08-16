#include <stdio.h>
#include <stdlib.h>
#include <cpu.h>
#include <hal.h>

i8080 test_cpu;

int main(int argc, char** argv) {
    printf("Initializing...\n");
    i8080_init(0x00);
    int size = sizeof(test_cpu.c);
    printf("Initialized %d\n",size);
    return 0;
}
