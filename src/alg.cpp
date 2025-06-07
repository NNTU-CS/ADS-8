// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  <algorithm>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        } else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }
    if (!word.empty()) tree.insert(word);
    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto nodes = tree.getAllNodes();
    std::sort(nodes.begin(), nodes.end(), [](const auto& a, const auto& b) {
        return (a->count != b->count) ? (a->count > b->count) : (a->key < b->key);
    });

    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Error creating freq.txt" << std::endl;
        return;
    }

    for (const auto& node : nodes) {
        std::cout << node->key << ": " << node->count << std::endl;
        out << node->key << ": " << node->count << std::endl;
    }
    out.close();
}
