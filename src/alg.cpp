// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file.is_open()) return;
    char ch;
    std::string currentWord;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += std::tolower(static_cast<unsigned char>(ch));
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) tree.insert(currentWord);
}
void printFreq(BST<std::string, int>& tree) {
    std::vector<std::pair<std::string, int>> data = tree.inOrder();
    std::sort(data.begin(), data.end(), 
        [](const auto& a, const auto& b) {
            if (a.second != b.second) 
                return a.second > b.second;
            return a.first < b.first;
        }
    );
    std::ofstream outFile("result/freq.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening result/freq.txt" << std::endl;
        return;
    }
    for (const auto& pair : data) {
        outFile << pair.first << " " << pair.second << std::endl;
    }
}
