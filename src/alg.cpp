// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"
using namespace std;

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
        tree.insert(curWord);
       }
  }
  file.close();
}

void printPeriod(BST& tree) {
    auto words = tree.getAll();
    sort(words.begin(), words.end(),
        [](const auto& word1, const auto& word2) {
            if (word1.second != word2.second) {
                return word1.second > word2.second;
            } else {
                return word1.first < word2.first;
            }
        });
    for (const auto& pair : words) {
        cout << pair.first.c_str() << " " << pair.second << "\n";
    }
}
