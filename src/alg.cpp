// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <algorithm>
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
    unsigned char uch = static_cast<unsigned char>(ch);
    if (std::isalpha(uch)) {
      word += std::tolower(uch);
    } else if (ch == '\'' && !word.empty()) {
      word += ch;
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getAllNodes();

  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    if (a.second == b.second) {
      return a.first < b.first;
    }
    return a.second > b.second;
  });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Output file error!" << std::endl;
    return;
  }

  for (const auto& [word, count] : words) {
    out << word << ": " << count << std::endl;
  }

  out.close();
}
