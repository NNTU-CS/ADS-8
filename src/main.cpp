// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include "bst.h"

extern void makeTree(BST<std::string>& tree, const char* filename);
extern void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";

    makeTree(tree, filename);
    printFreq(tree);

    std::cout << "Tree depth: " << tree.depth() << std::endl;
    return 0;
