// Copyright 2021 NNTU-CS

#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream fin(filename);
  if (!fin) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string line;
  while (std::getline(fin, line)) {
    size_t i = 0;
    while (i < line.size()) {
      while (i < line.size() &&
             !std::isalpha(static_cast<unsigned char>(line[i]))) {
        ++i;
      }
      size_t start = i;
      while (i < line.size() &&
             std::isalpha(static_cast<unsigned char>(line[i]))) {
        line[i] = static_cast<char>(
            std::tolower(static_cast<unsigned char>(line[i])));
        ++i;
      }
      if (start < i) {
        std::string token = line.substr(start, i - start);
        tree.insert(token);
      }
    }
  }
  fin.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.getAll(words);
  std::sort(words.begin(), words.end());
  std::vector<std::pair<std::string, int>> sorted;
  sorted.reserve(words.size());
  for (auto& p : words) {
    sorted.push_back(p);
  }
  std::sort(sorted.begin(), sorted.end(), [](const auto& a, const auto& b) {
    if (a.second != b.second) return a.second > b.second;
    return a.first < b.first;
  });
  std::ofstream fout("result/freq.txt");
  for (const auto& pr : sorted) {
    std::cout << pr.first << " " << pr.second << std::endl;
    if (fout) fout << pr.first << " " << pr.second << std::endl;
  }
  if (fout) fout.close();
}
