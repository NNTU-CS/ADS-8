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
    if (std::isalpha(static_cast<unsigned char>(ch)) && ch < 128) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    std::cout << "[" << word << "]" << std::endl;
    tree.insert(word);
    word.clear();
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.getAllNodes();

  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Output file error!" << std::endl;
    return;
  }

  for (const auto& [word, count] : words) {
    std::cout << word << ": " << count << std::endl;
    out << word << ": " << count << std::endl;
  }

  out.close();
}
