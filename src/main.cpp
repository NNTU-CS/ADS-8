// Copyright 2021 NNTU-CS
#include <iostream>
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
    Node<std::string>* found_node1 = word_tree.search(test_word1);
    if (found_node1) {
        std::cout << "Word \"" << test_word1 << "\" found with frequency: " << found_node1->count << std::endl;
    } else {
        std::cout << "Word \"" << test_word1 << "\" not found." << std::endl;
    }

    std::string test_word2 = "peace";
    Node<std::string>* found_node2 = word_tree.search(test_word2);
    if (found_node2) {
        std::cout << "Word \"" << test_word2 << "\" found with frequency: " << found_node2->count << std::endl;
    } else {
        std::cout << "Word \"" << test_word2 << "\" not found." << std::endl;
    }
    
    std::string test_word_nonexistent = "zubr";
    Node<std::string>* found_node3 = word_tree.search(test_word_nonexistent);
    if (found_node3) {
        std::cout << "Word \"" << test_word_nonexistent << "\" found with frequency: " << found_node3->count << std::endl;
    } else {
        std::cout << "Word \"" << test_word_nonexistent << "\" not found." << std::endl;
    }

    std::cout << "Program finished." << std::endl;

    return 0;
}
