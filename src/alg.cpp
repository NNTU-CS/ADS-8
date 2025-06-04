// Copyright 2021 NNTU-CS
#include "bst.h"
#include <cctype>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

/// ------------------------------------------------------------------
/// 1. Построение дерева из текстового файла
/// ------------------------------------------------------------------
void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename, std::ios::in | std::ios::binary);
    if (!file) {
        std::cerr << "File error: cannot open " << filename << '\n';
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
            word += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
        else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) tree.insert(word);   // последнее слово
    file.close();
}

/// ------------------------------------------------------------------
/// 2. Печать слов в порядке убывания частоты + сохранение в файл
/// ------------------------------------------------------------------
void printFreq(BST<std::string>& tree) {
    // 1) собрать всё из дерева
    struct Rec { std::string word; int freq; };
    std::vector<Rec> data;
    tree.forEachInOrder([&](auto* node) {
        data.push_back({node->key, node->freq});
    });

    // 2) сортировка по freq &darr;, если равны… по алфавиту &uarr;
    std::sort(data.begin(), data.end(),
        [](const Rec& a, const Rec& b) {
            if (a.freq != b.freq) return a.freq > b.freq;
            return a.word < b.word;
        });

    // 3) вывод на экран
    for (auto& r : data)
        std::cout << r.word << " : " << r.freq << '\n';

    // 4) сохранить в result/freq.txt
    fs::create_directories("result");
    std::ofstream out("result/freq.txt");
    for (auto& r : data)
        out << r.word << ' ' << r.freq << '\n';
    out.close();
}
