// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);
int main() {
  BST<std::string> tree;
  std::cout << "Building tree from War and Peace..." << std::endl;
  makeTree(tree, "src/war_peace.txt");
  std::cout << "Tree depth: " << tree.depth() << std::endl;
  std::cout << "\nWord frequencies (also saved to result/freq.txt):\n" << std::endl;
  printFreq(tree);
  return 0;
}
