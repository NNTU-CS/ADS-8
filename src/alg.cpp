// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "../include/bst.h"

void makeTree(BST<std::string> &tree, const char *filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл!" << std::endl;
    return;
  }
  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else {
      if (!word.empty()) {
        tree.add(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.add(word);
  }
  file.close();
}

void printFreq(BST<std::string> &tree) {
  auto words = tree.getAllWords();

  std::sort(words.begin(), words.end(), [](const auto &a, const auto &b) {
    return a.second > b.second || (a.second == b.second && a.first < b.first);
  });
  std::ofstream out("result/freq.txt");
  if (!out.is_open()) {
    std::cerr << "Ошибка: не удалось создать файл result/freq.txt" << std::endl;
    return;
  }

  for (const auto &[word, count] : words) {
    out << word << " " << count << '\n';
  }
  out.close();

  for (const auto &[word, count] : words) {
    std::cout << word << ": " << count << '\n';
  }
}
