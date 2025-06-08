// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"


void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
    return 0;
  const char* filename = "src/war_peace.txt";
  BST<std::string> tree;

  makeTree(tree, filename);

  std::cout << "Depth of tree: " << tree.depth() << std::endl;

  printFreq(tree);

  return 0;
}

