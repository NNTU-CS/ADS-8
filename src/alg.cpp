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
      std::cout << "Error" << std::endl;
      return;
  }
  std::string curWord;
  while (!file.eof()) {
      char ch = file.get();
      if (isalpha(ch)) {
          curWord += tolower(ch);
      } else {
        if (!curWord.empty()) {
            tree.insert(curWord);
            curWord.clear();
        }
      }
  }
  if (!curWord.empty()) {
      tree.insert(curWord);
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
