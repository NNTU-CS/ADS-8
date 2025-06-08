// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "../include/bst.h"

void makeTree(BST<std::string>& bstInstance, const char* inputFile);
void printFreq(const BST<std::string>& bstInstance);

int main() {
  BST<std::string> wordTree;
  const char* sourceFile = "war_peace.txt";

  makeTree(wordTree, sourceFile);
  printFreq(wordTree);

  return 0;
}
