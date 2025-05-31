// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> tree;
    tree.insert("hello");
    tree.insert("world");
    tree.insert("foo");
    tree.insert("bar");

    std::cout << "Tree depth: " << tree.depth() << std::endl;  // здесь было Depth() — исправила
    std::cout << "Tree size: " << tree.size() << std::endl;

    return 0;
}
