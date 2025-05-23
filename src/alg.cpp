// Copyright 2021 NNTU-CS
#include <string>
#include <iostream> 
#include <algorithm>
#include <fstream>
#include <cctype>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) return;

  std::string word;
  char c;

  while (fin.get(c)) {
    if (isalpha(static_cast<unsigned char>(c))) {
      word.clear();
      do {
        word += std::tolower(static_cast<unsigned char>(c));
      } while (fin.get(c) && isalpha(static_cast<unsigned char>(c)));
      tree.insert(word);
    }
  }
  fin.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getAll();
  std::sort(words.begin(), words.end(),
    [](const auto& a, const auto& b) {
      return a.second != b.second ? a.second > b.second : a.first < b.first;
    });

  for (const auto& p : words) {
    std::cout << p.first << " " << p.second << "\n";
  }
}
  for (const auto& p : words) {
    std::cout << p.first << " " << p.second << "\n";
  }
}
