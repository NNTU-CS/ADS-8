// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <cctype>
#include <string>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
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
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    for (const auto& node : nodes) {
        std::cout << node.first << " " << node.second << std::endl;
    }
}
