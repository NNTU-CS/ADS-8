// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <utility>
#include <string>
#include <vector>
#include <algorithm>
#include  "../include/bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream input_file(filename);
    if (!input_file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }
    std::string current_word;
    char ch;
    while (input_file.get(ch)) {
        if (std::isupper(static_cast<unsigned char>(ch))) {
            ch = std::tolower(static_cast<unsigned char>(ch));
        }
        if (std::islower(static_cast<unsigned char>(ch))) {
            current_word += ch;
        } else if (!current_word.empty()) {
            tree.add(current_word);
            current_word.clear();
        }
    }
    if (!current_word.empty()) {
        tree.add(current_word);
    }
    std::cout << tree.depth() << std::endl;
}

bool compareFrequencies(const std::pair<std::string, int>& a,
                       const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();
    std::sort(frequencies.begin(), frequencies.end(), compareFrequencies);
    std::ofstream outputFile("result/freq.txt");

    for (const auto& pair : frequencies) {
        std::cout << pair.first << " - " << pair.second << std::endl;
        outputFile << pair.first << " - " << pair.second << std::endl;
    }
}
