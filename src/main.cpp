// Copyright 2021 NNTU-CS
#include "bst.h"

int main() {
    return 0;
}
#include <iostream>

int main() {
	BST<std::string> tree;
	const char* filename = "war_peace.txt";
	makeTree(tree, filename);
	std::cout << "Tree depth: " << tree.depth() << std::endl;
	printFreq(tree);
	return 0;
}
