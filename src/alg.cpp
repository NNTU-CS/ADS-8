// Copyright 2021 NNTU-CS
#include "alg.h"
#include <cctype>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    char ch;
    while (file.get(ch)) {
        if (isalpha(ch)) {
            currentWord += tolower(ch);
        } else if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
    }

    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }

    file.close();
}

void printFreq(BST<std::string>& tree) {
    auto words = tree.inOrder();
    std::sort(words.begin(), words.end(),
        [](const auto& a, const auto& b) { return b.second < a.second; });

    std::ofstream out("result/freq.txt");
    for (const auto& [word, count] : words) {
        std::cout << word << " - " << count << std::endl;
        out << word << " - " << count << std::endl;
    }
    out.close();
}
