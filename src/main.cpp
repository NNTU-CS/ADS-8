// Copyright 2021 NNTU-CS
#include "bst.h"
void makeTree(BST&, const char*);
void printPeriod(BST&);

int main() {
    BST tree;
    makeTree(tree, "war_peace.txt");
    printPeriod(tree);
    return 0;
}
