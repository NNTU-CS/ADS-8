// Copyright 2021 NNTU-CS
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include "bst.h"
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) tree.insert(word);
  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.toVector();
  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });
  fs::create_directory("result");
  std::ofstream out("result/freq.txt");
  for (const auto& pair : words) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    out << pair.first << " - " << pair.second << std::endl;
  }
}
