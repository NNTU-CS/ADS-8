// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string word;
    while (file >> word) {
        std::string cleaned;
        for (char c : word) {
            unsigned char uc = static_cast<unsigned char>(c);
            if (std::isalpha(uc)) {
                cleaned += std::tolower(uc);
            }
        }
        if (!cleaned.empty()) {
            tree.insert(cleaned);
        }
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> data = tree.inOrder();
    
    std::sort(data.begin(), data.end(), 
        [](const auto& a, const auto& b) {
            if (a.second != b.second) 
                return a.second > b.second;
            return a.first < b.first;
        }
    );
    
    std::ofstream outFile("result/freq.txt");
    if (!outFile.is_open()) {
        std::cerr << "Error opening result/freq.txt" << std::endl;
        return;
    }
    
    for (const auto& pair : data) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outFile << pair.first << " " << pair.second << std::endl;
    }
}
