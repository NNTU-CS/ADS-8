// Copyright 2021 NNTU-CS
#include "bst.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>

std::string toLower(const std::string &str) {
  std::string result = str;
  for (char &c : result) {
    c = std::tolower(c);
  }
  return result;
}

bool isLatinLetter(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

void makeTree(BST<std::string> &tree, const char *filename) {
  std::ifstream file(filename);
  if (!file) {
    return;
  }

  std::string word;
  char c;
  while (!file.eof()) {
    word.clear();
    while (!file.eof()) {
      c = file.get();
      if (isLatinLetter(c)) {
        word += c;
      } else if (!word.empty()) {
        tree.insert(toLower(word));
        word.clear();
      }
    }
    if (!word.empty()) {
      tree.insert(toLower(word));
    }
  }
  file.close();
}

void printFreq(BST<std::string> &tree) {
  std::vector<std::pair<std::string, int>> frequencies = tree.getFrequencies();

  std::sort(frequencies.begin(), frequencies.end(),
            [](const auto &a, const auto &b) {
              return a.second > b.second ||
                     (a.second == b.second && a.first < b.first);
            });

  for (const auto &pair : frequencies) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  std::ofstream outFile("result/freq.txt");
  if (outFile) {
    for (const auto &pair : frequencies) {
      outFile << pair.first << ": " << pair.second << "\n";
    }
    outFile.close();
  } else {
    std::cout << "err" << std::endl;
  }
}
