// Copyright 2021 NNTU-CS
#include <map>
#include <vector>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <locale>
#include <cstdlib>
#include <regex>
#include <algorithm>
#include <set>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    std::string word;
    std::regex word_regex("[a-zA-Z]+");

    std::vector<std::string> words;

    while (file >> word) {
        std::sregex_iterator it(word.begin(), word.end(), word_regex);
        std::sregex_iterator end;

        for (; it != end; ++it) {
            std::string clean = it->str();
            std::transform(clean.begin(), clean.end(), clean.begin(), ::tolower);
            words.push_back(clean);
        }
    }

    // Сортируем, чтобы получить перекошенное дерево
    std::sort(words.begin(), words.end());

    for (const auto& w : words)
        tree.insert(w);
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.toVector();

    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) {
            return a.second > b.second; // по убыванию частоты
        });

    std::ofstream out("result/freq.txt");
    for (const auto& [word, count] : words) {
        std::cout << word << ": " << count << '\n';
        out << word << ": " << count << '\n';
    }
}
