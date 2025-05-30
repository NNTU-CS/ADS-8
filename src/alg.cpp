// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream fileStream(filename);
    if (!fileStream) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string tempWord;
    char currentChar;
    while (fileStream.get(currentChar)) {
        if (isalpha(currentChar)) {
            tempWord += tolower(currentChar);
        } else if (!tempWord.empty()) {
            wordTree.insert(tempWord);
            tempWord.clear();
        }
    }
    if (!tempWord.empty()) {
        wordTree.insert(tempWord);
    }
    fileStream.close();
}

void printFreq(BST<std::string>& wordTree) {
    wordTree.printReverseInOrder();
}
