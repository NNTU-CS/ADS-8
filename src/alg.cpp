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

bool isValid(char ch) {
    return (ch >= 'a' && ch <= 'z');
}

std::string toLower(const std::string& str) {
    std::string result = "";
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }
    std::string word;
    std::string currentWord;
    while (file.get(word[0])) {
        char ch = word[0];
        if (std::isalpha(ch)) {
            currentWord += ch;
        }
        else {
            if (!currentWord.empty()) {
                tree.add(toLower(currentWord));
                currentWord.clear();
            }
        }
    }
    if (!currentWord.empty()) {
        tree.add(toLower(currentWord));
    }
    file.close();
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
