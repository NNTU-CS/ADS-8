// Copyright 2021 NNTU-CS
#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <algorithm>
#include "bst.h"

void build_word_tree(BinarySearchTree<std::string>& word_tree, const char* file_path) {
    std::ifstream input_file(file_path);
    if (!input_file) return;
    std::string current_word;
    char current_char;
    while (input_file.get(current_char)) {
        if (std::isalpha(static_cast<unsigned char>(current_char))) {
            current_word += std::tolower(static_cast<unsigned char>(current_char));
        } else if (!current_word.empty()) {
            word_tree.insert(current_word);
            current_word.clear();
        }
    }
    if (!current_word.empty()) {
        word_tree.insert(current_word);
    }
}

void display_frequencies(const BinarySearchTree<std::string>& word_tree) {
    auto word_list = word_tree.get_all_elements();
    std::sort(word_list.begin(), word_list.end(),
        [](const auto& item1, const auto& item2) {
            return item1.second != item2.second ?
                   item1.second > item2.second :
                   item1.first < item2.first;
        });
    for (const auto& [word, count] : word_list) {
        std::cout << word << " " << count << "\n";
    }
}
