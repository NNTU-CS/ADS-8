// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#include "bst.h"

int main() {
  BST<std::string> tree;
  const char* filename = "src/war_peace.txt";

  makeTree(tree, filename);
  printFreq(tree);

  std::cout << "Tree depth: " << tree.depth() << std::endl;

  return 0;
}
