// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include  <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening the file." << std::endl;
        return;
    }

    std::string word;
    char ch;
    while (file >> std::noskipws >> ch) {
        if (std::isalpha(ch)) {
            word += tolower(ch);
        } else if (!word.empty()) {
            tree.insert(word);
            word.clear();
        }
    }
    if (!word.empty())
        tree.insert(word);

    file.close();
}

struct WordFrequencyPair {
    std::string word;
    int frequency;

    WordFrequencyPair(const std::string &w, int f) : word(w), frequency(f) {}

    bool operator<(const WordFrequencyPair &other) const {
        return this->frequency > other.frequency || (this->frequency == other.frequency && this->word < other.word);
    }
};

void collectWords(BST<std::string>& tree, std::vector<WordFrequencyPair>& words) {
    struct Helper {
        static void traverse(Node<std::string>* node, std::vector<WordFrequencyPair>& list) {
            if (node == nullptr) return;
            traverse(node->left, list);
            list.emplace_back(node->key, node->freq);
            traverse(node->right, list);
        }
    };
    Helper::traverse(tree.root, words);
}

void printFreq(BST<std::string>& tree) {
    std::vector<WordFrequencyPair> words;
    collectWords(tree, words);
    std::sort(words.begin(), words.end());

    for (auto& pair : words) {
        std::cout << pair.word << ": " << pair.frequency << "\n";
    }

    std::ofstream output("result/freq.txt");
    if (output.is_open()) {
        for (auto& pair : words) {
            output << pair.word << ": " << pair.frequency << "\n";
        }
        output.close();
    }
}
