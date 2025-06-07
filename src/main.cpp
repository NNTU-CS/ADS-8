// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>
#include "bst.h"

int main() {
    BST<std::string> words;
    makeTree(words, "src/war_and_peace.txt");
    std::cout << "Tree constructed.\n";

    std::cout << "Maximum tree depth: " << words.depth() << '\n';

    printFreq(words);
    std::cout << "Result saved in 'result/freq.txt'\n";

    return 0;
}
