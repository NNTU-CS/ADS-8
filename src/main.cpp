// Copyright 2021 NNTU-CS
#include "../include/bst.h"
#include <iostream>
#include <string>
void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);
int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");
    printFreq(tree);
    return 0;
}
