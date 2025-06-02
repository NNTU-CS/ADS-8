// Copyright 2021 NNTU-CS
#include "bst.h"
#include <string>
#include <fstream>
#include <sstream>
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
        if (std::isalpha(ch)) {
            currentWord += std::tolower(ch);
        } else if (!currentWord.empty()) {
            tree.addNode(currentWord);
            currentWord.clear();
        }
    }
    if (!currentWord.empty()) {
        tree.addNode(currentWord);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto* root = tree.getRoot();
    
    std::vector<std::pair<std::string, int>> wordCounts;
    std::stack<BST<std::string>::Node*> stack;
    BST<std::string>::Node* current = root;
    
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        
        current = stack.top();
        stack.pop();
        wordCounts.emplace_back(current->value, current->count);
        current = current->right;
    }

    std::sort(wordCounts.begin(), wordCounts.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });

    std::ofstream outFile("result/freq.txt");
    if (!outFile) {
        std::cerr << "Error: Could not open file 'result/freq.txt'\n";
        return;
    }

    for (const auto& [word, count] : wordCounts) {
        std::cout << word << " " << count << "\n";
        outFile << word << " " << count << "\n";
    }
}
