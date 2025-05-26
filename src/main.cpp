// Copyright 2021 NNTU-CS

#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    const char* fname = "../src/war_peace.txt";

    makeTree(tree, fname);

    std::cout << "\nTree depth: " << tree.depth() << "\n\n";
    printFreq(tree);
    return 0;
}