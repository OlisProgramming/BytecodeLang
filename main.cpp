#include "parser.h"
#include "nodes.h"
#include "bytecode_generator.h"

int main(int argc, char* argv[]) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("program.txt", "r");
	// make sure it is valid:
	if (!myfile) {
		return -1;
	}
	Node* program = parse_file(myfile);
	
	generate_bytecode(program, "program.bin");
	
	return 0;
}
