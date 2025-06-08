// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include <utility>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
      std::cout << "File error!" << std::endl;
      return;
  }
  std::string Word;
  while (!file.eof()) {
      char ch = file.get();
      if (isalpha(ch)) {
          Word += tolower(ch);
      } else {
        if (!Word.empty()) {
            tree.insert(Word);
            Word.clear();
        }
      }
  }
  if (!Word.empty()) {
      tree.insert(Word);
  }
  file.close();
}
void printFreq(BST<std::string>& tree) {
    auto words = tree.symBypass();
    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& pair : words) {
        std::cout << pair.first << " " << pair.second << std::endl;
        out << pair.first << " " << pair.second << std::endl;
    }
    out.close();
}
