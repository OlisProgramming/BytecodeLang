#ifndef COMMANDS_H
#define COMMANDS_H

#include "types.h"

enum class Command : uint8_t {

	NOP,		// Do nothing
	PSH_I32,	// Push int32_t onto stack
	ADD_I32,	// Add top two int32s on stack, return int32 result on stack.
	SUB_I32,	// Subtract top two int32s on stack, return int32 result on stack.
	MUL_I32,	// Multiply top two int32s on stack, return int32 result on stack.
	DIV_I32,	// Divide top two int32s on stack, return int32 result on stack.
};

#endif
