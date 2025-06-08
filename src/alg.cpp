// Copyright 2021 NNTU-CS

#include  "bst.h"

#include <fstream>
#include <cctype>
#include <algorithm>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }

    std::vector<std::string> words;
    std::string tekuhSlovo;
    
    while (!file.eof()) {
        char ch = file.get();
        if (isalpha(ch)) {
            tekuhSlovo += tolower(ch);
        } else {
            if (!tekuhSlovo.empty()) {
                words.push_back(tekuhSlovo);
                tekuhSlovo.clear();
            }
        }
    }
    
    if (!tekuhSlovo.empty()) {
        words.push_back(tekuhSlovo);
    }
    
    file.close();

    std::sort(words.begin(), words.end());
    words.erase(std::unique(words.begin(), words.end()), words.end());
    
    for (const auto& word : words) {
        tree.insert(word);
    }
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.inOrder();
    std::sort(words.begin(), words.end(), 
        [](const auto& a, const auto& b) { return a.second > b.second; });
    
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Cannot create output file!" << std::endl;
        return;
    }
    
    for (const auto& [word, count] : words) {
        std::cout << word << ": " << count << std::endl;
        outFile << word << ": " << count << std::endl;
    }
}
