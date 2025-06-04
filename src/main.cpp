#include <iostream>
#include "bst.h"

int main() {
	BST<std::string> tree;
	const char* filename = "war_peace.txt";
	makeTree(tree, filename);
	std::cout << "Tree depth: " << tree.depth() << std::endl;
	printFreq(tree);
	return 0;
}
