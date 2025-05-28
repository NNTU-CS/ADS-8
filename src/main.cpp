// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);


int main() {
    BST<std::string> word_tree;

    const char* filename = "src/war_peace.txt";

    std::cout << "Processing file: " << filename << std::endl;

    makeTree(word_tree, filename);

    std::cout << "Tree has been built." << std::endl;

    std::cout << "Depth of the tree: " << word_tree.depth() << std::endl;

    printFreq(word_tree);

    std::string test_word1 = "war";
    int count1 = word_tree.search(test_word1); // search теперь возвращает int
    if (count1 > 0) {
        std::cout << "Word \"" << test_word1 << "\" found with frequency: " << count1 << std::endl;
    } else {
        std::cout << "Word \"" << test_word1 << "\" not found." << std::endl;
    }

    std::string test_word2 = "peace";
    int count2 = word_tree.search(test_word2); // search теперь возвращает int
    if (count2 > 0) {
        std::cout << "Word \"" << test_word2 << "\" found with frequency: " << count2 << std::endl;
    } else {
        std::cout << "Word \"" << test_word2 << "\" not found." << std::endl;
    }
    // Удален лишний пробел в конце следующей строки
    std::string test_word_nonexistent = "zubr";
    int count3 = word_tree.search(test_word_nonexistent); // search теперь возвращает int
    if (count3 > 0) {
        std::cout << "Word \"" << test_word_nonexistent << "\" found with frequency: " << count3 << std::endl;
    } else {
        std::cout << "Word \"" << test_word_nonexistent << "\" not found." << std::endl;
    }

    std::cout << "Program finished." << std::endl;

    return 0;
}
