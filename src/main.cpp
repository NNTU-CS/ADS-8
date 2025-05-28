// Copyright 2021 NNTU-CS
#include "bst.h"
#include "alg.cpp"


int main() {
    BST<std::string> tree;
    const char* filename = "src/war_peace.txt";
    makeTree(tree, filename);
    printFreq(tree);
    return 0;
}
