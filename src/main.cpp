// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* fname) {
    std::ifstream inp(fname);
    if (!inp) {
        std::cout << "Error opening input file!" << std::endl;
        return;
    }
    std::string tmp;
    char sym;
    while (inp.get(sym)) {
        if (sym >= 'A' && sym <= 'Z') sym = sym - 'A' + 'a';
        if (sym >= 'a' && sym <= 'z') {
            tmp += sym;
        } else {
            if (!tmp.empty()) tree.add(tmp);
            tmp.clear();
        }
    }
}

void printFreq(const BST<std::string>& tree) {
    auto results = tree.words();
    std::sort(results.begin(), results.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second > b.second;
        });
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Error creating output file!" << std::endl;
        return;
    }
    for (const auto& w : results) {
        std::cout << w.first << "-" << w.second << '\n';
        out << w.first << "-" << w.second << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cout << "Usage: " << argv[0] << " <inputfile>" << std::endl;
        return 1;
    }
    BST<std::string> tree;
    makeTree(tree, argv[1]);
    printFreq(tree);
    return 0;
}
