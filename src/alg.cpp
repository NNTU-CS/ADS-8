// Copyright 2021 NNTU-CS
#include  <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <vector>
#include <sstream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <utility>
#include  "bst.h"

std::string toLower(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
}

void makeTree(BST<std::string>& tree, const char* filename) {std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string word;
        while (ss >> word) {
            word.erase(std::remove_if(word.begin(), word.end(), [](unsigned char c){
                return !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'));
            }), word.end());

            if (!word.empty()) {
                tree.insert(toLower(word));
            }
        }
    }

    file.close();
}


bool compareFrequencies(
const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
    return a.second > b.second;
}


void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();

    std::sort(frequencies.begin(), frequencies.end(), compareFrequencies);

    std::ofstream outfile("result/freq.txt");

    if (!outfile.is_open()) {
        std::cerr << "Error opening file result/freq.txt for writing!" << std::endl;
        return;
    }

    for (const auto& pair : frequencies) {
        std::cout << pair.first << ": " << pair.second << std::endl;
        outfile << pair.first << ": " << pair.second << std::endl;
    }

    outfile.close();
}

