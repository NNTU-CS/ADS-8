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
    bool in_word = false;

    while (file.get(ch)) {
        if (isalpha(static_cast<unsigned char>(ch))) {
            word += tolower(static_cast<unsigned char>(ch));
            in_word = true;
        } else if (in_word) {
            tree.insert(word);
            word.clear();
            in_word = false;
        }
    }

    if (in_word) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.getAllNodes();
    
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    });

    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Output file error!" << std::endl;
        return;
    }

    for (const auto& [word, count] : words) {
        out << word << ": " << count << std::endl;
    }

    out.close();
}
