// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <unordered_map>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "ERROR " << filename << std::endl;
        return;
    }

    std::string currentWord;
    char ch;
   while (file.get(ch)) {
        if (isalpha(ch)) {
            //currentWord += tolower(ch);
            currentWord += tolower(static_cast<unsigned char>(ch));

        }
        else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }


    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }


    file.close();
}


/*void makeMap(std::unordered_map<std::string, int>& freq, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "ERROR " << filename << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file.get(ch)) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
            word += std::tolower(static_cast<unsigned char>(ch));
        }
        else if (!word.empty()) {
            freq[word]++;
            word.clear();
        }
    }
    if (!word.empty()) freq[word]++;
}*/


void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> words;

    auto collector = [&words](BST<std::string>::Node* node) {
        words.emplace_back(node->key, node->count);
        };

    tree.inOrder(collector);

    std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    std::ofstream outfile("output.txt");
    if (!outfile) {
        std::cerr << "Ошибка при открытии файла для записи: " << "output.txt" << std::endl;
        return;
    }

    for (const auto& pair : words) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    for (const auto& pair : words) {
        outfile << pair.first << ": " << pair.second << std::endl;
    }
}


