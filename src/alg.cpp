// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <string>
#include  <vector>
#include  <locale>
#include  <cstdlib>
#include  <utility>
#include  <algorithm>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;

  std::string word = "";
  int character;
  while ((character = file.get()) != EOF) {
    if (character >= 'A' && character <= 'Z') {
      character += 'a' - 'A';
    }

    if (character >= 'a' && character <= 'z') {
      word += character;
    } else {
      if (!word.empty()) {
        tree.add(word);
      }
      word = "";
    }
  }
  if (!word.empty()) {
    tree.add(word);
  }

  file.close();
  std::cout << tree.depth();
}

bool compareFrequencies(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
  return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> frequencies = tree.getFreqs();
  std::sort(frequencies.begin(), frequencies.end(), compareFrequencies);
  std::ofstream outputFile("result/freq.txt");
  if (!outputFile.is_open()) return;
  
  for (const auto& pair : frequencies) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    outputFile << pair.first << " - " << pair.second << std::endl;
  }
  outputFile.close();
}
