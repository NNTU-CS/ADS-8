// Copyright 2021 NNTU-CS
#include <iostream>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> freqTree;
  const char* filename = "src/war_peace.txt";
  makeTree(freqTree, filename);
  printFreq(freqTree);
  return 0;
}
