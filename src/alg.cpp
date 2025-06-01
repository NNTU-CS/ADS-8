// Copyright 2021 NNTU-CS
#include "../include/bst.h"
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (isalpha(ch)) {
            currentWord += tolower(ch);
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
    auto words = tree.inOrder();
    std::sort(words.begin(), words.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    for (const auto& pair : words) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    std::ofstream outFile("C:/Users/Артём/Desktop/project/result/freq.txt");
    if (!outFile) {
        std::cerr << "Could not open output file!" << std::endl;
        return;
    }
    for (const auto& pair : words) {
        outFile << pair.first << ": " << pair.second << std::endl;
    }
    outFile.close();
}
