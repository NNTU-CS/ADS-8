// Copyright 2021 NNTU-CS
#include "bst.h"
using namespace std;

void makeTree(BST<string>& tree, const char* filename);
void printFreq(BST<string>& tree);

int main() {
  BST<std::string> tree;
  const char* filename = "war_peace.txt";
  makeTree(tree, filename);
  printFreq(tree);
  return 0;
}
