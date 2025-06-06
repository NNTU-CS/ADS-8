// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

bool compareFrequency(const std::pair<std::string, int>& a,
                      const std::pair<std::string, int>& b) {
  return a.second > b.second;
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Ошибка: не удалось открыть файл '" << filename
              << "' для чтения." << std::endl;
    return;
  }

  std::string cur_word;
  char let;

  while (file.get(let)) {
    if (std::isalpha(static_cast<unsigned char>(let))) {
      cur_word += std::tolower(static_cast<unsigned char>(let));
    } else {
      if (!cur_word.empty()) {
        tree.insert(cur_word);
        cur_word.clear();
      }
    }
  }

  if (!cur_word.empty()) {
    tree.insert(cur_word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> word_freq;
  tree.getWordFrequencies(word_freq);

  std::sort(word_freq.begin(), word_freq.end(), compareFrequency);

  std::cout << "Частотный анализ слов (по убыванию встречаемости):"
            << std::endl;
  for (const auto& pair : word_freq) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  std::ofstream outfile("result/freq.txt");
  if (!outfile.is_open()) {
    std::cerr << "Ошибка: не получилось открыть файл 'result/freq.txt' для "
                 "записи результатов."
              << std::endl;
    return;
  }

  outfile << "Частотный анализ слов (по убыванию встречаемости):" << std::endl;
  for (const auto& pair : word_freq) {
    outfile << pair.first << ": " << pair.second << std::endl;
  }

  outfile.close();
}
