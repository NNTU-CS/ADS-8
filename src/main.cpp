// Copyright 2021 NNTU-CS
#include "bst.h"
#include "alg.cpp"


int main() {
    BST<std::string> tree;
    const char* filename = "/home/runner/work/ADS-8/ADS-8/build/test/war_peace.txt";
    makeTree(tree, filename);
    printFreq(tree);
    return 0;
}
