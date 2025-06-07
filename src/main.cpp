// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* fname);
void printFreq(const BST<std::string>& tree);

int main() {
  BST<std::string> freqTree;
  const char* file = "war_peace.txt";
  makeTree(freqTree, file);
  printFreq(freqTree);
  return 0;
}
