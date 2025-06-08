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

    std::string tekuhSlovo;
    while (!file.eof()) {
        char ch = file.get();
        if (isalpha(ch)) {
            tekuhSlovo += tolower(ch);
        } else {
            if (!tekuhSlovo.empty()) {
                tree.insert(tekuhSlovo);
                tekuhSlovo.clear();
            }
        }
    }
    
    if (!tekuhSlovo.empty()) {
        tree.insert(tekuhSlovo);
    }
    
    file.close();
}


void printFreq(BST<std::string>& tree) {
    auto words = tree.inOrder();
    
    std::sort(words.begin(), words.end(), 
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    
    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Cannot create output file!" << std::endl;
        return;
    }
    
    for (const auto& pair : words) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outFile << pair.first << ": " << pair.second << std::endl;
    }
    
    outFile.close();
}
