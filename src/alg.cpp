// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <cctype>
#include  <algorithm>
#include  <vector>
#include  <string>
#include  <utility>
#include  "bst.h"

void makeTree(bst<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
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
void printFreq(bst<std::string>& tree) {
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
