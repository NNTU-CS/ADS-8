// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"
#include "alg.h"

int main() {
    BST<std::string> tree;
    const char* filename = "war_peace.txt";
    makeTree(tree, filename);
    printFreq(tree);
    return 0;
}
