// Copyright 2021 NNTU-CS

#include  <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> wordTree;
    const char* filename = "src/war_peace.txt";

    makeTree(wordTree, filename);

    std::cout << "Tree height: " << wordTree.heightT() << std::endl;

    printFreq(wordTree);

    int kol = wordTree.searchNode("in");
    if (ko; > 0) {
        std::cout << "Word 'in' found with count: " << kol << std::endl;
    } else {
        std::cout << "Word 'in' not found" << std::endl;
    }

    return 0;
}
