// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <sstream>
#include  <fstream>
#include  <vector>
#include  <algorithm>
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

    std::string word;
    while (file >> word) {
        // Убираем все символы, кроме латинских букв
        std::string cleanedWord;
        for (char ch : word) {
            if (std::isalpha(ch)) {
                cleanedWord += std::tolower(ch);
            }
        }
        if (!cleanedWord.empty()) {
            tree.insert(cleanedWord);
        }
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freqList;

    std::function<void(Node<std::string>*)> collect = [&](Node<std::string>* node) {
        if (node) {
            collect(node->left);
            freqList.emplace_back(node->data, node->count);
            collect(node->right);
        }
    };

    collect(tree.root);

    std::sort(freqList.begin(), freqList.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::ofstream outFile("result/freq.txt");
    for (const auto& pair : freqList) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outFile << pair.first << ": " << pair.second << std::endl;
    }
    outFile.close();
}
