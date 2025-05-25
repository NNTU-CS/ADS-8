// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
   std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            // Преобразование к нижнему регистру
            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            // Очистка от нелатинских символов
            word.erase(std::remove_if(word.begin(), word.end(), [](char c) {
                return !std::isalpha(c);
            }), word.end());

            if (!word.empty()) {
                tree.insert(word);
            }
        }
    }
    file.close();
}


void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getWordFrequencies();

    // Сортировка по убыванию частоты
    std::sort(frequencies.begin(), frequencies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    std::ofstream outfile("result/freq.txt");

    for (const auto& pair : frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outfile << pair.first << ": " << pair.second << std::endl;
    }

    outfile.close();
}

