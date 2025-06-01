// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <locale>
#include "bst.h"

void processFile(BST<std::string>& tree, std::ifstream& file);
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
std::locale::global(std::locale("C"));
BST<std::string> tree;
const char* filename = "war_peace.txt";
makeTree(tree, filename);
printFreq(tree);
    return 0;
}
