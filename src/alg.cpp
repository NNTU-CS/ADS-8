// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
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
        if (std::isalpha(ch)) {
            currentWord += std::tolower(ch);
        } else if (!currentWord.empty()) {
            tree.add(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        tree.add(currentWord);
    }
}

void printFreq(const BST<std::string>& tree) {
    auto wordCounts = tree.getWordsWithCounts();
    std::sort(wordCounts.begin(), wordCounts.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error: Could not open file 'result/freq.txt'\n";
        return;
    }

    for (const auto& [word, count] : wordCounts) {
        std::cout << word << " " << count << "\n";
        outFile << word << " " << count << "\n";
    }
}
