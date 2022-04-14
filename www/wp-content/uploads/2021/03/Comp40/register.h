#ifndef UM_INCLUDE
#define UM_INCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <assert.h>
#include <stdint.h>
#include "memory.h"

typedef struct UM_T* UM_T;

UM_T new_um();

void free_um(UM_T my_um);

uint32_t get_reg(int rA, UM_T my_um);

void set_reg(int rA, uint32_t val, UM_T my_um);

Memory_T get_mem(UM_T my_um);

void segment_load(int rA, int rB, int rC, UM_T my_um);

void segment_store(int rA, int rB, int rC, UM_T my_um);

void conditional_move(int rA, int rB, int rC, UM_T my_um);

void addition(int rA, int rB, int rC, UM_T my_um);

void multiplication(int rA, int rB, int rC, UM_T my_um);

void division(int rA, int rB, int rC, UM_T my_um);

void bitwise_nand(int rA, int rB, int rC, UM_T my_um);

int halt();

void map_segment(int rC, int rB, UM_T my_um);

void ummap_segment(int rC, UM_T my_um);

void output(int rC, UM_T my_um);

void input(int rC, UM_T my_um);

void load_program(int rB, UM_T my_um);

void load_value(int rA, uint32_t value, UM_T my_um);

#endif