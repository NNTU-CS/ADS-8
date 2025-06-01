// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

extern void makeTree(BST<std::string>& tree, const char* filename);
extern void displayFrequency(BST<std::string>& tree);

int main() {
     BST<std::string> wordTree;
    const char* inputFile = "src/war_peace.txt";

    makeTree(wordTree, inputFile);
    displayFrequency(wordTree);

    std::cout << "Depth of the BST: " << wordTree.height() << std::endl;

    return 0;
}
