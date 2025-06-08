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

    // 1. Подсчёт частот слов
    std::map<std::string, int> freq;
    while (file >> word) {
        std::sregex_iterator it(word.begin(), word.end(), word_regex);
        std::sregex_iterator end;

        for (; it != end; ++it) {
            std::string clean = it->str();
            std::transform(clean.begin(), clean.end(), clean.begin(), ::tolower);
            freq[clean]++;
        }
    }

    // 2. Получаем отсортированный список слов
    std::vector<std::string> sorted_words;
    for (const auto& [word, _] : freq)
        sorted_words.push_back(word);

    // 3. Вставка в «ручном» сбалансированном порядке
    insertBalanced(sorted_words, 0, sorted_words.size() - 1, tree, freq);
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
