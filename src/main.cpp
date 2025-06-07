// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

// The program builds a binary search tree from a text file and outputs its depth and word frequency

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  const char* filename = "src/war_peace.txt";
  BST<std::string> tree;

  makeTree(tree, filename);

  std::cout << "Depth of tree: " << tree.depth() << std::endl;

  printFreq(tree);

  return 0;
}


