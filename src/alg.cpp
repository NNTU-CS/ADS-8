// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
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
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
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
    std::vector<BST<std::string>::Node*> nodes;
    tree.inOrderTraversal(nodes);
    std::sort(nodes.begin(), nodes.end(),
        [](const auto& a, const auto& b) {
            return a->count > b->count;
        });
    std::ofstream out("result/freq.txt");
    for (const auto& node : nodes) {
        std::cout << node->key << ": " << node->count << "\n";
        out << node->key << ": " << node->count << "\n";
    }
    out.close();
}
