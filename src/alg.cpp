// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
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
  std::vector<std::pair<std::string, int>> words = tree.array_words();
  std::sort(words.begin(), words.end(), [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
  });
  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Cannot create output file!" << std::endl;
    return;
  }
  for (const auto& pair : words) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    outFile << pair.first << " - " << pair.second << std::endl;
  }
  outFile.close();
}
