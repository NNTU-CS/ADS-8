// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);

    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += std::tolower(static_cast<unsigned char>(ch));
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto items = tree.getAll();
    std::sort(items.begin(), items.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });

    std::ofstream outFile("result/freq.txt");
    for (const auto& item : items) {
        std::cout << item.first << ": " << item.second << std::endl;
        if (outFile) {
            outFile << item.first << ": " << item.second << std::endl;
        }
    }
    outFile.close();
}
