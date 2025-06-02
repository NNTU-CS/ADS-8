// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "file error" << std::endl;
    return;
  }
  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    if (isalpha(ch)) {
      currentWord += tolower(ch);
    } else if (!currentWord.empty()) {
      tree.insert(currentWord);
      currentWord.clear();
    }
  }
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  tree.printFreq();
  std::ofstream outFile("freq.txt");
  if (outFile) {
    tree.printFreq(outFile);
    outFile.close();
  } else {
    std::cerr << "error opening output file" << std::endl;
  }
}
