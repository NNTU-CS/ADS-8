// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
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
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.getAll(words);

  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });

  std::ofstream fout("result/freq.txt");
  for (const auto& [word, freq] : words) {
    std::cout << word << " " << freq << std::endl;
    if (fout) fout << word << " " << freq << std::endl;
  }
  fout.close();
}
