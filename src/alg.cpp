// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "bst.h"

// Это «основная» функция постройки дерева (новое имя).
void buildTree(BST<std::string>& tree, const char* filepath) {
  std::ifstream inputFile(filepath);
  if (!inputFile.is_open()) {
    std::cerr << "File error: cannot open '" << filepath << "'." << std::endl;
    return;
  }

  std::string buffer;
  char ch;
  while (inputFile.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      buffer.push_back(
          static_cast<char>(std::tolower(static_cast<unsigned char>(ch))));
    } else {
      if (!buffer.empty()) {
        tree.insert(buffer);
        buffer.clear();
      }
    }
  }
  if (!buffer.empty()) {
    tree.insert(buffer);
  }
  inputFile.close();
}

// Это «основная» функция вывода частот (новое имя).
void outputFrequencies(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freqList;
  tree.collect(&freqList);

  auto frequencyCompare = [](const std::pair<std::string, int>& a,
                             const std::pair<std::string, int>& b) {
    if (a.second != b.second) {
      return a.second > b.second;
    }
    return a.first < b.first;
  };

  std::sort(freqList.begin(), freqList.end(), frequencyCompare);

  std::ofstream report("result/freq.txt");
  if (!report.is_open()) {
    std::cerr << "File error: cannot write to 'result/freq.txt'." << std::endl;
    return;
  }

  for (const auto& entry : freqList) {
    std::cout << entry.first << " " << entry.second << std::endl;
    report << entry.first << " " << entry.second << std::endl;
  }
  report.close();
}

// Ниже — «обёртки», чтобы тесты, ожидающие makeTree и printFreq, не «сломались».

// Тесты вызывают: makeTree(tree, filename)
extern "C" void makeTree(BST<std::string>& tree, const char* filename) {
  buildTree(tree, filename);
}

// Тесты вызывают: printFreq(tree)
extern "C" void printFreq(BST<std::string>& tree) {
  outputFrequencies(tree);
}
