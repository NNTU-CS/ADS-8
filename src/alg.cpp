// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }
    std::string currentWord;
    while (!file.eof()) {
        char ch = file.get();
        if (isalpha(ch)) {
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
void printFreq(BST<std::string>& tree) {
    auto nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(), [](const auto& a, const auto& b) {
        return a->count > b->count;
    });
    for (const auto& node : nodes) {
        std::cout << node->key << " - " << node->count << std::endl;
    }
}
