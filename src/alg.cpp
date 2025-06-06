// Copyright 2021 NNTU-CS
#include <fstream>
#include <iostream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "bst.h"


// Читает файл post по символам, собирает строки-слова в нижний регистр и вставляет в tree.
static void buildTree(BST<std::string>& tree, const char* filepath) {
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

// Сортирует вектор пар «(слово, частота)» по частоте убывания, потом по ключу.
static bool frequencyCompare(const std::pair<std::string, int>& a,
                             const std::pair<std::string, int>& b) {
  if (a.second != b.second) {
    return a.second > b.second;
  }
  return a.first < b.first;
}

// Собирает пары {слово, count} "in‐order", затем сортирует и выводит.
static void outputFrequencies(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> freqList;
  tree.collect(&freqList);

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

// === ФУНКЦИИ, КОТОРЫЕ ОЖИДАЮТ ТЕСТЫ ===

// Сигнатура makeTree(BST<std::string>&, const char*), как в тестах.
// Просто вызывает наш buildTree(...).
void makeTree(BST<std::string>& tree, const char* filename) {
  buildTree(tree, filename);
}

// Сигнатура printFreq(BST<std::string>&), как в тестах.
// Просто вызывает наш outputFrequencies(...).
void printFreq(BST<std::string>& tree) {
  outputFrequencies(tree);
}
