// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"


void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  const char* inputFilename = "src/war_peace.txt";
  BST<std::string> wordTree;
  
  makeTree(wordTree, inputFilename);
  
  printFreq(wordTree);
  return 0;
}
