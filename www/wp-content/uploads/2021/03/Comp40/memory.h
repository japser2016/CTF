#ifndef MEMORY_INCLUDE
#define MEMORY_INCLUDE

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef struct Memory_T* Memory_T; 

Memory_T new_memory();

void free_memory();

uint32_t load_instruction(uint32_t valrB, uint32_t valrC, Memory_T memory);

void store_instruction(uint32_t valrA, uint32_t valrB, uint32_t valrC, Memory_T memory);

UArray_T load_memory(uint32_t valrB, Memory_T memory);

void store_memory(UArray_T mem, Memory_T memory);

uint32_t map_memory(uint32_t valrC, Memory_T memory);

void unmap_memory(uint32_t valrC, Memory_T memory);

#endif
