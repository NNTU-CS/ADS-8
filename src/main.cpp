// Copyright 2021 NNTU-CS
#include "bst.h"

#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  const char* inputFile = "src/war_peace.txt";
  makeTree(tree, inputFile);
  std::cout << "Tree depth: " << tree.depth() << std::endl;
  printFreq(tree);
  return 0;
}
