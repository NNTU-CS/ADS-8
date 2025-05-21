// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Cannot open file: " << filename << "\n";
    return;
  }
  std::string word;
  char c;

  while (fin.get(c)) {
    if (isalpha(static_cast<unsigned char>(c))) {
      word.clear();
      while (fin && isalpha(static_cast<unsigned char>(c))) {
        word += std::tolower(static_cast<unsigned char>(c));
        fin.get(c);
      }
      tree.insert(word);
    }
  }
  fin.close();
}
void printFreq(BST<std::string>& tree) {
  auto words = tree.getAll();

  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });

  for (const auto& p : words) {
    std::cout << p.first << " " << p.second << "\n";
  }
}
