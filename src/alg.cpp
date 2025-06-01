// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <cctype>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string word;
    int ch;

    while ((ch = file.get()) != EOF) {
        if (std::isalpha(ch)) {
            word += static_cast<char>(std::tolower(ch));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    tree.printToFileAndConsole();
}
