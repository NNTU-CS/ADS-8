// Copyright 2021 NNTU-CS
#include <iostream>
#include "bst.h"

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  printFreq(tree);
  std::cout << "Depth: " << tree.depth() << "\n";
  return 0;
}
