// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
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

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freq;

  tree.inorder([&freq](auto node) {
    freq.emplace_back(node->key, node->count);
  });

  std::sort(freq.begin(), freq.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cerr << "Cannot open output file result/freq.txt" << std::endl;
    return;
  }

  for (const auto& p : freq) {
    std::cout << p.first << " " << p.second << std::endl;
    outFile << p.first << " " << p.second << std::endl;
  }

  outFile.close();
}
