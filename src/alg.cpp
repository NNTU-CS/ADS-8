// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(bst::BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += static_cast<char>(std::tolower(ch));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }
}

void printFreq(bst::BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words = tree.toVector();

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              return b.second < a.second;
            });

  std::ofstream fout("result/freq.txt");

  for (const auto& [word, count] : words) {
    std::cout << word << ": " << count << '\n';
    fout << word << ": " << count << '\n';
  }

  fout.close();
}
