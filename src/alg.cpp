// Copyright 2021 NNTU-CS
#include <algorithm>
#include <sys/stat.h>
#include <direct.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "bst.h"

static void EnsureResultDir() {
#ifdef _WIN32
    _mkdir("result");
#else
    mkdir("result", 0777);)
#endif
}

//------------------------------------------------------------------------------
// 1. Построение дерева из текстового файла
//------------------------------------------------------------------------------
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
            word += static_cast<char>(
                std::tolower(static_cast<unsigned char>(ch)));
        } else {
            if (!word.empty()) {
                tree.insert(word);
                word.clear();
            }
        }
    }
    if (!word.empty()) {  // последнее слово, если файл не закончился разделителем
        tree.insert(word);
    }
    file.close();
}

//------------------------------------------------------------------------------
// 2. Вывод слов по убыванию частоты + сохранение в result/freq.txt
//------------------------------------------------------------------------------
void printFreq(BST<std::string>& tree) {
    struct Rec {
        std::string word;
        int freq;
    };
    std::vector<Rec> data;

    tree.forEachInOrder([&](auto* node) {
        data.push_back({node->key, node->freq});
    });

    std::sort(data.begin(), data.end(), [](const Rec& a, const Rec& b) {
        return (a.freq != b.freq) ? (a.freq > b.freq) : (a.word < b.word);
    });

    // вывод на экран
    for (const auto& r : data) {
        std::cout << r.word << " : " << r.freq << '\n';
    }

    // сохранение в файл
    EnsureResultDir();
    std::ofstream out("result/freq.txt");
    for (const auto& r : data) {
        out << r.word << ' ' << r.freq << '\n';
    }
    // RAII-закрытие out при разрушении объекта
}
