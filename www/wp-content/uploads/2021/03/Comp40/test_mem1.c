#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <seq.h>
#include <assert.h>
#include "memory.h"

int main()
{
	/*Test new_memory()*/
	Memory_T memory = new_memory();

	/*Test map_memory()*/
	uint32_t segment0 = map_memory(5, memory);
	uint32_t segment1 = map_memory(6, memory);
	uint32_t segment2 = map_memory(7, memory);
	// uint32_t segment3 = map_memory(8, memory);
	// printf("Expected # of Segments: 1\n");
	// printf("Expected Segment Size: 5\n");


	/*Prints out the memory address of the first two arguments*/
	printf("%u\n", segment0);
	printf("%u\n", segment1);

	/*Tests store_instruction()*/
	store_instruction(1, 0, 12345678, memory);


	uint32_t instruction1 = load_instruction(1, 0, memory);
	printf("%u\n", instruction1);

	UArray_T temp_seg = load_memory(segment1, memory);
	store_memory(temp_seg, memory);
	temp_seg = load_memory(segment0, memory);
	instruction1 = load_instruction(0, 0, memory);
	printf("%u\n", instruction1);

	unmap_memory(segment2, memory);
	uint32_t segment4 = map_memory(7, memory);
	fprintf(stderr, "address of seg4: %u, expected address: %u\n", segment4, segment2);


}