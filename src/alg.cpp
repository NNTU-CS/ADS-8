// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <utility>

#include "bst.h"

bool compareFrequency(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    std::string current_word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            current_word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!current_word.empty()) {
                tree.insert(current_word);
                current_word.clear();
            }
        }
    }

    if (!current_word.empty()) {
        tree.insert(current_word);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> word_frequencies;
    tree.getWordFrequencies(word_frequencies);

    std::sort(word_frequencies.begin(), word_frequencies.end(), compareFrequency);

    std::cout << "Word Frequencies (Descending Order):" << std::endl;
    for (const auto& pair : word_frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    std::ofstream outfile("result/freq.txt");
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file result/freq.txt for writing." << std::endl;
        return;
    }

    outfile << "Word Frequencies (Descending Order):" << std::endl;
    for (const auto& pair : word_frequencies) {
        outfile << pair.first << ": " << pair.second << std::endl;
    }

    outfile.close();
    std::cout << "\nFrequencies also saved to result/freq.txt" << std::endl;
}
