// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>
void makeTree(BST<std::string>&, const char* filename);
void printPeriod(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    makeTree(tree, "war_peace.txt");
    printPeriod(tree);
    return 0;
}
