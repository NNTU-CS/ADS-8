// Copyright 2021 NNTU-CS
#include "bst.h"

#include <fstream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";

  makeTree(tree, filename);

  std::ofstream outFile("result/freq.txt");
  if (outFile) {
    tree.printReverseInOrder(outFile);
    outFile.close();
  }

  return 0;
}
