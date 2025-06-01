// Copyright 2021 NNTU-CS
#include  <iostream>
#include <string>
#include  <fstream>
#include  <locale>
#include <algorithm>
#include <vector>
#include  <cstdlib>
#include  "bst.h"

bool latinLetter(char sm) {
    return (sm >= 'a' && sm <= 'z') || (sm >= 'A' && sm <= 'Z');
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error!" << std::endl;
        return;
    }

    std::string curtWord;
    char sm;

    while (file.get(sm)) {
        if (latinLetter(sm)) {
            curtWord += tolower(sm);
        } else if (!curtWord.empty()) {
            tree.addNode(curtWord);
            curtWord.clear();
        }
    }

    if (!curtWord.empty()) {
        tree.addNode(curtWord);
    }

    file.close();
}

struct WordFreq {
    std::string word;
    int kol;
};

bool compareWordFreq(const WordFreq& a, const WordFreq& b) {
    return a.kol > b.kol;
}

void printFreq(BST<std::string>& tree) {
    std::vector<WordFreq> words;
    
    tree.inorder([&words](const BST<std::string>::Node* node) {
        words.push_back({node->slovo, node->kol});
    });
    
    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.kol > b.kol;
    });
    
    for (const auto& wf : words) {
        std::cout << wf.word << ": " << wf.kol << std::endl;
    }
}
