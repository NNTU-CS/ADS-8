// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "ERROR " << filename << std::endl;
        return;
    }

    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (isalpha(ch)) {
            currentWord += tolower(ch);
        }
        else if (!currentWord.empty()) {
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
    std::vector<std::pair<std::string, int>> words;

    auto collector = [&words](BST<std::string>::Node* node) {
        words.emplace_back(node->key, node->count);
        };

    tree.inOrder(collector);

    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    for (const auto& pair : words) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
}

