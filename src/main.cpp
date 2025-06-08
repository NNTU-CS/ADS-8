// Copyright 2021 NNTU-CS
#include "bst.h"
#include "alg.cpp"

int main() {
    const char* filename = "war_peace.txt";
    BST<std::string> tree;
    makeTree(tree, filename);
    printFreq(tree);
    return 0;
}
