#include "parser.h"
#include "nodes.h"

int main(int argc, char* argv[]) {
	// open a file handle to a particular file:
	FILE *myfile = fopen("program.txt", "r");
	// make sure it is valid:
	if (!myfile) {
		return -1;
	}
	Node* program = parse_file(myfile);
	
	
	
	return 0;
}
