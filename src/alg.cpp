// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
#include <algorithm>
#include <vector>
#include <string>
#include <utility>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
      std::cout << "File error!" << std::endl;
      return;
  }
  std::string currentWord;
  while (!file.eof()) {
      char ch = file.get();
      if (isalpha(ch)) {
          currentWord += tolower(ch);
      } else {
        if (!currentWord.empty()) {
            tree.insert(currentWord);
            currentWord.clear();
        }
      }
  }
 
  if (!currentWord.empty()) {
      tree.insert(currentWord);
  }
  
  file.close();
}
