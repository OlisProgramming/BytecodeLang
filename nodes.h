#ifndef LEXPARSE_NODES_H
#define LEXPARSE_NODES_H
#include <string>
#include <vector>

class Node { public: virtual std::string getDotCommand(std::string name) = 0; virtual std::string getSymbol() = 0; };

class NodeNumeric : public Node {
protected:
	int num;
public:
	NodeNumeric(int val) : num(val) {}
	std::string getDotCommand(std::string name) override {		
		return name+" [label=\"" + std::to_string(num) + "\"];\n";
	}
	std::string getSymbol() override { return std::to_string(num); }
};

class NodeBinaryOperator : public Node {
protected:
	Node* left;
	Node* right;
public:
	NodeBinaryOperator(Node* left, Node* right) : left(left), right(right) {}
	std::string getDotCommand(std::string name) override {		
		return name+" [label=\"" + getSymbol() + "\"];\n" + left->getDotCommand(name+"_A") + right->getDotCommand(name+"_B") + name + " -> " + name+"_A;\n" + name + " -> " + name+"_B;\n";
	}
};

class NodePlus : public NodeBinaryOperator {
//	using NodeBinaryOperator::NodeBinaryOperator;
public:
	NodePlus(Node* left, Node* right) : NodeBinaryOperator(left, right) {}
	std::string getSymbol() override { return "+"; }
};

class NodeMinus : public NodeBinaryOperator {
//	using NodeBinaryOperator::NodeBinaryOperator;
public:
	NodeMinus(Node* left, Node* right) : NodeBinaryOperator(left, right) {}
	std::string getSymbol() override { return "-"; }
};

class NodeMul : public NodeBinaryOperator {
//	using NodeBinaryOperator::NodeBinaryOperator;
public:
	NodeMul(Node* left, Node* right) : NodeBinaryOperator(left, right) {}
	std::string getSymbol() override { return "*"; }
};

class NodeDiv : public NodeBinaryOperator {
//	using NodeBinaryOperator::NodeBinaryOperator;
public:
	NodeDiv(Node* left, Node* right) : NodeBinaryOperator(left, right) {}
	std::string getSymbol() override { return "/"; }
};

class NodeExprList : public Node {
protected:
	std::vector<Node*> arglist;
public:
	NodeExprList(Node* left) { arglist.push_back(left); }
	NodeExprList(Node* left, Node* right) { arglist.push_back(left); arglist.push_back(right); }
	void addChild(Node* node) { arglist.push_back(node); }
	std::string getDotCommand(std::string name) override {		
		std::string out = name+" [label=\"" + getSymbol() + "\"];\n";
		for (unsigned int i = 0; i < arglist.size(); ++i) {
			out += arglist[i]->getDotCommand(name + "_" + std::to_string(i)) + name + " -> " + name + "_" + std::to_string(i) + ";\n";
		}
		return out;
	}
	std::string getSymbol() override { return "exprlist"; }
	
};

class NodeProgram : public Node {
protected:
	NodeExprList* exprlist;
public:
	NodeProgram(NodeExprList* exprlist) : exprlist(exprlist) {}
	std::string getSymbol() override { return "program"; }
	std::string getDotCommand(std::string name) override {
		return name+" [label=\"program\"];\n" + exprlist->getDotCommand(name+"_A") + name + " -> " + name + "_A;\n";
	}
};

#endif
