// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include "bst.h"
#include "alg.cpp"

int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";
    makeTree(tree, filename);
    std::cout << "Word frequency analysis:\n";
    tree.printFreq();
    printFreq(tree);
    std::cout << "\nTree depth: " << tree.depth() << std::endl;
    return 0;
}
