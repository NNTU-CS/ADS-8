// Copyright 2021 NNTU-CS
#include "bst.h"

int main() {
    BST<std::string> tree;
    makeTree(tree, "src/war_peace.txt");

    std::cout << "Depth of the tree: " << tree.depth() << std::endl;
    printFreq(tree);
    return 0;
}
