#ifndef COMMANDS_H
#define COMMANDS_H

#include "types.h"

enum
#ifdef __cplusplus
Command : uint8_t
#endif
{

	C_NOP,		// Do nothing
	C_PSH_I32,	// Push int32_t onto stack
	C_ADD_I32,	// Add top two int32s on stack, return int32 result on stack.
	C_SUB_I32,	// Subtract top two int32s on stack, return int32 result on stack.
	C_MUL_I32,	// Multiply top two int32s on stack, return int32 result on stack.
	C_DIV_I32,	// Divide top two int32s on stack, return int32 result on stack.
};

#endif
