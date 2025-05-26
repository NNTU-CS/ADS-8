// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include "alg.cpp"

int main() {
    BST<std::string> tree;
    makeTree(tree, "../src/war_peace.txt");

    std::cout << "\nTree depth: " << tree.depth() << "\n";
    std::cout << "\nMost frequent words:\n";
    printFreq(tree);

    return 0;
}