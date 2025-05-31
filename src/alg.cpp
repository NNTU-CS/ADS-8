// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <string>

void process(const std::string& filename, BST<std::string>& tree) {
    std::ifstream file(filename);
    std::string line, word;

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        while (iss >> word) {
            word.erase(std::remove_if(word.begin(), word.end(),
                [](unsigned char c) { return !std::isalpha(c); }),
                word.end());

            std::transform(word.begin(), word.end(), word.begin(), ::tolower);

            if (!word.empty()) {
                tree.insert(word);
            }
        }
    }
}
