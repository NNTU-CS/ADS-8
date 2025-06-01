// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }
  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.add(word);
  }
}

void printFreq(BST<std::string>& tree) {
  auto data = tree.getAll();
  std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  std::ofstream out("result/freq.txt");
  for (const auto& [word, count] : data) {
    std::cout << word << ": " << count << std::endl;
    out << word << ": " << count << std::endl;
  }
  out.close();
}

