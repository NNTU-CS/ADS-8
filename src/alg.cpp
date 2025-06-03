// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream input_file(input_filename);
    if (!input_file.is_open()) {
        std::cerr << "Error opening input file: " << input_filename << std::endl;
        return;
    }

    std::string current_word;
    while (input_file >> current_word) {
        std::string cleaned_word;
        for (char character : current_word) {
            unsigned char unsigned_char = static_cast<unsigned char>(character);
            if (std::isalpha(unsigned_char)) {
                cleaned_word += std::tolower(unsigned_char);
            }
        }
        if (!cleaned_word.empty()) {
            word_tree.insert(cleaned_word);
        }
    }
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> word_frequencies = word_tree.getAllEntries();
    std::sort(word_frequencies.begin(), word_frequencies.end(),
        [](const auto& first_pair, const auto& second_pair) {
            if (first_pair.second != second_pair.second) 
                return first_pair.second > second_pair.second;
            return first_pair.first < second_pair.first;
        }
    );
    std::ofstream output_file("result/freq.txt");
    if (!output_file.is_open()) {
        std::cerr << "Error opening output file: freq.txt" << std::endl;
        return;
    }
    
    for (const auto& entry : word_frequencies) {
        std::cout << entry.first << " " << entry.second << std::endl;
        output_file << entry.first << " " << entry.second << std::endl;
    }
}
