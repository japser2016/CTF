#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <seq.h>
#include <stdint.h>
#include <assert.h>
#include "memory.h"
#define max_seg_len (1<<32)

struct Memory_T {
	Seq_T segment_manager;
	Seq_T queue;
};

Memory_T new_memory()
{
        Memory_T my_mem = malloc(sizeof(struct Memory_T));
        my_mem->segment_manager = Seq_new(0);
        my_mem->queue = Seq_new(0);
        return my_mem;
}

void free_memory(Memory_T my_mem)
{
        Seq_free(&(my_mem->queue));
        Seq_free(&(my_mem->segment_manager));    
        free(my_mem);    
}

uint32_t load_instruction(uint32_t valrB, uint32_t valrC, Memory_T memory)
{
        UArray_T segment = (UArray_T)Seq_get(memory->segment_manager, valrB);
        uint32_t instruction = *(uint32_t*)UArray_at(segment, valrC); 
        return instruction;
}

void store_instruction(uint32_t valrA, uint32_t valrB, uint32_t valrC, Memory_T memory)
{
        UArray_T segment = ((UArray_T)Seq_get(memory->segment_manager, valrA));
        *(uint32_t*) UArray_at(segment, valrB) = valrC;
        // fprintf(stderr, "Actual instruction in mem: %u\n", *(uint32_t*)UArray_at(segment, valrB));
}

UArray_T load_memory(uint32_t valrB, Memory_T memory)
{
      UArray_T segment = (UArray_T)Seq_get(memory->segment_manager, valrB);
      UArray_T dup_segment = UArray_copy(segment, UArray_length(segment));
      return dup_segment;
}

void store_memory(UArray_T mem, Memory_T memory)
{
        UArray_T segment = (UArray_T) Seq_get(memory->segment_manager, 0);
        UArray_free(&segment);
        Seq_put(memory->segment_manager, 0, (void*)mem);
}

uint32_t map_memory(uint32_t valrC, Memory_T memory)
{

        if (Seq_length(memory->queue) == 0) {
                UArray_T segment = UArray_new(valrC, sizeof(uint32_t));
                Seq_addhi(memory->segment_manager, (void*)segment);
                return Seq_length(memory->segment_manager) - 1;
        } else {
                uint32_t seg_id = (uint64_t)Seq_remlo(memory->queue);
                UArray_T segment = UArray_new(valrC, sizeof(uint32_t));
                Seq_put(memory->segment_manager, seg_id, (void*)segment);
                return seg_id;
        }
}

void unmap_memory(uint32_t valrC, Memory_T memory)
{
        Seq_addhi(memory->queue, (void*)(uintptr_t)valrC);
        UArray_T segment = Seq_get(memory->segment_manager, valrC);
        UArray_free(&segment);
}