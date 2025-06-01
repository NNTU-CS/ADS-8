// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include "bst.h"

extern const std::string RESULT_FILE = "result/freq.txt";

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: File not found" << std::endl;
        return;
    }
    std::string buffer;
    while (file >> buffer) {
        std::string word;
        for (char c : buffer) {
            char lower = std::tolower(c);
            if (std::isalpha(lower))
                word += lower;
        }
        if (!word.empty())
            tree.insert(word);
    }
}
void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freq_data;
    tree.getWordsAndFrequencies(freq_data);
    std::sort(freq_data.begin(), freq_data.end(),
        [](const auto& a, const auto& b) {
            return a.second != b.second ? a.second > b.second : a.first < b.first;
        });
    for (const auto& [word, count] : freq_data) {
        std::cout << word << ": " << count << std::endl;
    }
    std::ofstream fout(RESULT_FILE);
    if (fout.is_open()) {
        for (const auto& [word, count] : freq_data) {
            fout << word << ": " << count << std::endl;
        }
    }
}