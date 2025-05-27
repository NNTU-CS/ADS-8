// Copyright 2021 NNTU-CS
#include "../include/bst.h"
#include <iostream>
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

// Построение дерева из файла: слова в нижний регистр, только латиница
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "File error: cannot open " << filename << "\n";
        return;
    }

    std::string word;
    char ch;
    while (in.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word.push_back(static_cast<char>(std::tolower(ch)));
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

    in.close();
}

// Печать слов по убыванию частоты: в cout и в result/freq.txt
void printFreq(BST<std::string>& tree) {
    // Собираем все (слово, счёт) в вектор
    std::vector<std::pair<std::string,int>> freq;
    tree.traverseInOrder([&freq](const std::string& w, int c) {
        freq.emplace_back(w, c);
    });

    // Сортируем по убыванию счёта
    std::sort(freq.begin(), freq.end(),
              [](auto& a, auto& b) { return a.second > b.second; });

    // Вывод в консоль и в файл
    std::ofstream out("result/freq.txt");
    if (!out) {
        std::cerr << "File error: cannot open result/freq.txt for writing\n";
        return;
    }
    for (const auto& p : freq) {
        std::cout << p.first << "\t" << p.second << "\n";
        out << p.first << "\t" << p.second << "\n";
    }
}

