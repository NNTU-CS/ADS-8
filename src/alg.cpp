// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  while (!file.eof()) {
    char ch = file.get();
    if (isalpha(ch)) {
      currentWord += tolower(ch);
    } else {
      if (!currentWord.empty()) {
        tree.insert(currentWord);
        currentWord.clear();
      }
    }
  }

  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto words = tree.inOrder();

  std::sort(words.begin(), words.end(),
    [](const std::pair<std::string, int>& a,
    const std::pair<std::string, int>& b) {
      return a.second > b.second;
    });

  for (const auto& pair : words) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  std::ofstream out("result/freq.txt");
  for (const auto& pair : words) {
    out << pair.first << ": " << pair.second << std::endl;
  }
  out.close();
}
