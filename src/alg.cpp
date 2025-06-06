// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "bst.h"

std::string toLowerCase(const std::string& str) {
    std::string result;
    for (char ch : str) {
        result += std::tolower(ch);
    }
    return result;
}

bool isAlphabetic(char ch) {
    return std::isalpha(ch);
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fileStream(filename);
    if (!fileStream) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string wordBuffer;
    char ch;
    while (fileStream.get(ch)) {
        if (isAlphabetic(ch)) {
            wordBuffer += std::tolower(ch);
        }
        else if (!wordBuffer.empty()) {
            tree.insert(wordBuffer);
            wordBuffer.clear();
        }
    }

    if (!wordBuffer.empty()) {
        tree.insert(wordBuffer);
    }

    fileStream.close();
}

void printFreq(const BST<std::string>& tree) {
    auto frequencyList = tree.get_frequencies();

    std::sort(frequencyList.begin(), frequencyList.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    std::ofstream outFile("freq.txt");
    if (!outFile) {
        std::cerr << "Unable to open output file!" << std::endl;
        return;
    }

    for (const auto& pair : frequencyList) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outFile << pair.first << " " << pair.second << std::endl;
    }

    outFile.close();
}
