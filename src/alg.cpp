// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include <sys/stat.h>
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

void printFreq(const BST<std::string>& tree) {
    // Use getFrequencies() instead of toVector()
    std::vector<std::pair<std::string, int>> words = tree.getFrequencies();
    
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    // Create directory if it doesn't exist
    mkdir("result", 0777);
    
    std::ofstream file("result/freq.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to create output file!" << std::endl;
        return;
    }
    
    for (const auto& pair : words) {
        std::cout << pair.first << " - " << pair.second << '\n';
        file << pair.first << " - " << pair.second << '\n';
    }
    file.close();
}
