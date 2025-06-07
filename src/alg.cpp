// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <string>
#include <vector>
#include <algorithm>
#include "bst.h"

namespace Alg {

void makeTree(BST<std::string> &tree, const char *filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening the file!\n";
        return;
    }

    std::string word;
    char c;
    while (file.get(c)) {
        if (isalpha(c)) {
            word += static_cast<char>(tolower(c));
        } else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }
    file.close();
}

void printFreq(BST<std::string> &tree) {
    std::ofstream output("result/freq.txt");
    if (output.fail()) {
        std::cerr << "Error writing to file!\n";
        return;
    }

    std::vector<Node<std::string> *> nodes;
    tree.inorder(nodes);
    std::sort(nodes.begin(), nodes.end(), [](const Node<std::string> *a, const Node<std::string> *b) {
        return a->count > b->count || (a->count == b->count && a->key < b->key);
    });

    for (auto n : nodes) {
        output << n->key << ": " << n->count << '\n';
    }
    output.close();
}
}  // namespace Alg
