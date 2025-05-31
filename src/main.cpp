// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> wordTree;
    makeTree(wordTree, "war_peace.txt");
    printFreq(wordTree);
    return 0;
}
