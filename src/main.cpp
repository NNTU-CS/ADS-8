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
  const char* filename = "https://github.com/malishev-danil/ADS-8/blob/bee66f0926fb93c7ad3a47a0d879178279d7440d/test/war_peace.txt";
  makeTree(tree, filename);
  printFreq(tree);
  return 0;
}
