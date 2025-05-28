// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  char ch;
  while (file.get(ch)) {
    if (isalpha(ch)) {
      currentWord += tolower(ch);
    } else if (!currentWord.empty()) {
      tree.insert(currentWord);
      currentWord.clear();
    }
  }
  if (!currentWord.empty()) {
    tree.insert(currentWord);
  }
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> words;

  auto collectWords = [&words](BST<std::string>::Node* node) {
    words.emplace_back(node->key, node->count);
  };

  tree.inOrder(collectWords);

  std::sort(words.begin(), words.end(), [](const auto& a, const auto& b) {
    return a.second > b.second;
  });

  for (const auto& pair : words) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  std::ofstream outFile("result/freq.txt");
  for (const auto& pair : words) {
    outFile << pair.first << ": " << pair.second << std::endl;
  }
  outFile.close();
}
