// Copyright 2021 NNTU-CS
#include "bst.h"

int main() {
    BST<std::string> freq_tree;
    makeTree(freq_tree, "src/war_peace.txt");
    std::cout << "Tree depth: " << freq_tree.depth() << std::endl;
    printFreq(freq_tree);
    return 0;
}