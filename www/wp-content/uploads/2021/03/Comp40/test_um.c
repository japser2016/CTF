#include <stdlib.h>
#include <stdio.h>
#include <uarray.h>
#include <seq.h>
#include <assert.h>
#include "register.h"

int main()
{
	UM_T my_um = new_um();

	 /*Test get_reg and set_reg*/
	uint32_t val = 12345678;
	set_reg(0, val, my_um);
	fprintf(stderr, "%u\n", get_reg(0, my_um));

	/*Test segment_load */
	uint32_t addy = map_memory(5, get_mem(my_um));
	uint32_t addy1 = map_memory(8, get_mem(my_um));
	uint32_t addy2 = map_memory(4, get_mem(my_um));


	fprintf(stderr, "address: %u\n", addy);
	store_instruction(addy, 0, val, get_mem(my_um));

	set_reg(1, 0, my_um);
	set_reg(addy, 0, my_um);
	segment_load(4, addy, 1, my_um);

	uint32_t valr4 = get_reg(4, my_um);
	fprintf(stderr, "valr4 in segment_load: %u\n", valr4);

	unmap_memory(addy2, get_mem(my_um));
	uint32_t addy4 = map_memory(15, get_mem(my_um));
	fprintf(stderr, "addy4 in segment_store: %u\n", addy4);

	// segment_store(); 
	segment_store(addy1, 5, 4, my_um);
	segment_load(7, addy1, 5, my_um);
	fprintf(stderr, "Expected 12345678: %u\n", get_reg(7, my_um));

	// fprintf(stderr, "valr4: %u, instruction: %u\n", valr4, load_instruction(get_reg(addy1, my_um), get_reg(5, my_um), my_um->my_memory));

	/*Test conditional_move */ 
	int rA = 0;
	int rB = 1;
	int rC = 2;  
	set_reg(rA, 0, my_um);
	set_reg(rB, 12345678, my_um);
	set_reg(rC, 5, my_um);
	conditional_move(rA, rB, rC, my_um);
	uint32_t valrA = get_reg(rA, my_um);
	fprintf(stderr, "valrA should be: 12345678: %u\n", valrA);

	set_reg(rC, 0, my_um);
	set_reg(rA, 0, my_um);
	set_reg(rB, 12345678, my_um);

	conditional_move(rA, rB, rC, my_um);
	valrA = get_reg(rA, my_um);
	fprintf(stderr, "valrA should be: 0: %u\n", valrA);

	/*Test addtion*/
	set_reg(rA, 0, my_um);
	set_reg(rB, 69, my_um);
	set_reg(rC, 420, my_um);
	addition(rA, rB, rC, my_um);

	valrA = get_reg(rA, my_um);
	fprintf(stderr, "valrA should be: 489: %u\n", valrA);
	/*Test multiplication*/
	multiplication(rA, rB, rC, my_um);
	valrA = get_reg(rA, my_um);
	fprintf(stderr, "valrA should be: 28980: %u\n", valrA);

	/*Test division*/
	division(rA, rB, rC, my_um);
	valrA = get_reg(rA, my_um);
	fprintf(stderr, "valrA should be: 0: %u\n", valrA);

	// halt();

	// /*bitwisenand*/
	set_reg(rB, 75, my_um);
	set_reg(rC, 55, my_um);
	bitwise_nand(rA, rB, rC, my_um);
	valrA = get_reg(rA, my_um);
	fprintf(stderr, "valrA should be: 4294967292: %u\n", valrA);

	/*IO*/
	input(rC, my_um);
	output(rC, my_um);




}