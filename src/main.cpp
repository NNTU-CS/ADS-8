// Copyright 2021 NNTU-CS
#include <iostream>
#include "alg.cpp"
#include "bst.h"

using namespace std;

int main() {
    BST<string> words;
    makeTree(words, "src/war_and_peace.txt");
    cout << "Tree constructed.\n";
    cout << "Maximum tree depth: " << words.depth() << endl;
    printFreq(words);
    cout << "Result saved in 'result/freq.txt'\n";
    return 0;
}
