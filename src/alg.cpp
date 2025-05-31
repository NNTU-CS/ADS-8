// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <string>

bool isLatinLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

char toLowerLatin(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Cannot open file: " << filename << "\n";
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
            word += toLowerLatin(ch);
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
    auto data = tree.getSortedByFrequency();

    std::ofstream fout("result/freq.txt");
    if (!fout.is_open()) {
        std::cerr << "Cannot write to result/freq.txt\n";
        return;
    }

    for (const auto& entry : data) {
        std::cout << entry.first << " " << entry.second << "\n";
        fout << entry.first << " " << entry.second << "\n";
    }

    fout.close();
}
