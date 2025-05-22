// Copyright 2021 NNTU-CS
#include "bst.h"

#include <iostream>
#include <string>

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  printFreq(tree);
  return 0;
}
