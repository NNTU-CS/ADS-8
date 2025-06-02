// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string word;
        char symbol;

        while (file.get(symbol)) {
            if (std::isalpha(symbol)) {
                word += std::tolower(static_cast<unsigned char>(symbol));
            } else {
                if (!word.empty()) {
                    tree.addNode(word);
                    word.clear();
                }
            }
        }

        if (!word.empty()) {
            tree.addNode(word);
        }

        file.close();
    } else {
        std::cout << "File was not read correctly." << std::endl;
    }
}
