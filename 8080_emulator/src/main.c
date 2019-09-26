#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "errors.h"
#include "cpu.h"
#include "hal.h"

#define TESTS 4

char *test_files[] = { "./cpu_tests/CPUTEST.COM", "./cpu_tests/TST8080.COM",
                    "./cpu_tests/8080PRE.COM", "./cpu_tests/8080EXM.COM" };

int copy_to_memory(int i, char *load_addr){
    FILE *fp = fopen(test_files[i], "r+b");
    int bytes_read = 0, total = 0;
    if(fp == NULL) {
        printf("fopen error\n");
        return FOPEN_FAILURE;
    } 
    
    while(!feof(fp)) {
        bytes_read = fread((void *) load_addr, 1, 0x400, fp);
        if(bytes_read < 0) return FREAD_FAILURE;
        else if (bytes_read == 0) break;
        load_addr += bytes_read; 
        total += bytes_read;  
    }
    printf("\n***********%d bytes copy successful*************\n", total);
    return SUCCESS;
}

/*
 * Routine to run 1 test
 */
int run_test(int i) {
    uint8_t *mem_start_ptr = memory_init();
    int ret = FAILURE;
    if(copy_to_memory(i, mem_start_ptr + 0x100) != 0) {
        return COPY_FAILURE;
    }
    

    mem_start_ptr[5] = 0xC9;
    i8080_init(0x100);
    
    while(1) {
        uint16_t prog_counter = i8080_get_current_PC();
        if(mem_start_ptr[prog_counter] == 0x76) {
            printf("Program counter(0x%04x) reached HLT\n", prog_counter);
            return HALT_FAILURE;      
        }
        
        if(prog_counter == 0x5) {
            if(i8080_get_C() == 9) {
                for(uint16_t de = i8080_get_DE(); mem_start_ptr[de] != '$'; de++){
                    printf("%c", mem_start_ptr[de]);
                    ret = SUCCESS;
                }
            } 
            if(i8080_get_C() == 2) {
                printf("%c", (char)i8080_get_E());
            }
        }
        
        i8080_run_insn();
        prog_counter = i8080_get_current_PC();
        if(prog_counter == 0) {
            if(i == 2 && ret != SUCCESS) {
                return JUMP_FAILURE;
            }        
            break;       
        }
    }
    return SUCCESS;
}

/*
 * The Main for testing 8080 functionality
 */
int main(int argc, char** argv) {
    if(argc != 1) {
        printf("Usage: emulator\n");
        return 1;
    }

    uint8_t i = 0, ret_val = FAILURE;

    // uint8_t *start = memory_init();
    // uint8_t test_byte;
    // uint16_t test_word, test_addr;
    
    // test_byte = 0xAA;
    // test_word = 0x5566;
    // test_addr = 0x1234;

    // printf("Before write, [0x%x] = 0x%x\n",test_addr, read_byte(test_addr)); 
    // write_byte(test_addr, test_byte);
    // printf("After write, [0x%x] = 0x%x\n", test_addr, read_byte(test_addr));

    // printf("Before write, [0x%x] = 0x%x\n",test_addr+5, read_word(test_addr+5)); 
    // write_word(test_addr+5, test_word);
    // printf("After write, [0x%x] = 0x%x\n", test_addr+5, read_word(test_addr+5));
    // printf("[0x%x] = 0x%x\n[0x%x] = 0x%x\n", test_addr+5, read_byte(test_addr+5), test_addr+6, read_byte(test_addr+6));

/*
 *  Testing Condition reg bit magic
 *  
 *  condition_reg c;
    c.f_reg = 0x00;

    printf("0x00\nC_F:%u U_F:%u P_F:%u U_F:%u A_F:%u U_F:%u Z_F:%u S_F:%u\n", c.c_bit.carry_flag, \
            c.c_bit.undef_bit1, c.c_bit.parity_flag, c.c_bit.undef_bit3, c.c_bit.aux_carry, \
            c.c_bit.undef_bit5, c.c_bit.zero_flag, c.c_bit.sign_flag);

    c.f_reg = 0x0F;

    printf("0x0F\nC_F:%u U_F:%u P_F:%u U_F:%u A_F:%u U_F:%u Z_F:%u S_F:%u\n", c.c_bit.carry_flag, \
            c.c_bit.undef_bit1, c.c_bit.parity_flag, c.c_bit.undef_bit3, c.c_bit.aux_carry, \
            c.c_bit.undef_bit5, c.c_bit.zero_flag, c.c_bit.sign_flag);

    c.f_reg = 0xF0;

    printf("0xF0\nC_F:%u U_F:%u P_F:%u U_F:%u A_F:%u U_F:%u Z_F:%u S_F:%u\n", c.c_bit.carry_flag, \
            c.c_bit.undef_bit1, c.c_bit.parity_flag, c.c_bit.undef_bit3, c.c_bit.aux_carry, \
            c.c_bit.undef_bit5, c.c_bit.zero_flag, c.c_bit.sign_flag);

    c.f_reg = 0xFF;

    printf("0xFF\nC_F:%u U_F:%u P_F:%u U_F:%u A_F:%u U_F:%u Z_F:%u S_F:%u\n", c.c_bit.carry_flag, \
            c.c_bit.undef_bit1, c.c_bit.parity_flag, c.c_bit.undef_bit3, c.c_bit.aux_carry, \
            c.c_bit.undef_bit5, c.c_bit.zero_flag, c.c_bit.sign_flag);
*/
    /* while(i < TESTS) {
        ret_val = run_test(i);   
        if(ret_val == SUCCESS) {
            printf("\n**************%s=>SUCCESS**************\n", test_files[i]); 
        } else {
            printf("\n**************%s=>FAILURE**************\n", test_files[i]);
        }

        i++;
    } */
    return SUCCESS;
}
