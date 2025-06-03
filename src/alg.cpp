// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <cctype>
#include <string>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(static_cast<unsigned char>(ch));
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  // Insert the last word if file doesn't end with separator
  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

// Prints word frequencies sorted by count (descending) and alphabetically (ascending)
// Outputs to both console and "result/freq.txt" file
void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> elements;
  tree.getAll(elements);

  std::sort(elements.begin(), elements.end(),
    [](const auto& a, const auto& b) {
      if (a.second != b.second) {
        return a.second > b.second;
      }
      return a.first < b.first;
    });

  system("mkdir -p result");

  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cerr << "Error creating output file!" << std::endl;
    return;
  }
  
  for (const auto& pair : elements) {
    std::cout << pair.first << " " << pair.second << std::endl;
    outFile << pair.first << " " << pair.second << std::endl;
  }

  outFile.close();
}
