// Copyright 2021 NNTU-CS
#include <utility>
#include <sstream>
#include  <iostream>
#include  <fstream>
#include <algorithm>
#include  <locale>
#include  <cstdlib>
#include <string>
#include <vector>
#include <cctype>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
      std::ifstream file(filename);
      std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            std::string processedWord = "";
            for (char c : word) {
                if (std::isalpha(c)) {
                    processedWord += std::tolower(c);
                }
            }

            if (!processedWord.empty()) {
                tree.insert(processedWord);
            }
        }
    }
    file.close();
}


void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getWordFrequencies();

    std::sort(frequencies.begin(), frequencies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::ofstream outfile("result/freq.txt");

    for (const auto& pair : frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outfile << pair.first << ": " << pair.second << std::endl;
    }

    outfile.close();
}

