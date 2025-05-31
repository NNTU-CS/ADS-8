// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (isalpha(ch)) {
            word += tolower(ch);
        } else if (!word.empty()) {
            tree.add(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        tree.add(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words;
    tree.getAllWords(words);

    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    std::ofstream fout("result/freq.txt");
    if (!fout) {
        std::cout << "Cannot create output file" << std::endl;
        return;
    }

    for (const auto& p : words) {
        std::cout << p.first << " " << p.second << std::endl;
        fout << p.first << " " << p.second << std::endl;
    }

    fout.close();
}
