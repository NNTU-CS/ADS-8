// Copyright 2021 NNTU-CS
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>

#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;
  while (file.get(ch)) {
    if (std::isalpha(static_cast<unsigned char>(ch))) {
      word += std::tolower(ch);
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }

  if (!word.empty()) {
    tree.insert(word);
  }

  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;
  tree.getWords(words);

  std::sort(words.begin(), words.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });

  std::ofstream out("result/freq.txt");
  if (!out) {
    std::cerr << "Failed to open result/freq.txt" << std::endl;
    return;
  }

  for (const auto& [word, count] : words) {
    std::cout << word << ": " << count << "\n";
    out << word << ": " << count << "\n";
  }

  out.close();
}
