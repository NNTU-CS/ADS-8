// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <vector>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) return;
  std::locale loc;
  std::string word;
  char c;
  while (file.get(c)) {
    if (std::isalpha(c, loc)) {
      word += std::tolower(c, loc);
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

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string,int>> vec;
  tree.getAll(vec);
  std::sort(vec.begin(), vec.end(), [](auto& a, auto& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });
  std::ofstream out("result/freq.txt");
  for (auto& p : vec) {
    out << p.first << " " << p.second << "\n";
  }
}
