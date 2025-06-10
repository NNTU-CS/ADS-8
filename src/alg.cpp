// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Cannot open file: " << filename << "\n";
    return;
  }
  std::string curWord;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      curWord.clear();
      do {
        curWord += std::tolower(static_cast<unsigned char>(ch));
      } while (file.get(ch) && std::isalpha(static_cast<unsigned char>(ch)));
      tree.addEl(curWord);
    }
  }
  file.close();
}

void printPeriod(BST<std::string>& tree) {
  auto words = tree.getAllEl();
  std::sort(words.begin(), words.end(),
      [](const auto& lhs, const auto& rhs) {
        if (lhs.second != rhs.second) {
          return lhs.second > rhs.second;
        } else {
          return lhs.first < rhs.first;
        }
      });
  for (const auto& pair : words) {
    std::cout << pair.first << " " << pair.second << "\n";
  }
}
