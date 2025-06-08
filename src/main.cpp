// Copyright 2021 NNTU-CS
#include "bst.h"

#include <iostream>
#include <string>

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";

  makeTree(tree, filename);
  std::cout << "Tree depth: " << tree.depth() << '\n';

  printFreq(tree);
  return 0;
}
