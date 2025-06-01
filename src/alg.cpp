// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <string>
#include  "bst.h"
void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream inputFile(filename);
  if (!inputFile.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
  return;
  }

  std::string currentWord;
  char ch;
  while (inputFile.get(ch)) {
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
  inputFile.close();
}

void printFreq(BST<std::string>& tree) {
  tree.printSortedByFrequency();
}
