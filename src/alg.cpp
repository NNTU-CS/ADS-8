// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include "bst.h"

namespace {

std::string to_lower(const std::string& str) {
    std::string lower_str;
    lower_str.reserve(str.size());
    for (const unsigned char c : str) {
        lower_str += std::tolower(c);
    }
    return lower_str;
}

bool is_letter(char c) {
    return std::isalpha(static_cast<unsigned char>(c));
}

}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (isLetter(ch)) {
            word += std::tolower(ch);
        } else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }

    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();

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
