// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(ch)) {
            word += std::tolower(ch);
        } else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }

    file.close();
}
void printFreq(BST<std::string>& tree) {
    
    std::vector<std::pair<std::string, int>> freqVec;

    std::sort(freqVec.begin(), freqVec.end(),
              [](const auto& a, const auto& b) { return a.second > b.second; });

    std::ofstream os("result/freq.txt");
    for (const auto& pair : freqVec) {
        os << pair.first << ": " << pair.second << std::endl;
        std::cout << pair.first << ": " << pair.second << std::endl;
    }
    os.close();
}
