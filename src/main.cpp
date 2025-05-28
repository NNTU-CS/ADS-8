// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

// Прототипы функций, определенных в src/alg.cpp
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    BST<std::string> word_tree;
    const char* filename = "src/war_peace.txt";

    makeTree(word_tree, filename);
    printFreq(word_tree);

    return 0;
}
