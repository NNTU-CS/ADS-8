// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "../include/bst.h"

/// объявления реализованы в alg.cpp
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    const char* filename = "src/war_peace.txt";
    BST<std::string> tree;

    std::cout << "Building tree…\n";
    makeTree(tree, filename);

    std::cout << "Tree height  : " << tree.depth() << '\n';
    std::cout << "Unique words : ";
    size_t cnt = 0;
    tree.forEachInOrder([&](auto*){ ++cnt; });
    std::cout << cnt << "\n\n";

    std::cout << "=== TOP words ===\n";
    printFreq(tree);

    return 0;
}
