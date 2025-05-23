// Copyright 2021 NNTU-CS
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream input_stream(filename);
  if (!input_stream.is_open()) {
    std::cerr << "файл не открыт!" << std::endl;
    return;
  }

  std::string current_word;
  char letter;
  while (input_stream.get(letter)) {
    if (letter >= 'A' && letter <= 'Z') letter = tolower(letter);
    if (letter >= 'a' && letter <= 'z') {
      current_word += letter;
    } else if (!current_word.empty()) {
      tree.add(current_word);
      current_word.clear();
    }
  }
  if (!current_word.empty()) {
    tree.add(current_word);
  }

  input_stream.close();
  std::cout << "Глубина дерева: " << tree.depth() << std::endl;
}

bool compare_by_freq(const std::pair<std::string, int>& a,
                    const std::pair<std::string, int>& b) {
  return a.second > b.second || (a.second == b.second && a.first < b.first);
}

void printFreq(BST<std::string>& tree) {
  auto word_stats = tree.getFreqs();
  std::sort(word_stats.begin(), word_stats.end(), compare_by_freq);

  std::ofstream output_stream("result/freq.txt");
  if (!output_stream.is_open()) {
    std::cerr << "файл результатов не создан!" << std::endl;
    return;
  }

  for (const auto& pair : word_stats) {
    std::cout << pair.first << ": " << pair.second << std::endl;
    output_stream << pair.first << ": " << pair.second << "\n";
  }
  output_stream.close();
}
