// Copyright 2021 NNTU-CS
#include "bst.h"

int main() {
  BST<std::string> wordTree;
  
  wordTree.insert("test");
  wordTree.insert("example");
  wordTree.insert("test");

  std::cout << "Depth: " << wordTree.depth() << std::endl;
  std::cout << "'test' count: " << wordTree.getCount("test") << std::endl;
  
  return 0;
}
