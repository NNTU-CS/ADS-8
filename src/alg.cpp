// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <string>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else {
            if (!word.empty()) {
                tree.add(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.add(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto frequencies = tree.getFrequencies();
    std::sort(frequencies.begin(), frequencies.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second || (a.second == b.second && a.first < b.first);
              });

    std::ofstream output("result/freq.txt");
    if (!output) {
        std::cerr << "Error creating output file!" << std::endl;
        return;
    }

    for (const auto& entry : frequencies) {
        output << entry.first << ": " << entry.second << "\n";
    }
    output.close();
}
