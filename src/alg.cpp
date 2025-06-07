// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include <cctype>
#include  <locale>
#include  <cstdlib>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(ch)) {
      word += std::tolower(ch);
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}


void printFreq(BST<std::string>& tree) {
  auto sortedWords = tree.getSortedByFrequency();

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cerr << "Error creating output file!" << std::endl;
    return;
  }

  for (const auto& pair : sortedWords) {
    //std::cout << pair.first << " -> " << pair.second << std::endl;
    outFile << pair.first << " -> " << pair.second << std::endl;
  }

  outFile.close();
}
