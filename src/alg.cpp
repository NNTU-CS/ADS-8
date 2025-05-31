// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
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
        if (std::isalpha(ch)) {
            word += std::tolower(ch);
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
    auto vec = tree.toVector();
    std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "Can't write to result/freq.txt" << std::endl;
        return;
    }

    for (const auto& [word, count] : vec) {
        std::cout << word << " — " << count << '\n';
        out << word << " — " << count << '\n';
    }

    out.close();
}
