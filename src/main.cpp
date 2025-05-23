// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void build_word_tree(BinarySearchTree<std::string>&, const char*);
void display_frequencies(const BinarySearchTree<std::string>&);

int main() {
    BinarySearchTree<std::string> word_storage;
    makeTree(word_storage, "war_peace.txt");
    display_frequencies(word_storage);
    return 0;
}
