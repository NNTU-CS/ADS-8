// Copyright 2021 NNTU-CS
#include "bst.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

bool isLatinLetter(char ch) {
    return std::isalpha(static_cast<unsigned char>(ch)) && ch < 128;
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    } else {
        std::cout << "File opened successfully: " << filename << std::endl;
    }

    std::string word;
    char ch;
    int insertedWords = 0;
    while (file.get(ch)) {
        if (isLatinLetter(ch)) {
            word += std::tolower(ch);
        } else if (!word.empty()) {
            tree.insert(word);
            insertedWords++;
            word.clear();
        }
    }
    if (!word.empty()) {
        tree.insert(word);
        insertedWords++;
    }
    file.close();

    std::cout << "Total words inserted: " << insertedWords << std::endl;
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

int main() {
    BST<std::string> tree;
    const char* filename = "../src/war_peace.txt";

    std::cout << "Loading file: " << filename << std::endl;
    makeTree(tree, filename);

    std::cout << "\nTree depth: " << tree.depth() << "\n";
    std::cout << "\nMost frequent words:\n";
    printFreq(tree);

    return 0;
}