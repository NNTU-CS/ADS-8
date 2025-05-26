// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <string>
#include <algorithm>
#include <vector>
#include "bst.h"

bool isLatinLetter(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch)) && ch < 128;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
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
    std::vector<Node<std::string>*> nodes = tree.getNodes();
    std::sort(nodes.begin(), nodes.end(), [](Node<std::string>* a, Node<std::string>* b) {
        return a->count > b->count;
    });

    std::ofstream fout("result/freq.txt");
    for (auto node : nodes) {
        std::cout << node->key << " : " << node->count << std::endl;
        fout << node->key << " : " << node->count << std::endl;
    }
    fout.close();
}
