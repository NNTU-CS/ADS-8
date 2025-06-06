// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "bst.h"

bool isLetter(char c) {
    return std::isalpha(static_cast<unsigned char>(c));
}

void buildWordTree(BST<std::string>& tree, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
        return;
    }

    std::string currentWord;
    char ch;

    while (file.get(ch)) {
        if (isLetter(ch)) {
            currentWord += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }

    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.get_frequencies();

    std::sort(frequencies.begin(), frequencies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    std::ofstream outputFile("freq.txt");
    if (!outputFile) {
        std::cerr << "Error opening result file!" << std::endl;
        return;
    }
    for (const auto& pair : frequencies) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    outputFile.close();
}
