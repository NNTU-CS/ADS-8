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
        std::cout << "Error opening file!" << std::endl;
        return;
    }

    std::string lastWord;
    std::string curtWord;
    char sm;

    while (file.get(sm)) {
        if (isalpha(sm)) {
            curtWord += tolower(sm);
        } else if (!curtWord.empty()) {
            if (curtWord != lastWord) {
                tree.insert(curtWord);
                lastWord = curtWord;
            }
            curtWord.clear();
        }
    }

    if (!curtWord.empty() && curtWord != lastWord) {
        tree.insert(curtWord);
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

void printFreq(const BST<std::string>& tree) {
    std::vector<BST<std::string>::Node*> nodes;

    tree.inorder([&nodes](auto* node) {
        nodes.push_back(node);
    });

    std::sort(nodes.begin(), nodes.end(), [](auto n1, auto n2) {
        return n1->kol > n2->kol;
    });

    for (auto* node : nodes) {
        std::cout << node->slovo << ": " << node->kol << "\n";
    }
}
