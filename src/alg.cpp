// Copyright 2021 NNTU-CS
##include <cctype>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream in(filename);
  if (!in) return;

  std::string word;
  char ch;
  while (in.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word.push_back(static_cast<char>(std::tolower(ch)));
    } else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) tree.insert(word);
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freq;
  tree.traverseInOrder([&](const std::string& w, int c) {
    freq.emplace_back(w, c);
  });

  std::sort(freq.begin(), freq.end(),
            [](auto& a, auto& b) { return a.second > b.second; });

  std::ofstream out("result/freq.txt");
  for (auto& p : freq) {
    std::cout << p.first << "\t" << p.second << "\n";
    out << p.first << "\t" << p.second << "\n";
  }
}
