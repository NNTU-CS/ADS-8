// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>
#include <utility>
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

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto elements = tree.getAllElements();

  std::sort(elements.begin(), elements.end(),
            [](const std::pair<std::string, int>& a,
               const std::pair<std::string, int>& b) {
              return b.second < a.second;
            });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cout << "Cannot open result/freq.txt" << std::endl;
    return;
  }

  for (const auto& [word, count] : elements) {
    std::cout << word << ": " << count << std::endl;
    out << word << ": " << count << std::endl;
  }

  out.close();
}

