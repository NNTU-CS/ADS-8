// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void MakeTree(BST<std::string>& tree, const char* filename);
void PrintFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  MakeTree(tree, "src/war_peace.txt");
  PrintFreq(tree);
  std::cout << "Tree depth: " << tree.Depth() << std::endl;
  return 0;
}
