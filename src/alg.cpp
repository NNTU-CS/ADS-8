// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <algorithm>
#include <string>
#include <vector>
#include "bst.h"


void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }
  std::string currentWord;
    char ch;
    while (file.get(ch)) {
      if (isalpha(static_cast<unsigned char>(ch))) {
        currentWord += tolower(static_cast<unsigned char>(ch));
      } else {
          if (!currentWord.empty() && currentWord.length() > 1) {
            auto it = std::find_if(wordCounts.begin(), wordCounts.end(), [&](const auto& pair) { return pair.first == currentWord; });
            if (it != wordCounts.end()) {
              it->second++;
            } else {
              wordCounts.emplace_back(currentWord, 1);
            }
          }
        currentWord.clear();
      }
    }
    if (!currentWord.empty() && currentWord.length() > 1) {
      auto it = std::find_if(wordCounts.begin(), wordCounts.end(), [&](const auto& pair) { return pair.first == currentWord; });
      if (it != wordCounts.end()) {
        it->second++;
      } else {
      wordCounts.emplace_back(currentWord, 1);
      }
    }
    file.close();
    std::sort(wordCounts.begin(), wordCounts.end(), [](const auto& a, const auto& b) { return a.first < b.first; });
    std::function<void(int, int)> balancedInsert = [&](int start, int end) {
      if (start > end) {
        return;
      }
      int mid = start + (end - start) / 2;
      for (int i = 0; i < wordCounts[mid].second; ++i) {
        tree.insert(wordCounts[mid].first);
      }
      balancedInsert(start, mid - 1);
      balancedInsert(mid + 1, end);
    };
    balancedInsert(0, wordCounts.size() - 1);
}

void printFreq(const BST<std::string>& tree) {
  auto words = tree.inOrder();
  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });
  std::ofstream outFile("result/freq.txt");
  if (!outFile) {
    std::cout << "Cannot create output file!" << std::endl;
    return;
  }
  for (const auto& pair : words) {
    std::cout << pair.first << " - " << pair.second << std::endl;
    outFile << pair.first << " - " << pair.second << std::endl;
  }
  outFile.close();
}
