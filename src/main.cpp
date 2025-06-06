// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  std::cout << "Tree depth: " << tree.depth() << '\n';
  printFreq(tree);
  return 0;
}
