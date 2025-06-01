// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Unable to open file \"" << filename << "\"." << std::endl;
        return;
    }

    std::string currentWord;
    char ch;
    while (inputFile.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
}

void displayFrequency(BST<std::string>& tree) {
    const std::string outputPath = "result/freq.txt";
    std::ofstream outputFile(outputPath);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Could not open output file \"" << outputPath << "\"." << std::endl;
        return;
    }

    tree.displayFrequency(outputFile);
    tree.displayFrequency(std::cout);
}
