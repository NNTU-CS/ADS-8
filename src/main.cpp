// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main()
{
    const char* filename = "src/war_peace.txt";
    BST<std::string> tree;

    makeTree(tree, filename);

    std::cout << "----- Tree depth: " << tree.depth() << " -----\n\n";
    printFreq(tree);

    return 0;
}
