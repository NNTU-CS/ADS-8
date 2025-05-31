// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    char ch;

    while (file.get(ch)) {
        if (isalpha(ch)) {
            currentWord += tolower(ch);
        } else if (!currentWord.empty()) {
            tree.add(currentWord);
            currentWord.clear();
        }
    }

    if (!currentWord.empty()) {
        tree.add(currentWord);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words;
    tree.getAll(words);

    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });

    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Cannot create output file" << std::endl;
        return;
    }

    for (const auto& pair : words) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outFile << pair.first << " " << pair.second << std::endl;
    }

    outFile.close();
}
