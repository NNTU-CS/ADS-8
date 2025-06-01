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
  if (!file.is_open()) {
    std::cerr << "File error!" << std::endl;
    exit(1);
  }
  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isupper(ch)) ch = std::tolower(ch);
    if (std::islower(ch)) {
      word += ch;
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
  file.close();
}

void printFreq(const BST<std::string>& tree) {
  auto words = tree.array_words();
  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
  std::ofstream file("result/freq.txt");
  if (!file.is_open()) {
    std::cerr << "Failed to open output file!" << std::endl;
    return;
  }
  for (const auto& pair : words) {
    std::cout << pair.first << "-" << pair.second << '\n';
    file << pair.first << "-" << pair.second << '\n';
  }
  file.close();
}
