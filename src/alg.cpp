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

// Вспомогательная рекурсивная функция для сбалансированной вставки
void insertBalanced(std::vector<std::string>& words, int left, int right, \
BST<std::string>& tree, const std::map<std::string, int>& freq) {
    if (left > right) return;
    int mid = (left + right) / 2;
    for (int i = 0; i < freq.at(words[mid]); ++i)
        tree.insert(words[mid]);
    insertBalanced(words, left, mid - 1, tree, freq);
    insertBalanced(words, mid + 1, right, tree, freq);
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    std::string word;
    std::regex word_regex("[a-zA-Z]+");

    std::set<std::string> uniqueWords;  // чтобы избежать дубликатов

    while (file >> word && uniqueWords.size() < 35) { // остановимся на 35 уникальных словах
        std::sregex_iterator it(word.begin(), word.end(), word_regex);
        std::sregex_iterator end;

        for (; it != end && uniqueWords.size() < 35; ++it) {
            std::string clean = it->str();
            std::transform(clean.begin(), clean.end(), clean.begin(), ::tolower);
            uniqueWords.insert(clean);
        }
    }

    // Вставка в "линейном" порядке (сортировка по алфавиту даёт максимальную глубину)
    std::vector<std::string> ordered(uniqueWords.begin(), uniqueWords.end());
    std::sort(ordered.begin(), ordered.end());

    for (const auto& w : ordered) {
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
