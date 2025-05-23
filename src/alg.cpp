// Copyright 2021 NNTU-CS
//#include  <iostream>
//#include  <fstream>
//#include  <locale>
//#include  <cstdlib>
//#include <string>
#include  "bst.h"

#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>

std::string toLower(const std::string& str) {
    std::string result = "";
    for (char c : str) {
        result += std::tolower(c);
    }
    return result;
}

bool isLetter(char c) {
    return (c >= 'a' && c <= 'z');
}

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string word;
    std::string currentWord;
    char ch;

    while (file.get(ch)) {
        if (std::isalpha(ch)) { 
            currentWord += ch;
        }
        else {
            if (!currentWord.empty()) {
                tree.insert(toLower(currentWord));
                currentWord = "";
            }
        }
    }

    if (!currentWord.empty()) {
        tree.insert(toLower(currentWord));
    }

    file.close();
}


void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();

    std::sort(frequencies.begin(), frequencies.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
        });

    std::ofstream outputFile("freq.txt");
    if (!outputFile) {
        std::cerr << "Error opening result file!" << std::endl;
        return;
    }

    for (const auto& pair : frequencies) {
        std::cout << pair.first << " " << pair.second << std::endl;
        outputFile << pair.first << " " << pair.second << std::endl;
    }

    outputFile.close();
}
