// Copyright 2021 NNTU-CS
#include <string>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream fileStream(filename);
  if (!fileStream.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  std::string wordBuffer;
  char currentChar;
  while (fileStream.get(currentChar)) {
    if (isalpha(currentChar)) {
        wordBuffer += tolower(currentChar);
    } else if (!wordBuffer.empty()) {
        tree.insert(wordBuffer);
        wordBuffer.clear();
    }
  }
  if (!wordBuffer.empty()) {
    tree.insert(wordBuffer);
  }
  fileStream.close();
}

void printFrequency(BST<std::string>& tree) {
    tree.printSortedByFrequency();
}
