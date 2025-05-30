// Copyright 2021 NNTU-CS
#include "bst.h"
#include <string>
#include <fstream>
#include <locale>
#include <cstdlib>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    if (isalpha(ch)) {
      currentWord += tolower(ch);
    } else if (!currentWord.empty()) {
      tree.insert(currentWord);
      currentWord.clear();
    }
  }
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  tree.printReverseInOrder();
}
