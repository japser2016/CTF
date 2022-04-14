#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <seq.h>
#include <assert.h>
#include <sys/stat.h>
#include <bitpack.h>
#include "register.h"


void initilize (char*, UM_T, int);
uint64_t execute(UM_T, uint32_t, int*);

int main(int argc, char *argv[])
{      
        // assert(argc = 1);
        (void) argc;
        int program_counter = 0;
	UM_T my_um = new_um();

        //gets length of input file
        struct stat st;
        stat(argv[1], &st);
        int file_len = st.st_size; 

        // fprintf(stderr, "The file len is %d \n", file_len);

        initilize(argv[1], my_um, file_len);

        uint64_t opcode = 0;
        while(opcode != 7) {
                uint32_t instruction = load_instruction(0, program_counter, get_mem(my_um));
                if(opcode != 12) {
                        program_counter++;
                }
                // fprintf(stderr, "instuction: %u\n", instruction);
                opcode = execute(my_um, instruction, &program_counter);
                // fprintf(stderr, "opcode: %lu\n", opcode);
                // fprintf(stderr, "program_counter: %d\n", program_counter);
        }

        free_um(my_um);

	return 0;
}

void initilize(char *filename, UM_T my_um, int file_len)
{
        int i, j, k; 
        FILE *fp = fopen(filename, "r");
        char temp_instruction[4];

        /*setting all registers to 0*/
        for(k = 0; k < 7; k++){
                set_reg(k, 0, my_um);
        }

        /*mapping the program to memory segment 0*/
        UArray_T program = UArray_new(file_len/4, sizeof(uint32_t));

        for(i = 0; i < file_len/4; i++) {
                for(j = 3; j >= 0; j--) {
                        temp_instruction[j] = fgetc(fp); 
                        // fprintf(stderr, "%c\n", temp_instruction[j]);
                }
                uint32_t word = *(uint32_t*)temp_instruction;
                *(uint32_t*) UArray_at(program, i) = word;
        }    

        // fprintf(stderr, "before store\n");
        map_memory(0, get_mem(my_um));
        store_memory(program, get_mem(my_um));
        // fprintf(stderr, "after store\n");
}

uint64_t execute(UM_T my_um, uint32_t instruction, int* program_counter)
{
        uint64_t opcode = Bitpack_getu(instruction, 4, 28);

        if (opcode == 13) {
                int rA = Bitpack_getu(instruction, 3, 25);
                int val = Bitpack_getu(instruction, 25, 0);
                load_value(rA, val, my_um);
        } else { 
                int rA = Bitpack_getu(instruction, 3, 6);
                int rB = Bitpack_getu(instruction, 3, 3);
                int rC = Bitpack_getu(instruction, 3, 0);

                switch(opcode)
                {
                        case 0: 
                                conditional_move(rA, rB, rC, my_um);
                                break;
                        case 1: 
                                segment_load(rA, rB, rC, my_um);
                                break;
                        case 2: 
                                segment_store(rA, rB, rC, my_um);
                                break; 
                        case 3: 
                                addition(rA, rB, rC, my_um);
                                break; 
                        case 4: 
                                multiplication(rA, rB, rC, my_um);
                                break; 
                        case 5: 
                                division(rA, rB, rC, my_um);
                                break; 
                        case 6: 
                                bitwise_nand(rA, rB, rC, my_um);
                                break; 
                        case 7: 
                                halt();
                                break;  
                        case 8: 
                                map_segment(rC, rB, my_um);
                                break; 
                        case 9: 
                                ummap_segment(rC, my_um);
                                break; 
                        case 10: 
                                output(rC, my_um);
                                break; 
                        case 11: 
                                input(rC, my_um);
                                break; 
                        case 12: 
                                load_program(rB, my_um);
                                *program_counter = get_reg(rC, my_um);
                                break; 

                        (void) program_counter;
                }
        }
        return opcode;
}