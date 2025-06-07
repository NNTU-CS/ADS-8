// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <string>
#include  <algorithm>
#include  <locale>
#include  <cstdlib>
#include <utility>
#include <vector>
#include  "bst.h"

std::string toLower(const std::string& str) {
    std::string result = "";
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}
bool isValidLetter(char a) {
    return (a >= 'a' && a <= 'z');
}
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error" << std::endl;
        return;
    }
    std::string word;
    std::string currentWord;
    while (file.get(word[0])) {
        char c = word[0];
        if (std::isalpha(c)) {
            currentWord += c;
        } else {
            if (!currentWord.empty()) {
                tree.add(toLower(currentWord));
                currentWord.clear();
            }
        }
    }
    if (!Word.empty()) {
        tree.add(toLower(currentWord));
    }
    file.close();
}
bool compareFrequencies(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}
void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();
    std::sort(frequencies.begin(), frequencies.end(), compareFrequencies);
    std::ofstream outputFile("result/freq.txt");
    if (!outputFile.is_open()) {
        std::cerr << "Error while opening result file" << std::endl;
        return;
    }
    for (const auto& pair : frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outputFile << pair.first << ": " << pair.second << std::endl;
    }
    outputFile.close();
}
