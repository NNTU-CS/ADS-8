// Copyright 2021 NNTU-CS
#include "bst.h"
#include "alg.h"
#include <iostream>

int main() {
    BST<std::string> tree;
    process("data.txt", tree);
    std::cout << "Tree depth: " << tree.depth() << std::endl;
    std::cout << "Unique words: " << tree.count() << std::endl;
    return 0;
}
