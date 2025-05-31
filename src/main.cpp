// Copyright 2021 NNTU-CS

#include <string>
#include <iostream>
#include <fstream>
#include "bst.h"

int main() {
    BST<std::string> wordTree;
    const char* filename = "src/war_peace.txt";
    makeTree(wordTree, filename);
    std::cout << "Tree depth: " << wordTree.depth() << std::endl;
    printFreq(wordTree);
    return 0;
}
