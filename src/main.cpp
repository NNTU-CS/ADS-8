// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include "bst.h"

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");

  std::cout << "BST depth: " << tree.depth() << std::endl;

  printFreq(tree);

  return 0;
}
