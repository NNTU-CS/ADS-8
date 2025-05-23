// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <cctype>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }

    std::string word;
    char c;
    
    while (file.get(c)) {
        if (isalpha(c)) {
            word += tolower(c);
        } else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }
    
    if (!word.empty()) {
        tree.insert(word);
    }
}
