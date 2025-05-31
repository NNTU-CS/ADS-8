// Copyright 2021 NNTU-CS
#include "bst.h"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

void buildFrequencyTree(FrequencyTree<std::string>& tree, 
                       const std::string& filename) {
  std::ifstream input_file(filename);
  if (!input_file.is_open()) {
    throw std::runtime_error("Failed to open file: " + filename);
  }

  std::string current_word;
  char ch;
  while (input_file.get(ch)) {
    if (isalpha(ch)) {
      current_word += tolower(ch);
    } else if (!current_word.empty()) {
      tree.add(current_word);
      current_word.clear();
    }
  }
  
  if (!current_word.empty()) {
    tree.add(current_word);
  }
}

void displayFrequencyResults(const FrequencyTree<std::string>& tree) {
  auto items = tree.getAllItems();
  
  std::sort(items.begin(), items.end(),
            [](const auto& a, const auto& b) {
              return b.second < a.second || 
                    (b.second == a.second && b.first > a.first);
            });

  std::ofstream output_file("result/frequency_results.txt");
  
  for (const auto& [word, count] : items) {
    std::cout << word << ": " << count << '\n';
    output_file << word << ": " << count << '\n';
  }
}
