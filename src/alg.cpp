// Copyright 2021 NNTU-CS
#include  <iostream>
#include <string>
#include  <fstream>
#include  <locale>
#include <algorithm>
#include <vector>
#include  <cstdlib>
#include  "bst.h"


bool isLatinLetter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Ошибка открытия файла!\n";
        return;
    }

    std::string currentWord;
    char symbol;

    while (file.get(symbol)) {
        if (isLatinLetter(symbol)) {
            currentWord += tolower(symbol);
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear(); // очищаем буфер
        }
    }

    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }

    file.close();
}

struct WordFrequency {
    std::string word;
    int frequency;
};

bool compareByFrequency(const WordFrequency& wf1, const WordFrequency& wf2) {
    return wf1.frequency > wf2.frequency;
}

void printFreq(const BST<std::string>& tree) {
    std::vector<WordFrequency> frequencies;

    tree.inorder([&frequencies](const typename BST<std::string>::Node* node) {
        frequencies.emplace_back(WordFrequency{node->slovo, node->kol});
    });

    std::sort(frequencies.begin(), frequencies.end(), compareByFrequency);

    std::ofstream output("result/freq.txt");
    if (!output.is_open()) {
        std::cerr << "Ошибка записи результата\n";
        return;
    }

    for (const auto& freq : frequencies) {
        output << freq.word << ": " << freq.frequency << '\n';
    }

    output.close();
}
