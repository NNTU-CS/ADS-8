// Copyright 2021 NNTU-CS
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <algorithm>
#include "bst.h"

std::string clean_word(const std::string& word) {
  std::string result;
  for (char c : word) {
    if (std::isalpha(static_cast<unsigned char>(c))) {
      result += std::tolower(static_cast<unsigned char>(c));
    }
  }
  return result;
}

BST<std::string> build_tree(const std::string& filename) {
  BST<std::string> tree;
  std::ifstream file(filename);
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream iss(line);
    std::string word;
    while (iss >> word) {
      std::string cleaned = clean_word(word);
      if (!cleaned.empty()) {
        tree.insert(cleaned);
      }
    }
  }

  return tree;
}
