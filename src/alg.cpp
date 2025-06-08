// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fileStream(filename);
    if (!fileStream.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }
    std::string wordBuffer;
    char currentChar;
    while (fileStream.get(currentChar)) {
        if (isalpha(currentChar)) {
            wordBuffer += tolower(currentChar);
        }
        else if (!wordBuffer.empty()) {
            tree.insert(wordBuffer);
            wordBuffer.clear();
        }
    }
    if (!wordBuffer.empty()) {
        tree.insert(wordBuffer);
    }
    fileStream.close();
}
void inorderCollect(BST<std::string>::Node* node, std::vector<WordFreq>& vec) {
    if (!node) return;
    inorderCollect(node->left, vec);
    vec.emplace_back(node->key, node->count);
    inorderCollect(node->right, vec);
}
void printFreq(BST<std::string>& tree) {
    std::vector<WordFreq> words;
    inorderCollect(tree.getRoot(), words);
    std::sort(words.begin(), words.end(), [](const WordFreq& a, const WordFreq& b) {
        return b.freq < a.freq;
        });
    for (const auto& wf : words) {
        std::cout << wf.word << ": " << wf.freq << std::endl;
    }
    std::ofstream outfile("freq.txt");
    if (!outfile) {
        std::cerr << "Error: Failed to create freq.txt" << std::endl;
        return;
    }
    for (const auto& wf : words) {
        outfile << wf.word << ": " << wf.freq << std::endl;
    }
    outfile.close();
}
