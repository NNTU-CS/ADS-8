// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cctype>
#include <cstdlib>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error: cannot open " << filename << '\n';
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word.push_back(std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {
        tree.insert(word);
    }
    file.close();
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> vec;
    tree.inorder([&](auto node) {
        vec.emplace_back(node->key, node->count);
    });

    std::sort(vec.begin(), vec.end(),
              [](auto& a, auto& b) {
                  return a.second > b.second;
              });

    std::ofstream ofs("result/freq.txt");
    for (auto& p : vec) {
        std::cout << p.first << ' ' << p.second << '\n';
        if (ofs) ofs << p.first << ' ' << p.second << '\n';
    }
    if (ofs) ofs.close();
}