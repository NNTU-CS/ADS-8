// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  // поместите сюда свой код
  std::ifstream file(filename);
  if (!file) return;

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) tree.insert(word);
  file.close();
}

void printFreq(const BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words = tree.array_words();
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    std::ofstream file("result/freq.txt");
    if (!file.is_open()) {
        std::cerr << "File is not open!" << std::endl;
        return;
    }
    for (const auto& pair : words) {
        std::cout << pair.first << "-" << pair.second << '\n';
        file << pair.first << "-" << pair.second << '\n';
    }
    file.close();
}
