// Copyright 2021 NNTU-CS
#include "bst.h"

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);

int main() {
    BST<std::string> my_tree;

    makeTree(my_tree, "src/war_peace.txt");
    printFreq(my_tree);

    return 0;
}