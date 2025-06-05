// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(const BST<std::string>& tree);

int main() {
    BST<std::string> wordTree;
    const char* filename = "src/war_peace.txt";

    makeTree(wordTree, filename);

    std::cout << "Глубина дерева: " << wordTree.depth() << std::endl;

    printFreq(wordTree);

    int pierreCount = wordTree.search("pierre");
    std::cout << "Pierres найдено: " << pierreCount << std::endl;

    int natashaCount = wordTree.search("natasha");
    std::cout << "Natashas найдено: " << natashaCount << std::endl;

    int andrewCount = wordTree.search("andrew");
    std::cout << "Andrews найдено: " << andrewCount << std::endl;

    return 0;
}
