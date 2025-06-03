// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(ch) && ch >= 0 && ch <= 127) {
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
