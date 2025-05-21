// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    return;
    }
  std::string word;
  while (true) {
    char ch = file.get();
    if (file.eof()) break;
    if ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) {
      if (ch >= 'A' && ch <= 'Z') {
        ch = ch + ('a' - 'A');
      }
      word += ch;
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}

struct WordFreq {
    std::string word;
    int count;
};


WordFreq frequencies[10000];

int totalWords = 0;

void collect(const std::string& word, int count) {
  if (totalWords < 10000) {
    frequencies[totalWords].word = word;
    frequencies[totalWords].count = count;
    totalWords++;
  }
}


void sortFrequencies() {
  for (int i = 0; i < totalWords - 1; ++i) {
    for (int j = 0; j < totalWords - 1 - i; ++j) {
      if (frequencies[j].count < frequencies[j + 1].count) {
        WordFreq temp = frequencies[j];
        frequencies[j] = frequencies[j + 1];
        frequencies[j + 1] = temp;
      }
    }
  }
}

void printFreq(BST<std::string>& tree) {
  totalWords = 0;
  tree.traverse(collect);
  sortFrequencies(); // Сортировка по убыванию частоты
}

