// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* fi_name) {
    std::ifstream fi(fi_name);
    if (!fi.is_open()) {
        return;
    }
    std::string currentWord;
    char ch;
    while (fi.get(ch)) {
        if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z')) {
            if (ch >= 'A' && ch <= 'Z') {
                currentWord += (ch - 'A' + 'a');
            } else {
                currentWord += ch;
            }
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
    fi.close();
}
void printFreq(BST<std::string>& tree) {
    auto words = tree.getWordsByFrequency();
    std::ofstream outFile("result/freq.txt");
    if (!outFile.is_open()) {
        return;
    }    for (const auto& pair : words) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outFile << pair.first << " " << pair.second << std::endl;
    }
    outFile.close();
}