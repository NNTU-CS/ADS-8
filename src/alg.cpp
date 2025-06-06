// Copyright 2021 NNTU-CS
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  while (file >> word) {
    std::string cleanedWord;
    for (char ch : word) {
      if (std::isalpha(ch)) {
        cleanedWord += std::tolower(ch);
      }
    }
    if (!cleanedWord.empty()) {
      tree.insert(cleanedWord);
    }
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freqList;
  tree.inOrder(
      freqList);

  std::sort(
      freqList.begin(), freqList.end(),
      [](const std::pair<std::string, int>& a,
         const std::pair<std::string, int>& b) { return a.second > b.second; });

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Cannot open file!" << std::endl;
    return;
  }

  for (const auto& p : freqList) {
    std::cout << p.first << " : " << p.second << std::endl;
    outFile << p.first << " : " << p.second << std::endl;
  }

  outFile.close();
}
