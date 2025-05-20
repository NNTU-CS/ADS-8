// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <algorithm>
#include <vector>
#include <filesystem>
#include <iomanip>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string word;
  char ch;

  while (file.get(ch)) {
    if (std::isalpha(ch)) {
      word += std::tolower(ch);
    } else if (!word.empty()) {
      tree.insert(word);
      word.clear();
    }
  }
  if (!word.empty()) tree.insert(word);

  file.close();
}

void printFreq(BST<std::string>& tree) {
  auto vec = tree.toVector();

  std::sort(vec.begin(), vec.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  std::filesystem::create_directories("result");
  std::ofstream out("result/freq.txt");

  for (const auto& pair : vec) {
    std::cout << std::setw(5) << pair.second << " - " << pair.first << "\n";
    out << pair.second << " - " << pair.first << "\n";
  }

  out.close();
}
