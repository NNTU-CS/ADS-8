// Copyright 2021 NNTU-CS
#include <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <string>
#include <vector>
#include <algorithm>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error!" << std::endl;
        return;
    }
    std::string word;
    while (!file.eof()) {
        char ch = file.get();
        if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
        if (ch >= 'a' && ch <= 'z') {
            word += ch;
        } else {
            if (!word.empty())
              tree.add(word);
            word.clear();
        }
    }
    file.close();
}
