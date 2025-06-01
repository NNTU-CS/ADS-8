// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z') {
            word += ch + 32;
        } else if (ch >= 'a' && ch <= 'z') {
            word += ch;
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto items = tree.getItems();
    std::sort(items.begin(), items.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& [word, count] : items) {
        out << word << ": " << count << "\n";
    }
    out.close();
}
