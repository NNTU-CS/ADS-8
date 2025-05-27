// Copyright 2021 NNTU-CS
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/bst.h"
#include "../include/bst.h"
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include "../include/bst.h"
#include <cctype>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) return;
    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            currentWord += std::tolower(static_cast<unsigned char>(ch));
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
void printFreq(BST<std::string>& tree) {
    auto elements = tree.getAll();
    std::sort(elements.begin(), elements.end(),
              [](const auto& a, const auto& b) {
                  return a.second > b.second || (a.second == b.second && a.first < b.first);
              });
    std::ofstream outFile("result/freq.txt");
    for (const auto& pair : elements) {
        std::cout << pair.first << " " << pair.second << std::endl;
        if (outFile) outFile << pair.first << " " << pair.second << std::endl;
    }
    outFile.close();
}
