// Copyright 2021 NNTU-CS
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include "bst.h"

bool isAsciiLetter(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}

char toLowerAscii(char ch) {
    return (ch >= 'A' && ch <= 'Z') ? ch + 32 : ch;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << '\n';
        return;
    }

    std::string currentWord;
    char ch;

    auto storeWord = [&]() {
        if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    };

    while (file.get(ch)) {
        if (isAsciiLetter(ch)) {
            currentWord += toLowerAscii(ch);
        } else {
            storeWord();
        }
    }
    storeWord();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, std::size_t>> entries;
    tree.inorder([&](const std::string& word, std::size_t freq) {
        entries.emplace_back(word, freq);
    });

    std::sort(entries.begin(), entries.end(),
              [](const auto& a, const auto& b) {
                  return (a.second == b.second)
                      ? a.first < b.first
                      : a.second > b.second;
              });

    std::ofstream output("result/freq.txt");
    if (!output.is_open()) {
        std::cerr << "Error: cannot write to result/freq.txt\n";
    }

    for (const auto& [word, freq] : entries) {
        std::cout << word << " : " << freq << '\n';
        if (output) {
            output << word << ' ' << freq << '\n';
        }
    }
}
