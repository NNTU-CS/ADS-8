// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  <cctype>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    while (!file.eof()) {
        int ch = file.get();
        
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
    auto words = tree.inorder();
    
    std::sort(words.begin(), words.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::ofstream out("freq.txt");
    if (!out) {
        std::cout << "Cannot open output file!" << std::endl;
        return;
    }
    
    for (const auto& [word, count] : words) {
        std::cout << word << ": " << count << std::endl;
        out << word << ": " << count << std::endl;
    }
    
    out.close();
}
