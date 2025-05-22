// Copyright 2021 NNTU-CS
#include "main.h"

#include <iostream>
#include <string>

#include "alg.h"

int main() {
  BST<std::string> tree;
  makeTree(tree, "src/war_peace.txt");
  printFreq(tree);
  return 0;
}
