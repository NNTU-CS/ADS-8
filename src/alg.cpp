// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <utility>
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
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(ch);
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
  auto elements = tree.getAllElements();

  std::sort(elements.begin(), elements.end(),
            [](const auto& a, const auto& b) {
              return b.second < a.second;
            });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Cannot write result!" << std::endl;
    return;
  }

  for (const auto& pair : elements) {
    std::cout << std::setw(20) << std::left << pair.first << ": " << pair.second << std::endl;
    out << pair.first << ": " << pair.second << '\n';
  }

  out.close();
}
