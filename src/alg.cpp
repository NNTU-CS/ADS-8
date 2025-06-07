// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* fname) {
    std::ifstream inp(fname);
    if (!inp) {
        std::cout << "Error!" << std::endl;
        return;
    }
    std::string tmp;
    char sym;
    while (inp.get(sym)) {
        if (sym >= 'A' && sym <= 'Z') sym += 32;
        if (sym >= 'a' && sym <= 'z') {
            tmp += sym;
        } else {
            if (tmp.length()) tree.add(tmp);
            tmp = "";
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
        std::cerr << "File is not open!" << std::endl;
        return;
    }
    for (auto& word : results) {
        std::cout << word.first << "-" << word.second << '\n';
        out << word.first << "-" << word.second << '\n';
    }
}
