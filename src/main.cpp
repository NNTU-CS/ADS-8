// Copyright 2021 NNTU-CS
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");

    std::cout << "Depth of the tree: " << tree.depth() << std::endl;
    printFreq(tree);
    return 0;
}
