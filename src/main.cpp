// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "bst.h"

int main() {

    BST<std::string> tree;

    std::ifstream file("input.txt");


    if (!file.is_open()) {
        std::cerr << "Ne ydalos otkr fail" << std::endl;
        return 1;
    }


    std::string line, word;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        while (stream >> word) {
            tree.insert(word);
        }
    }
    file.close();

    tree.inOrder([](BST<std::string>::Node* node) {
        std::cout << node->key << " : " << node->count << std::endl;
        });

    std::cout << "Glubina Dereva: " << tree.depth() << std::endl;

    return 0;


}
