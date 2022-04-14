#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <assert.h>
#include <math.h>
#include "register.h"

struct UM_T {
        UArray_T my_registers; 
        Memory_T my_memory;
};

UM_T new_um()
{
        int my_um_num = 8;
        UM_T my_um = malloc(sizeof(struct UM_T)); 

        my_um->my_registers = UArray_new(my_um_num, sizeof(uint32_t));
        my_um->my_memory = new_memory();
	return my_um;
}

void free_um(UM_T my_um)
{
        UArray_free(&(my_um->my_registers));
        free_memory(get_mem(my_um));
        free(my_um);
}

uint32_t get_reg(int rA, UM_T my_um)
{
        uint32_t word = *(uint32_t*)UArray_at(my_um->my_registers, rA);
        return word;
}

void set_reg(int rA, uint32_t val, UM_T my_um)
{
        *(uint32_t*)UArray_at(my_um->my_registers, rA) = val;
}

Memory_T get_mem(UM_T my_um)
{
       return my_um->my_memory;
}

void segment_load(int rA, int rB, int rC, UM_T my_um)
{
        uint32_t valrB = get_reg(rB, my_um);
        uint32_t valrC = get_reg(rC, my_um);
        uint32_t instruction = load_instruction(valrB, valrC, my_um->my_memory);
        set_reg(rA, instruction, my_um);
}

void segment_store(int rA, int rB, int rC, UM_T my_um)
{
        uint32_t seg_id = get_reg(rA, my_um);
        uint32_t offset = get_reg(rB, my_um);
        uint32_t instruction = get_reg(rC, my_um);
        store_instruction(seg_id, offset, instruction, my_um->my_memory);
}

void conditional_move(int rA, int rB, int rC, UM_T my_um)
{
        if(get_reg(rC, my_um) != 0) {
                set_reg(rA, get_reg(rB, my_um), my_um);
        } 
}

void addition(int rA, int rB, int rC, UM_T my_um)
{
        uint32_t valrB = get_reg(rB, my_um);
        uint32_t valrC = get_reg(rC, my_um);
        uint32_t val = (valrB + valrC);
        set_reg(rA, val, my_um);
}

void multiplication(int rA, int rB, int rC, UM_T my_um)
{
        uint32_t valrB = get_reg(rB, my_um);
        uint32_t valrC = get_reg(rC, my_um);
        uint32_t val = (valrB * valrC);
        set_reg(rA, val, my_um);

}

void division(int rA, int rB, int rC, UM_T my_um)
{
        uint32_t valrB = get_reg(rB, my_um);
        uint32_t valrC = get_reg(rC, my_um);
        uint32_t val = valrB/valrC;
        set_reg(rA, val, my_um);
}

void bitwise_nand(int rA, int rB, int rC, UM_T my_um)
{
        uint32_t valrB = get_reg(rB, my_um);
        uint32_t valrC = get_reg(rC, my_um);
        uint32_t val = ~(valrB & valrC);
        set_reg(rA, val, my_um);
}

int halt()
{
        exit(0);
}

void map_segment(int rC, int rB, UM_T my_um)
{
        uint32_t valrC = get_reg(rC, my_um);
        uint32_t address = map_memory(valrC, my_um->my_memory);
        set_reg(rB, address, my_um);
}

void ummap_segment(int rC, UM_T my_um)
{
        uint32_t valrC = get_reg(rC, my_um);
        unmap_memory(valrC, my_um->my_memory);
}

void output(int rC, UM_T my_um)
{
        int valrC = get_reg(rC, my_um);
        fputc(valrC, stdout);
}

void input(int rC, UM_T my_um)
{       
        uint32_t valrC = fgetc(stdin);
        int32_t end = -1; 

        if(valrC == (uint32_t)end) {
                set_reg(rC, (uint32_t)end, my_um);
        }

        set_reg(rC, valrC, my_um);
}

void load_program(int rB, UM_T my_um)
{
        uint32_t valrB = get_reg(rB, my_um);
        if(valrB != 0) {
               UArray_T program = load_memory(rB, my_um->my_memory);
               store_memory(program, my_um->my_memory);
        }
}

void load_value(int rA, uint32_t value, UM_T my_um)
{
        set_reg(rA, value, my_um);
}