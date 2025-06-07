// Copyright 2021 NNTU-CS
#include "bst.h"
#include "alg.cpp"

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  std::cout << "Tree depth: " << tree.depth() << std::endl;
  printFreq(tree);

  return 0;
}
