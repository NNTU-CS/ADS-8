// Copyright 2021 NNTU-CS

#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }
    std::string tekuhSlovo;  // word → tekuhSlovo
    char c;
    while (fin.get(c)) {
        if (isalpha(static_cast<unsigned char>(c))) {
            tekuhSlovo.clear();
            do {
                tekuhSlovo += std::tolower(static_cast<unsigned char>(c));
            } while (fin.get(c) && isalpha(static_cast<unsigned char>(c)));
            tree.insert(tekuhSlovo);
        }
    }
    fin.close();
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.getAll();
    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            return a.second != b.second ? a.second > b.second : a.first < b.first;
        });
    for (const auto& p : words) {
        std::cout << p.first << " " << p.second << "\n";
    }
}
