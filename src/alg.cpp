// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <cctype>
#include <iomanip>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += static_cast<char>(std::tolower(ch));
        } else if (!word.empty()) {
            tree.add(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        tree.add(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> wordList;
    tree.toVector(wordList);
    std::sort(wordList.begin(), wordList.end(), [](const auto& a, const auto& b) {
        return (a.second > b.second) || (a.second == b.second && a.first < b.first);
        });
    for (const auto& entry : wordList) {
        std::cout << entry.second << " " << entry.first << std::endl;
    }
    std::ofstream fout("freq.txt");
    if (!fout) {
        std::cout << "Can't open freq.txt" << std::endl;
        return;
    }
    for (const auto& entry : wordList) {
        fout << entry.second << " " << entry.first << "\n";
    }
    fout.close();
}
