// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

static bool IsAsciiLetter(char ch) {
  return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!\n";
    return;
  }
  std::string word;
  char ch;
  while (file.get(ch)) {
    if (IsAsciiLetter(ch)) {
      word.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    } else if (!word.empty()) {
      tree.Insert(word);
      word.clear();
    }
  }
  if (!word.empty()) tree.Insert(word);
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> data;
  tree.InOrder([&](auto* node) {
    data.emplace_back(node->key, node->count);
  });
  std::sort(data.begin(), data.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });
  std::ofstream out_file("result/freq.txt");
  for (const auto& [word, cnt] : data) {
    std::cout << word << ' ' << cnt << '\n';
    if (out_file) out_file << word << ' ' << cnt << '\n';
  }
}
