// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <algorithm>
#include <vector>
#include "bst.h"

static bool isLatinLetter(char c) {
    return std::isalpha(static_cast<unsigned char>(c)) && (c & 0x80) == 0;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!\n";
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
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
    auto nodes = tree.getNodes();
    std::sort(nodes.begin(), nodes.end(),
              [](auto a, auto b){ return a->count > b->count; });

    std::ofstream out("result/freq.txt");
    for (auto n : nodes) {
        std::cout << n->key << " : " << n->count << "\n";
        out << n->key << " : " << n->count << "\n";
    }
    out.close();
}