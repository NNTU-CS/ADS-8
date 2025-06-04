// Copyright 2021 NNTU-CS
#include <cstdlib>
#include <fstream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";

  makeTree(tree, filename);

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    return EXIT_FAILURE;
  }
  tree.printReverseInOrder(outFile);
  return EXIT_SUCCESS;
}
