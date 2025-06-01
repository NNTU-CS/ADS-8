// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <string>

void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>&);

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  printFreq(tree);

  std::cout << "Depth: " << tree.depth() << std::endl;
  std::cout << "Occurrences of 'war': " << tree.search("war") << std::endl;

  return 0;
}
