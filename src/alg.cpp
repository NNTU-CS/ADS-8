// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include "include/bst.h"
#include <cctype>
#include <string>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += std::tolower(static_cast<unsigned char>(ch));
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    file.close();
}
