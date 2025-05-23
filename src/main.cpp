// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>
#include <stdexcept>

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);
int main() {
    try {
        const char* filename = "src/war_peace.txt";
        BST<std::string> wordTree;
        makeTree(wordTree, filename);
        printFreq(wordTree);
        std::cout << "Tree depth: " << wordTree.depth() << std::endl;
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
