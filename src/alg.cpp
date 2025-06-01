// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <cctype>
#include <utility>
#include <vector>
#include <algorithm>
#include "bst.h"

bool isAsciiLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char toLowerAscii(char ch) {
    return (ch >= 'A' && ch <= 'Z') ? ch + 32 : ch;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }
    std::string currentWord;
    char ch;
    auto storeWord = [&]() {
        if (!currentWord.empty()) {
            tree.add(currentWord);
            currentWord.clear();
        }
        };
    while (file.get(ch)) {
        if (isAsciiLetter(ch)) {
            currentWord += toLowerAscii(ch);
        }
        else {
            storeWord();
        }
    }
    storeWord();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> entries;
    tree.toVector(entries);
    std::sort(entries.begin(), entries.end(),
        [](const auto& a, const auto& b) {
            return (a.second == b.second)
                ? a.first < b.first
                : a.second > b.second;
        });
    std::ofstream output("freq.txt");
    if (!output.is_open()) {
        std::cerr << "Error: cannot write to freq.txt\n";
        return;
    }
    for (const auto& entry : entries) {
        const std::string& word = entry.first;
        int freq = entry.second;
        std::cout << word << " " << freq << '\n';
        output << word << ' ' << freq << '\n';
    }
}
