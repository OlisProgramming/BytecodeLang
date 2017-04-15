#include <stdio.h>
#include <stdlib.h>
#include "../types.h"

#define STACK_MAX 100

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

	return 0;
}
