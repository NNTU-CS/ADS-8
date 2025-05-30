// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include "bst.h"

int main() {
    BST<std::string> wordTree;
    const char* filename = "war_peace.txt";
    
    makeTree(wordTree, filename);
    
    std::ofstream outFile("result/freq.txt");
    if (outFile) {
        wordTree.printFreq(outFile);
        outFile.close();
    } else {
        std::cerr << "Could not open output file!" << std::endl;
    }
    
    std::cout << "Tree depth: " << wordTree.depth() << std::endl;
    return 0;
}
