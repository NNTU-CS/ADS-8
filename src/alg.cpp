// Copyright 2021 NNTU-CS
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>

#include "bst.h"

namespace {
    void processInputFile(std::ifstream& input_stream, BST<std::string>& word_tree) {
        std::string current_word;
        char current_char;
        
        while (input_stream.get(current_char)) {
            if (std::isalpha(static_cast<unsigned char>(current_char))) {
                current_word += static_cast<char>(std::tolower(current_char));
            } else if (!current_word.empty()) {
                word_tree.insert(current_word);
                current_word.clear();
            }
        }
        
        if (!current_word.empty()) {
            word_tree.insert(current_word);
        }
    }

    void writeFrequencyData(const std::vector<std::pair<std::string, int>>& word_frequencies) {
        std::ofstream output_file("result/freq.txt");
        for (const auto& entry : word_frequencies) {
            std::cout << entry.first << "\t" << entry.second << "\n";
            output_file << entry.first << "\t" << entry.second << "\n";
        }
    }
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream input_file(filename);
    if (!input_file) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    
    processInputFile(input_file, tree);
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequency_data;
    
    tree.traverseInOrder([&frequency_data](const std::string& word, int count) {
        frequency_data.emplace_back(word, count);
    });
    
    std::sort(frequency_data.begin(), frequency_data.end(),
        [](const auto& first, const auto& second) {
            return first.second > second.second;
        });
    
    writeFrequencyData(frequency_data);
}
