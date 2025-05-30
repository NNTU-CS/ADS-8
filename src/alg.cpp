// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  <cctype>
#include  <algorithm>
#include  <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File opening error!" << std::endl;
    return;
  }
  std::string word;
  int ch;
  while ((ch = file.get()) != EOF) {
    if (std::isalpha(ch)) {
      word += static_cast<char>(std::tolower(ch));
    } else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
  if (!word.empty())
    tree.add(word);
  file.close();
}
void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> result;
  tree.getSorted(result);
  std::ofstream outFile("result/freq.txt");
  for (const auto& pair : result) {
    std::cout << pair.first << ": " << pair.second << std::endl;
    outFile << pair.first << " " << pair.second << std::endl;
  }
  outFile.close();
}
