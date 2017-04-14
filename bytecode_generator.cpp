#include "bytecode_generator.h"

#include <string>
#include <fstream>
#include "commands.h"

template<typename T> void ofswrite(std::ofstream& ofs, T val) {
	ofs.write(reinterpret_cast<char*>(&val), sizeof(T));
}

void assertmsg(bool expr, std::string msg) {
	if (!expr) { fputs(msg.c_str(), stderr); fputs("\n", stderr); throw std::runtime_error(""); }
}

void generate_bytecode(Node* node, std::ofstream& ofs);

void generate_bytecode(Node* program, std::string outfilename) {

	puts("Begin bytecode generation...");

	std::ofstream ofs(outfilename, std::ios::binary);

	bool successful = true;

	try {
		assertmsg(program->getClassName() == "NodeProgram", "Initial node must be program node!");
		generate_bytecode(program, ofs);
	} catch (std::runtime_error& ex) {
		successful = false;
	}
	
	ofs.close();

	if (successful) puts("Successfully completed bytecode generation.\n");
}


void generate_bytecode(Node* node, std::ofstream& ofs) {
	if (node->getClassName() == "NodeProgram") {
		for (Node* expr : ((NodeProgram*)node)->getExprList()->getChildren()) {
			// Complete a post-order traversal of each expression.
			generate_bytecode(expr, ofs);
		}
	}
	
	else if (node->getClassName() == "NodeNumeric") {
		ofswrite<Command>(ofs, Command::PSH_I32);
		ofswrite<int32_t>(ofs, ((NodeNumeric*)node)->getInt32Val());
	}
	
	else {
		assertmsg(false, "Unrecognised node type: '" + node->getClassName() + "'.");
	}
}
