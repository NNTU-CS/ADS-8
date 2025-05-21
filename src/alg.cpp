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
  while (!file.eof()) {
    char ch = file.get();
    if (file.eof()) break;
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(ch);
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

#define MAX_WORDS 10000

struct WordFreq {
    std::string word;
    int count;
};

WordFreq frequencies[MAX_WORDS];
int freqSize = 0;

void collect(const std::string& word, int count) {
  if (freqSize < MAX_WORDS) {
    frequencies[freqSize].word = word;
    frequencies[freqSize].count = count;
    freqSize++;
  }
}

void sortFrequencies() {
  for (int i = 0; i < freqSize - 1; ++i) {
    for (int j = 0; j < freqSize - i - 1; ++j) {
      if (frequencies[j].count < frequencies[j + 1].count) {
        WordFreq temp = frequencies[j];
        frequencies[j] = frequencies[j + 1];
        frequencies[j + 1] = temp;
      }
    }
  }
}
void printFreq(BST<std::string>& tree) {
  freqSize = 0;
  tree.traverse(collect);
  sortFrequencies();
  std::ofstream fout("freq.txt");
  for (int i = 0; i < freqSize; ++i) {
    std::cout << frequencies[i].word << ": " << frequencies[i].count << std::endl;
    fout << frequencies[i].word << ": " << frequencies[i].count << std::endl;
  }
  fout.close();
}
