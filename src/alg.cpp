// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "../include/bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
      std::cerr << "Ошибка: не удалось открыть файл!" << std::endl;
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
