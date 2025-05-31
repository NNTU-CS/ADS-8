// Copyright 2021 NNTU-CS
#include  <iostream>
#include <string>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
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
