// Copyright 2021 NNTU-CS
#include "alg.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    unsigned char uch = static_cast<unsigned char>(ch);
    if (uch == 0xC3) {
      char next;
      if (file.get(next)) {
        unsigned char unext = static_cast<unsigned char>(next);
        if (unext >= 0xA0 && unext <= 0xA6) currentWord += 'a';
      }
    } else if (std::isalpha(ch) && ch >= 0 && ch <= 127) {
      currentWord += std::tolower(ch);
    } else {
      if (!currentWord.empty()) {
        tree.insert(currentWord);
        currentWord.clear();
      }
    }
  }
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getByFrequency();
  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Error creating output file!" << std::endl;
    return;
  }
  bool first = true;
  for (const auto& pair : words) {
    if (!first) {
      std::cout << " ";
      outFile << " ";
    }
    std::cout << pair.first;
    outFile << pair.first;
    first = false;
  }
  std::cout << std::endl;
  outFile << std::endl;
  outFile.close();
}
