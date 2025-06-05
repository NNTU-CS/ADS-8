// Copyright 2021 NNTU-CS
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream fin(filename);
  if (!fin.is_open()) {
    std::cerr << "Error: не удалось открыть файл " << filename << std::endl;
    return;
  }

  std::string line;
  while (std::getline(fin, line)) {
    std::stringstream ss(line);
    std::string token;
    while (ss >> token) {
      std::string clean;
      for (char ch : token) {
        if (std::isalpha(static_cast<unsigned char>(ch))) {
          clean += static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
        }
      }
      if (!clean.empty()) {
        tree.insert(clean);
      }
    }
  }
  fin.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> vec = tree.toVector();

  std::sort(vec.begin(), vec.end(),
    [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
      if (a.second != b.second)
        return a.second > b.second;
      return a.first < b.first;
    });

  std::ofstream fout("result/freq.txt");
  if (!fout.is_open()) {
    std::cerr << "Error: не удалось открыть файл result/freq.txt для записи" << std::endl;
  }

  for (const auto& p : vec) {
    std::cout << p.first << " " << p.second << std::endl;
    if (fout.is_open()) {
      fout << p.first << " " << p.second << std::endl;
    }
  }

  if (fout.is_open()) {
    fout.close();
  }
}
