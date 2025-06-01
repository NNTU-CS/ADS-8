// Copyright 2021 NNTU-CS
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include  "bst.h"


void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }
    std::string word;
    while (!file.eof()) {
        char ch = file.get();
        if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
        if (ch >= 'a' && ch <= 'z') {
            word += ch;
        } else {
            if (!word.empty()) {
                tree.add(word);
            }
            word.clear();
        }
    }
    file.close();
}

void printFreq(const BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words = tree.array_words();
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) { return a.second > b.second; });
    std::ofstream file("result/freq.txt");
    if (!file.is_open()) {
        std::cerr << "File is not open!" << std::endl;
        return;
    }
    for (const auto& pair : words) {
        std::cout << pair.first << "-" << pair.second << '\n';
        file << pair.first << "-" << pair.second << '\n';
    }
    file.close();
}
