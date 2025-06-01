// Copyright 2021 NNTU-CS
#include "../include/bst.h"

#include <fstream>
#include <locale>
#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>
#include <algorithm>


void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }
  std::string word;
  while (file) {
    char ch = file.get();
    if (isupper(ch)) ch = tolower(ch);
    if (islower(ch)) {
      word += ch;
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
}
void printFreq(const BST<std::string>& tree) {
  auto words = tree.array_words();
  std::sort(words.begin(), words.end(),
    [](const auto& a, const auto& b) { return a.second > b.second; });
  std::ofstream file("C:/Users/Артём/Desktop/project/result/freq.txt");
  if (!file) {
    std::cerr << "Failed to open output file!" << std::endl;
    return;
  }
  for (const auto& pair : words) {
    std::cout << pair.first << "-" << pair.second << '\n';
    file << pair.first << "-" << pair.second << '\n';
  }
}
