// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>

extern void makeTree(BST<std::string>& tree, const char* filename);
extern void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> wordTree;
    const char* inputFile = "src/war_peace.txt";

    makeTree(wordTree, inputFile);
    printFreq(wordTree);

    std::cout << "Depth of the BST: " << wordTree.depth() << std::endl;

    return 0;
}
