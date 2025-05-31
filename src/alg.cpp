// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error while file open: " << filename << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.add(word);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.collectAll(words);

  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });

  for (size_t i = 0; i < words.size(); ++i) {
    std::cout << words[i].first << ": " << words[i].second << '\n';
  }
}
