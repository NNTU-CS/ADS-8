// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream fin(filename);
    if (!fin.is_open()) {
      std::cerr << "Cant open file: " << filename << "\n";
      return;
    }
    char c;
    bool in_word = false;
    std::string word;
    while (fin.get(c)) {
      if (std::isalpha(static_cast<unsigned char>(c))) {
        word += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        in_word = true;
      }
      else if (in_word) {
        if (!word.empty()) {
          tree.add(word);
          word.clear();
        }
        in_word = false;
      }
    }
    if (!word.empty()) {
      tree.add(word);
    }
    fin.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.getAll(words);
  std::sort(words.begin(), words.end(),
    [](const auto& a, const auto& b) {
      return (a.second != b.second) ? a.second > b.second : a.first < b.first;
    });
    for (const auto& p : words) {
      std::cout << p.first << " " << p.second << "\n";
    }
    std::ofstream fout("result/freq.txt");
    if (fout.is_open()) {
      for (const auto& p : words) {
        fout << p.first << " " << p.second << "\n";
      }
      fout.close();
    }
    else {
      std::cerr << "Cant create output file\n";
    }
}
