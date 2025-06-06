// Copyright 2021 NNTU-CS
#include "bst.h"

extern void makeTree(BST<std::string>& tree, const char* filename);
extern void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;

    makeTree(tree, "src/war_peace.txt");

    printFreq(tree);
    
    return 0;
}
