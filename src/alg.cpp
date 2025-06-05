// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <cctype>
#include  <algorithm>
#include  <vector>
#include <utility>
#include <string>
#include  "bst.h"

void printFreq(BST<std::string>& tree) {
  auto elems = tree.toVector();
  std::sort(elems.begin(), elems.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      if (a.second != b.second)       return a.second > b.second;
      return a.first < b.first;
    });
  std::ofstream ofs("result/freq.txt");
  for (const auto& p : elems) {
    ofs << p.first << " " << p.second << std::endl;
  }
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream ifs(filename);
  if (!ifs) return;

  std::string word;
  char c;
  while (ifs.get(c)) {
    if (std::isalpha((unsigned char)c)) {
      word += std::tolower((unsigned char)c);
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

  printFreq(tree);
}
