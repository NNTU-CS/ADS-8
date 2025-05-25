// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: " << filename << "\n";
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
        else {
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
    auto vec = tree.toVector();

    std::sort(vec.begin(), vec.end(),
        [](auto& a, auto& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    std::ofstream fout("result/freq.txt");
    if (!fout) {
        std::cerr << "Cannot open result/freq.txt for writing\n";
        return;
    }

    for (auto& p : vec) {
        std::cout << p.first << " " << p.second << "\n";
        fout << p.first << " " << p.second << "\n";
    }
    fout.close();
}

