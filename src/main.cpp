// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> tree;
    makeTree(tree, "war_peace.txt");
    printFreq(tree);

    std::cout << "Depth of tree: " << tree.depth() << "\n";
    std::cout << "Search 'war': " << (tree.search("war") ? "Found" : "Not Found") << "\n";

    return 0;
}
