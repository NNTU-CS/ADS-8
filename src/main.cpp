// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";

  makeTree(tree, filename);

  std::cout << "Tree depth: " << tree.depth() << std::endl;
  std::cout << "Printing frequency..." << std::endl;

  printFreq(tree);

  return 0;
}
