// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <string>
#include  <cstdlib>
#include  <vector>
#include <algorithm>
#include "../include/bst.h"

void collectWords(BST<std::string>& tree, std::vector<WordFrequencyPair>& words) {
    BST<std::string>::Helper::traverse(tree.root, words);
}

void printFreq(BST<std::string>& tree) {
    std::vector<WordFrequencyPair> words;
    collectWords(tree, words);
    std::sort(words.begin(), words.end());

    for (auto& pair : words) {
        std::cout << pair.word << ": " << pair.frequency << '\n';
    }

    std::ofstream out("result/freq.txt");
    if (out.is_open()) {
        for (auto& pair : words) {
            out << pair.word << ": " << pair.frequency << '\n';
        }
        out.close();
    }
}

