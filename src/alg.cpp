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
  std::ofstream out("result/freq.txt");
  if (!out.is_open()) {
    std::cerr << "Ошибка: не удалось создать файл result/freq.txt" << std::endl;
    return;
  }
  tree.printInOrder(out);
  out.close();
}
