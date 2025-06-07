// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include <cctype>
#include  <locale>
#include  <cstdlib>
#include <string>
#include <random>
#include <vector>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  std::vector<std::string> words;

  while (file.get(ch)) {
    if (std::isalpha(ch)) {
      word += std::tolower(ch);
    } else {
      if (!word.empty()) {
        words.push_back(word);
        word.clear();
      }
    }
  }

  if (!word.empty()) {
    words.push_back(word);
  }

  file.close();

  std::random_device rd;
  std::mt19937 g(rd());
  std::shuffle(words.begin(), words.end(), g);

  for (const auto& w : words) {
    tree.insert(w);
  }
}

void printFreq(BST<std::string>& tree) {
  auto sortedWords = tree.getSortedByFrequency();

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cerr << "Error creating output file!" << std::endl;
    return;
  }

  for (const auto& pair : sortedWords) {
    //std::cout << pair.first << " -> " << pair.second << std::endl;
    outFile << pair.first << " -> " << pair.second << std::endl;
  }

  outFile.close();
}
