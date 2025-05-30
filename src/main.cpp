// Copyright 2021 NNTU-CS
#include "bst.h"
#include <fstream>

void makeTree(BST<std::string>& wordTree, const char* filename);
void printFreq(BST<std::string>& wordTree);

int main() {
    BST<std::string> frequencyTree;
    const char* novelFile = "war_peace.txt";

    makeTree(frequencyTree, novelFile);

    std::ofstream resultFile("result/freq.txt");
    if (resultFile) {
        frequencyTree.printReverseInOrder(resultFile);
        resultFile.close();
    }

    return 0;
}
