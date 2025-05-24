// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "../include/bst.h"

int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");
    printFreq(tree);
    return 0;
}
