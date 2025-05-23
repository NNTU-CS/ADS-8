// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* namefile) {
  std::ifstream LevTolstoyFile(namefile);
  if (!LevTolstoyFile.is_open()) {
    std::cerr << "Error: " << namefile << std::endl;
      return;
    }
  std::string words2 = "";
  char symbol;
  while (LevTolstoyFile.get(symbol)) {
    if(isalpha(symbol)){
      words2 += std::tolower(symbol);
    } else {
      if(!words2.empty()){
      tree.insert(words2);
      }
      words2 = "";
    }
  }
  if (!words2.empty()) {
    tree.insert(words2);
  }
  LevTolstoyFile.close();
}

void printFreq(BST<std::string>& tree) {
  tree.printInOrder();
}
