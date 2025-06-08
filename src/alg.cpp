// Copyright 2021 NNTU-CS
#include  "bst.h"
#include <string>
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <regex>
#include <algorithm>
#include <vector>


void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    std::string word;
    std::regex word_regex("[a-zA-Z]+");

    while (file >> word) {
        std::sregex_iterator it(word.begin(), word.end(), word_regex);
        std::sregex_iterator end;

        for (; it != end; ++it) {
            std::string clean_word = it->str();
            std::transform(clean_word.begin(), clean_word.end(), \
                clean_word.begin(), ::tolower);
            tree.insert(clean_word);
        }
    }
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
