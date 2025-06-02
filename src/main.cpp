// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> tree;
    makeTree(tree, "war_peace.txt");
    printFreq(tree);
    return 0;
}
