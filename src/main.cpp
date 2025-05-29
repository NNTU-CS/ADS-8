// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(bst::BST<std::string>& tree, const char* filename);
void printFreq(bst::BST<std::string>& tree);

int main() {
  bst::BST<std::string> tree;
  const char* filename = "src\\war_peace.txt";

  makeTree(tree, filename);

  std::cout << "Depth: " << tree.depth() << std::endl;
  printFreq(tree);

  return 0;
}
