// Copyright 2025 NNTU-CS
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "../include/bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(ch)) {
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
    std::vector<std::pair<std::string, int>> elements = tree.getAllElements();

    std::sort(elements.begin(), elements.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second;
              });

    std::ofstream outFile("result/freq.txt");
    for (const auto& pair : elements) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outFile << pair.first << ": " << pair.second << std::endl;
    }
    outFile.close();
}
