// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <sstream>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(ch)) { 
            word += std::tolower(ch);
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}
void printFreq(BST<std::string>& tree) {
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error writing to file!" << std::endl;
        return;
    }
    tree.printFreq();
    outFile.close();
}
