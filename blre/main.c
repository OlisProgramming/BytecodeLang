#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "../types.h"
#include "../commands.h"

#define STACK_MAX 100

typedef struct {
	int8_t data[STACK_MAX];
	unsigned int count;
} Stack;

void stclr(Stack* stack) {
	stack->count = 0;
	memset(stack->data, 0, STACK_MAX);
}

void stprint(Stack* stack) {
	printf("Stack:");
	for (unsigned int i = 0; i < stack->count; ++i) {
		printf(" %02x", (uint8_t)stack->data[i]);
	}
	puts("");
}

void stpush(Stack* stack, int8_t* pvalue, size_t valueSize) {
	//printf("%u, %zu\n", stack->count, valueSize);
	assert(stack->count+valueSize < STACK_MAX);
	memcpy(stack->data + stack->count, pvalue, valueSize); 
	stack->count += valueSize;
}

void stpushi32(Stack* stack, int32_t value) {
	stpush(stack, (int8_t*)(&value), sizeof(int32_t));
}

int8_t* stpop(Stack* stack, size_t valueSize) {
	assert(stack->count - valueSize >= 0);
	stack->count -= valueSize;
	return &(stack->data[stack->count]);  // Safe to return and use until more things are popped onto stack.
}

int32_t stpopi32(Stack* stack) {
	return *((int32_t*)(stpop(stack, sizeof(int32_t))));
}

int main(int argc, char** argv) {

	FILE* file = fopen("../program.bin", "rb");

	if (!file) {
		puts("Unable to open file!");
		return -1;
	}

	fseek(file, 0L, SEEK_END);
	unsigned long size = ftell(file);
	rewind(file);
	int8_t* instructions = calloc(size, sizeof(int8_t));
	fread(instructions, size, 1, file);
	printf("Instructions:");
	for (unsigned int i = 0; i < size; ++i) {
		printf(" %02x", (uint8_t)instructions[i]);
	}

//	printf("%d chars\n", size);
	puts("");

	fclose(file);
	
	Stack stack;
	stclr(&stack);
	/*stpushi32(&stack, 123);
	stprint(&stack);
	stpushi32(&stack, 234);
	stprint(&stack);
	printf("Popped %d.\n", stpopi32(&stack));
	stprint(&stack);
	printf("Popped %d.\n", stpopi32(&stack));
	stprint(&stack);*/


	int32_t tmp_i32a, tmp_i32b;

	unsigned int instructionPointer = 0;
	bool doClose = false;
	while (!doClose && instructionPointer<size) {
	
		int8_t instruction = instructions[instructionPointer];
		printf("Executing command %d (0x%02x)...\n", instruction, instruction);
		switch (instruction) {
			
		case C_PSH_I32:
			stpushi32(&stack, *((int32_t*)(instructions + instructionPointer + 1)));
			instructionPointer += 1 + sizeof(int32_t);  // Advance instruction pointer past both the instruction and the immediate value.
			break;
			
		case C_ADD_I32:
			stpushi32(&stack, stpopi32(&stack) + stpopi32(&stack));
			++instructionPointer;
			break;
		
		case C_SUB_I32:
			tmp_i32a = stpopi32(&stack);
			tmp_i32b = stpopi32(&stack);
			stpushi32(&stack, tmp_i32b - tmp_i32a);
			++instructionPointer;
			break;
			
		case C_MUL_I32:
			stpushi32(&stack, stpopi32(&stack) * stpopi32(&stack));
			++instructionPointer;
			break;
		
		case C_DIV_I32:
			tmp_i32a = stpopi32(&stack);
			tmp_i32b = stpopi32(&stack);
			stpushi32(&stack, tmp_i32b / tmp_i32a);
			++instructionPointer;
			break;
			
		default:
			printf("Command %d (0x%02x) unrecognised at instructon %d (0x%x)! Exiting...\n", instruction, instruction, instructionPointer, instructionPointer);
			doClose = true;
		}
		
		stprint(&stack);
	}
	
	// Dump int32s from stack
	while (stack.count) {
		printf("Popped %d from stack.\n", stpopi32(&stack));
	}

	return 0;
}
