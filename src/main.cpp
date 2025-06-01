// Copyright 2021 NNTU-CS
#include <iostream>
#include "bst.h"
#include <string>
int main() {
    BST<std::string> wordTree;
    const char* filename = "src/war_peace.txt";

    makeTree(wordTree, filename);
    printFreq(wordTree);

    return 0;
}
