// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл " << filename << std::endl;
        return;
    }

    std::string current_word;
    file.get();
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(ch)) {
            current_word += std::tolower(ch);
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
    std::vector<std::pair<std::string, int>> freqVec;
    tree.getWordsAndFrequencies(freqVec);
    std::sort(freqVec.begin(), freqVec.end(), 
        [](const auto& a, const auto& b) {
            return a.second > b.second || (a.second == b.second && a.first < b.first);
        });
    for (const auto& item : freqVec) {
        std::cout << item.first << ": " << item.second << std::endl;
    }
    std::ofstream outfile("result/freq.txt");
    if (outfile) {
        for (const auto& item : freqVec) {
            outfile << item.first << ": " << item.second << std::endl;
        }
    }
    else {
        std::cerr << "Не могу открыть файл result/freq.txt для записи." << std::endl;
    }
}
