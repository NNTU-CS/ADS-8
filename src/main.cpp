// Copyright 2021 NNTU-CS
// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void printFreq(const BST<std::string>& tree) {
  auto words = tree.toVector();
  for (const auto& pair : words) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }
}

int main() {
  const char* filename = "src/war_peace.txt";
  BST<std::string> tree;

  makeTree(tree, filename);

  std::cout << "Total unique words: " << tree.count() << std::endl;
  std::cout << "Tree max depth: " << tree.depth() << std::endl;
  std::cout << "Word frequencies:\n";
  printFreq(tree);

  return 0;
}
