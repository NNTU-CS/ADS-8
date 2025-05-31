// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>
#include <cctype>
#include <vector>
#include <algorithm>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "File error!" << std::endl;
        return;
    }

    std::string currentWord;
    while (!file.eof()) {
        char ch = file.get();
        
        if (isalpha(ch) && isascii(ch)) {
            currentWord += tolower(ch);
        } else {
            if (!currentWord.empty()) {
                tree.insert(currentWord);
                currentWord.clear();
            }
        }
    }
    
    if (!currentWord.empty()) {
        tree.insert(currentWord);
    }
    
    file.close();
}

struct WordFreq {
    std::string word;
    int count;
    
    bool operator<(const WordFreq& other) const {
        return count > other.count;
    }
};

void printFreq(BST<std::string>& tree) {
    std::vector<WordFreq> words;
    
    auto collect = [&words](BST<std::string>::Node* node) {
        words.push_back({node->key, node->count});
    };
    
    tree.inOrder(collect);
    
    std::sort(words.begin(), words.end());
    
    for (const auto& wf : words) {
        std::cout << wf.word << ": " << wf.count << std::endl;
    }

    std::ofstream out("result/freq.txt");
    for (const auto& wf : words) {
        out << wf.word << ": " << wf.count << std::endl;
    }
    out.close();
}
