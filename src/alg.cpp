// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "bst.h"

// Populates the BST with words from a file
void makeTree(BST<std::string>& tree, const char* filename) {
  // Open the input file
  std::ifstream fileStream(filename);
  if (!fileStream.is_open()) {
    std::cerr << "Error: Could not open file " << filename << std::endl;
    return;
  }

  // Process file character by character
  std::string wordBuffer;
  char currentChar;
  while (fileStream.get(currentChar)) {
    if (std::isalpha(currentChar, std::locale())) {
      wordBuffer += std::tolower(currentChar, std::locale());
    } else if (!wordBuffer.empty()) {
      tree.insert(wordBuffer);
      wordBuffer.clear();
    }
  }

  // Insert the last word if present
  if (!wordBuffer.empty()) {
    tree.insert(wordBuffer);
  }

  // Explicitly close the file
  fileStream.close();
}

// Prints word frequencies from the BST
void printFreq(BST<std::string>& tree) {
  tree.printSortedByFrequency();
}
