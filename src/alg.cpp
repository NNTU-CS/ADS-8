// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <cctype>   
#include <algorithm>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Ошибка: Не найден файл для анализа!" << std::endl;
        return;
    }

    std::string current_word{};
    char current_char;
    while (file.get(current_char)) {
        if (std::isalpha(current_char)) {
            current_word.push_back(std::tolower(current_char));
        } else {
            if (!current_word.empty()) {
                tree.insert(current_word.c_str());
                current_word.clear();
            }
        }
    }
    if (!current_word.empty()) 
        tree.insert(current_word);
    
    file.close();
}

void printFreq(BST<std::string>& tree) {

    std::vector<std::pair<std::string, int>> items;
    tree.getWordsAndFrequencies(items);
    std::sort(items.begin(), items.end(), 
        [](const auto& a, const auto& b) {
            return (a.second > b.second) || 
                (a.second == b.second && a.first < b.first);
        }
    );
    std::ofstream out("result/freq.txt");
    
    for (const auto& pair : items) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        out << pair.first << ": " << pair.second << std::endl;
    }

    if (out) out.close();
}
