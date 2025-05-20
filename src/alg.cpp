// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string word;
  while (!file.eof()) {
    char ch = file.get();
    if (file.eof()) break;
    if (std::isalpha(static_cast<unsigned char>(ch), std::locale())) {
      word += std::tolower(ch, std::locale());
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
  sortFrequencies();
  std::ofstream fout("freq.txt");
  for (int i = 0; i < totalWords; ++i) {
    std::cout << frequencies[i].word << ": " << frequencies[i].count << std::endl;
    fout << frequencies[i].word << ": " << frequencies[i].count << std::endl;
  }
  fout.close();
}
