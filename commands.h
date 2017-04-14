#ifndef COMMANDS_H
#define COMMANDS_H

#include "types.h"

enum class Command : uint16_t {

	NOP,		// Do nothing
	PSH_I32		// Push int32_t onto stack
};

#endif
