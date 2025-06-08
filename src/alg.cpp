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
      std::cout << "error" << std::endl;
      return;
  }
  std::string curWord;
  while (!file.eof()) {
      char ch1 = file.get();
      if (isalpha(ch1)) {
          curWord += tolower(ch1);
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
    auto words1 = tree.symBypass();
    std::sort(words1.begin(), words1.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& pair : words1) {
        std::cout << pair.first << " " << pair.second << std::endl;
        out << pair.first << " " << pair.second << std::endl;
    }
    out.close();
}
