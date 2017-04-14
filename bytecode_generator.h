#ifndef BYTECODE_GENERATOR_H
#define BYTECODE_GENERATOR_H
#include "nodes.h"
#include <string>
void generate_bytecode(Node* program, std::string outfilename);
#endif
