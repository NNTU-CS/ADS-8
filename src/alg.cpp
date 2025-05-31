// Copyright 2021 NNTU-CS
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Ошибка открытия файла: " << filename << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(ch)) {
      word += std::tolower(ch);
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }

  // Добавляем последнее слово, если оно есть
  if (!word.empty()) {
    tree.add(word);
  }

  file.close();
}
