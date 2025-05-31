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

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error: " << filename << std::endl;
    return;
  }

  std::string word;
  while (file >> word) {
    std::string cleaned = clean_word(word);
    if (!cleaned.empty()) {
      tree.insert(cleaned);
    }
  }
}
