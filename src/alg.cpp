// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream input_file(filename);
    if (!input_file) {
        std::cerr << "File error: " << filename << std::endl;
        return;
    }
    std::string current_word;
    char ch;

    while (input_file.get(ch)) {
        if (std::isupper(static_cast<unsigned char>(ch))) {
            ch = std::tolower(static_cast<unsigned char>(ch));
        }
        if (std::islower(static_cast<unsigned char>(ch))) {
            current_word += ch;
        } else if (!current_word.empty()) {
            tree.add(current_word);
            current_word.clear();
        }
    }
    if (!current_word.empty()) {
        tree.add(current_word);
    }
    std::cout << "Tree depth: " << tree.depth() << std::endl;
}

bool compareFrequencyPairs(const std::pair<std::string, int>& a, 
                          const std::pair<std::string, int>& b) {
    return a.second > b.second;
}

void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> freq_list = tree.getFrequencies();
    std::sort(freq_list.begin(), freq_list.end(), compareFrequencyPairs);
    
    std::ofstream output_file("result/freq.txt");
    if (!output_file) {
        std::cerr << "Error creating output file" << std::endl;
        return;
    }

    for (const auto& [word, count] : freq_list) {
        std::cout << word << " - " << count << "\n";
        output_file << word << " - " << count << "\n";
    }
}
