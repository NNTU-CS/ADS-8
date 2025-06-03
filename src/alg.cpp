// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file.is_open()) return;

    char ch;
    std::string currentWord;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += std::tolower(static_cast<unsigned char>(ch));
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) tree.insert(currentWord);
}
