// Copyright 2021 NNTU-CS
#include  <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <utility>
#include  "bst.h"


void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
  if (!file) {
    std::cerr << "File ERR" << std::endl;
    return;
  }

  std::string cword;
  char cch;

  while (file.get(cch)) {
    if (std::isalpha(cch)) {
      cword += std::tolower(cch);
    } else if (!cword.empty()) {
      tree.insert(cword);
      cword.clear();
    }
  }

  if (!cword.empty()) {
    tree.insert(cword);
  }

  file.close();
}


void printFreq(BST<std::string>& tree) {
  auto words = tree.toVector();
  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });

  std::ofstream out("result/freq.txt");
  for (const auto& pair : words) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    out << pair.first << " - " << pair.second << std::endl;
  }
}
