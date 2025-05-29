// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <string>
#include  <vector>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) std::cerr << "File error!";
  std::string word;
  while (!file.eof()) {
    char ch = file.get();
    if (('A' <= ch && ch <= 'Z') || ('a' <= ch && ch <= 'z')) {
      word.push_back(('A' <= ch && ch <= 'Z') ? ch + ('a' - 'A') : ch);
    } else if (!word.empty()) {
        tree.insert(word);
        word.clear();
    }
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> vec = tree.toVector();
  std::ofstream out("result/freq.txt");
  for (auto& pr : vec)
    out << pr.first << " " << pr.second << std::endl;
  out.close();
}
