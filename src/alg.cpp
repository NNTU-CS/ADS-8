// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "bst.h"

bool compareFrequency(const std::pair<std::string, int>& lhs,
                      const std::pair<std::string, int>& rhs) {
  if (lhs.second != rhs.second) {
    return lhs.second > rhs.second;
  }
  return lhs.first < rhs.first;
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream input_file(filename, std::ios::in);
  if (!input_file) {
    std::cerr << "Ошибка: не удалось открыть файл '" << filename
              << "' для чтения." << std::endl;
    return;
  }
  std::string current_word;
  int ch_int;
  while ((ch_int = input_file.get()) != EOF) {
    char ch = static_cast<char>(ch_int);
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      current_word.push_back(std::tolower(static_cast<unsigned char>(ch)));
    } else if (!current_word.empty()) {
      tree.insert(current_word);
      current_word.clear();
    }
  }
  if (!current_word.empty()) {
    tree.insert(current_word);
  }
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> word_freq;
  tree.getWordFrequencies(word_freq);

  std::sort(word_freq.begin(), word_freq.end(), compareFrequency);

  const std::string header = "Частотный анализ слов (по убыванию встречаемости):";
  std::cout << header << std::endl;
  for (const auto& entry : word_freq) {
    std::cout << entry.first << ": " << entry.second << std::endl;
  }

  std::ofstream output_file("result/freq.txt");
  if (!output_file) {
    std::cerr << "Ошибка: не получилось открыть файл 'result/freq.txt' для записи результатов."
              << std::endl;
    return;
  }
  output_file << header << std::endl;
  for (const auto& entry : word_freq) {
    output_file << entry.first << ": " << entry.second << std::endl;
  }
}
