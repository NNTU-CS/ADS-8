// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    while (!file.eof()) {
        char ch = file.get();
        
        if (isalpha(ch) && isascii(ch)) {
            currentWord += tolower(ch);
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
    }
    
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    
    file.close();
}

static std::vector<std::pair<std::string, int>> wordFreq;

void collectWordStats(std::string word, int count) {
    wordFreq.emplace_back(word, count);
}

void printFreq(BST<std::string>& tree) {
    wordFreq.clear();
    
    tree.inOrder(collectWordStats);
    
    std::sort(wordFreq.begin(), wordFreq.end(), 
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    
    for (const auto& [word, count] : wordFreq) {
        std::cout << word << ": " << count << std::endl;
    }
    
    std::ofstream out("result/freq.txt");
    for (const auto& [word, count] : wordFreq) {
        out << word << ": " << count << std::endl;
    }
    out.close();
}
