// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <string>
#include  <fstream>
#include  <vector>
#include  <algorithm>
#include  <locale>
#include  <cstdlib>
#include  <utility>
#include  "../include/bst.h"


void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word = "";
  int ch;

  while ((ch = file.get()) != EOF) {
    if (ch >= 'A' && ch <= 'Z') {
      ch += 'a' - 'A';
    }

    if (ch >= 'a' && ch <= 'z') {
      word += ch;
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
  std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();
  std::sort(frequencies.begin(), frequencies.end(), compareFrequencies);
  std::ofstream outputFile("result/freq.txt");

  if (!outputFile.is_open()) {
    std::cout << "Error opening result file!" << std::endl;
    return;
  }

  for (const auto& pair : frequencies) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    outputFile << pair.first << " - " << pair.second << std::endl;
  }

  outputFile.close();
}
