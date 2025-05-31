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
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    char ch;

    while (file.get(ch)) {
        if (isalpha(static_cast<unsigned char>(ch))) {
            currentWord += tolower(static_cast<unsigned char>(ch));
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
    std::vector<std::pair<std::string, int>> wordFrequencies;
    tree.getAllWords(wordFrequencies);

    std::sort(wordFrequencies.begin(), wordFrequencies.end(),
        [](const auto& a, const auto& b) {
            if (a.second != b.second)
                return a.second > b.second;
            return a.first < b.first;
        });

    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Cannot create output file" << std::endl;
        return;
    }

    for (const auto& pair : wordFrequencies) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outFile << pair.first << " " << pair.second << std::endl;
    }

    outFile.close();
}
