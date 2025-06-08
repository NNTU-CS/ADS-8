// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << '\n';
        return;
    }

    std::string word;
    char c;
    while (file.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            word += std::tolower(c);
        }
        else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words;
    tree.collect(words);

    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    for (const auto& [word, count] : words) {
        std::cout << word << ": " << count << '\n';
    }
}
