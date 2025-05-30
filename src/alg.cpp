// Copyright 2021 NNTU-CS
#include "bst.h"
#include <cstdlib>
#include <cctype>
#include <locale>
#include <fstream>
#include <iostream>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      currentWord += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    } else if (!currentWord.empty()) {
      tree.insert(currentWord);
      currentWord.clear();
    }
  }
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
}

void printFreq(BST<std::string>& tree) {
  tree.printReverseInOrder();
}
