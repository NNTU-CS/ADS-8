// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

int main() {
  BST<std::string> Tree;
  std::cout << "Loadfile and buildtree\n";
  makeTree(Tree, "war_peace.txt");
  std::cout << "Print frequency analysis to console and save file\n";
  printFreq(Tree);
  std::cout << "Done.Result save result/freq.txt\n";
  int Count = Tree.search("pierre");
  std::cout << Count;
  return 0;
}
