// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    const char* filename;
    if (argc > 1) {
        filename = argv[1];
    } else {
        filename = "src/war_peace.txt";
    }
    BST<std::string> tree;
    makeTree(tree, filename);
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    printFreq(tree);
    return 0;
}
