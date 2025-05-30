// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (isalpha(static_cast<unsigned char>(ch))) {
            word += tolower(static_cast<unsigned char>(ch));
        } else if (!word.empty()) {
            if (word.length() > 1 || (word[0] != 'a' && word[0] != 'i')) {
                tree.insert(word);
            }
            word.clear();
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.getAllNodes();

    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second;
        }
        return a.first < b.first;
    });

    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Output file error!" << std::endl;
        return;
    }

    for (const auto& pair : words) {
        out << pair.first << ": " << pair.second << std::endl;
    }

    out.close();
}
