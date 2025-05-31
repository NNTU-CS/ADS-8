// Copyright 2021 NNTU-CS
#include <fstream>
#include <string>
#include <cctype>
#include <iostream>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File ERR" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(const BST<std::string>& tree) {
  auto wordsVec = tree.toVector();
  std::sort(wordsVec.begin(), wordsVec.end(),
            [](const auto& a, const auto& b) {
              return a.second > b.second;
            });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cerr << "Ошибка открытия файла для записи result/freq.txt\n";
    return;
  }

  for (const auto& pair : wordsVec) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    out << pair.first << " - " << pair.second << std::endl;
  }
}
