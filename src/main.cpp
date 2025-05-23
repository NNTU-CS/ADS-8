// Copyright 2021 NNTU-CS

#include <string>
#include "bst.h"
void makeTree(BST<std::string>&, const char*);
void printFreq(BST<std::string>& tree);

int main() {
  const char* file = "src/war_peace.txt";
  BST<std::string> tree;
  makeTree(tree, file);
  printFreq(tree);
  return 0;
}
