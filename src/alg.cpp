// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
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

bool compareNodes(const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words;
    
    auto collectWords = [&words](BST<std::string>::Node* node) {
        words.emplace_back(node->key, node->count);
    };
    
    tree.inOrder(collectWords);
    
    std::sort(words.begin(), words.end(), compareNodes);
    
    for (const auto& pair : words) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    
    std::ofstream out("result/freq.txt");
    for (const auto& pair : words) {
        out << pair.first << ": " << pair.second << std::endl;
    }
    out.close();
}
}
