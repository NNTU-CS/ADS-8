// Copyright 2021 NNTU-CS
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main(int argc, char* argv[]) {
  if (argc < 2) return 1;
  BST<std::string> tree;
  makeTree(tree, argv[1]);
  printFreq(tree);
  return 0;
}
