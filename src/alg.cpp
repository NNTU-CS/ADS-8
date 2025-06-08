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

}  // namespace

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "File error! Could not open: " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (is_letter(ch)) {
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
    std::vector<std::pair<std::string, int>> words = tree.getFrequencies();
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        if (a.second != b.second) return a.second > b.second;
        return a.first < b.first;
    });
    mkdir("result", 0777);
    std::ofstream fout("result/freq.txt");
    for (const auto& pr : words) {
        std::cout << pr.first << " " << pr.second << std::endl;
        if (fout) fout << pr.first << " " << pr.second << std::endl;
    }
    if (fout) fout.close();
}
