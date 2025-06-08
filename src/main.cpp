// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#include "bst.h"

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";

  makeTree(tree, filename);
  std::cout << "Tree depth: " << tree.depth() << '\n';

  printFreq(tree);
  return 0;
}
