// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>

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
        } else if (!currentWord.empty()) {
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
    
    auto collect = [&words](typename BST<std::string>::Node* node) {
        words.emplace_back(node->key, node->count);
    };
    
    tree.inOrder(collect);
    
    std::sort(words.begin(), words.end(), 
        [](const auto& a, const auto& b) {
            return a.second > b.second;
        });
    
    for (const auto& [word, count] : words) {
        std::cout << word << ": " << count << std::endl;
    }
    
    // Save to file
    std::ofstream out("result/freq.txt");
    for (const auto& [word, count] : words) {
        out << word << ": " << count << std::endl;
    }
    out.close();
}
