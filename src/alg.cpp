// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
using std::cerr;
using std::cout;
using std::ifstream;
using std::sort;
using std::string;

void makeTree(BST& tree, const char* filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Cannot open file: " << filename << "\n";
    return;
  }
  MyString curWord;
  char ch;
  while (file.get(ch)) {
    if (isalpha(static_cast<unsigned char>(ch))) {
      curWord.clear();
      do {
        curWord.append(tolower(static_cast<unsigned char>(ch)));
      } while (file.get(ch) && isalpha(static_cast<unsigned char>(ch)));
      tree.addEl(curWord);
    }
  }
  file.close();
}

void printPeriod(BST& tree) {
  auto words = tree.getAllEl();
  sort(words.begin(), words.end(),
      [](const auto& lhs, const auto& rhs) {
        if (lhs.second != rhs.second) {
          return lhs.second > rhs.second;
        } else {
          return lhs.first < rhs.first;
        }
      });
  for (const auto& pair : words) {
    cout << pair.first.c_str() << " " << pair.second << "\n";
  }
}
