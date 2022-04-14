#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <seq.h>
#include <assert.h>
#include "memory.h"

#define FAIL -1
#define UArray_T int
/*We ran into a little issue with the Makefile we could not link
  any of the Hanson data structures so we defined UArray as an int
  it will not be like this in the actual implementation*/

void test_load_instruction();
void test_store_instruction();
void test_store_memory();
void test_load_memory();
void map_test();
void test_queue();


int main()
{
        init_mem();

        test_load_instruction();
        test_store_instruction();
        test_store_memory();
        void test_load_memory();
}

/* We assume that the individual functions have passed the obvious test 
   we are only writing the test cases that involves a number of differt
   functions */

void test_load_instruction()
{
        uint32_t word; 
        word = load_instruction(-1, -1);
        word = load_instruction(32432, 1);  
        (void) word;
}

void test_store_instruction()
{
        uint32_t valrA = 1;
        uint32_t valrB = 2;
        uint32_t valrC = 3;
        store_instruction(valrC, valrA, valrB); 

        valrC = 5;
        store_instruction(valrC, valrA, valrB);

        valrA = -1;
        valrB = -1;
        store_instruction(valrC, valrA, valrB);
}

void test_store_memory()
{
        uint32_t valrC = map_memory(5);
        UArray_T segment = load_memory(valrC);
        store_memory(valrC, segment);
        if(segment == load_memory(valrC))
                fprintf(stderr, "passed test_store_memory");
}

void test_load_memory()
{
        uint32_t valrB = -1;
        load_memory(valrB);

        valrB = 433324;
        load_memory(valrB);
}

void map_test()
{
        uint32_t valrC = map_memory(5);
        unmap_memory(valrC);
        load_memory(valrC);
}

void test_queue()
{
        uint32_t valrC = map_memory(5);
        unmap_memory(2); 
        uint32_t valrB = map_memory(1);
        if (valrB == 2)
                fprintf(stderr, "passed test_queue");
        (void) valrC;
}

