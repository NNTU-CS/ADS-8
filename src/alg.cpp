// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
#include "bst.h"
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fin(filename);
    if (!fin) {
        throw std::runtime_error(std::string("Cannot open file: ") + filename);
    }
    std::string word;
    char c;
    while (fin.get(c)) {
        if (std::isalpha(static_cast<unsigned char>(c))) {
            word.clear();
            do {
                word += std::tolower(static_cast<unsigned char>(c));
            } while (fin.get(c) && std::isalpha(static_cast<unsigned char>(c)));
            if (!word.empty()) {
                tree.insert(word);
            }
        }
    }
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.getAll();
    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            return a.second != b.second ? a.second > b.second : a.first < b.first;
        });
    std::ofstream fout("result/freq.txt");
    if (!fout) {
        throw std::runtime_error("Cannot open output file: result/freq.txt");
    }
    for (const auto& [word, count] : words) {
        std::cout << word << " " << count << "\n";
        fout << word << " " << count << "\n";
    }
}
