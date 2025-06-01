// Copyright 2021 NNTU-CS

#include  <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(const BST<std::string>& tree);

int main() {
    BST<std::string> wordTree;
    const char* filename = "src/war_peace.txt";

    makeTree(wordTree, filename);

    std::cout << "Tree height: " << wordTree.height() << std::endl;

    printFreq(wordTree);

    int kol = wordTree.search("in");
    if (kol; > 0) {
        std::cout << "Word 'in' found with count: " << kol << std::endl;
    } else {
        std::cout << "Word 'in' not found" << std::endl;
    }

    return 0;
}
