// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  char c;
  while (file.get(c)) {
    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z')) {
      word.push_back(static_cast<char>(std::tolower(static_cast<unsigned char>(c))));
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
  tree.toVector(&freq);

  std::sort(
      freq.begin(),
      freq.end(),
      [](const std::pair<std::string, int>& a,
         const std::pair<std::string, int>& b) {
        if (a.second != b.second) {
          return a.second > b.second;
        }
        return a.first < b.first;
      });
  std::ofstream out("result/freq.txt");
  for (const auto& p : freq) {
    std::cout << p.first << " " << p.second << std::endl;
    out << p.first << " " << p.second << std::endl;
  }
  out.close();
}
