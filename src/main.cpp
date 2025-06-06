// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include "bst.h"
using std::cout;
using std::endl;
using std::string;

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(const BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";
  makeTree(tree, filename);
  printFreq(tree);
  return 0;
}
