// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (isalpha(ch) && isascii(ch)) {
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
    auto items = tree.getAllItems();
    
    std::sort(items.begin(), items.end(),
        [](const auto& a, const auto& b) {
            return b.second < a.second;
        });

    std::ofstream out("result/freq.txt");
    for (const auto& [word, count] : items) {
        std::cout << word << ": " << count << std::endl;
        out << word << ": " << count << std::endl;
    }
    out.close();
}
