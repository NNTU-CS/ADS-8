// Copyright 2021 NNTU-CS
#include "bst.h"

void makeTree(BST<std::string>&, const char*);

int main() {
    BST<std::string> tree;
    makeTree(tree, "war_peace.txt");
    return 0;
}
