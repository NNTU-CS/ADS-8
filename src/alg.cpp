// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <vector>
#include <string>
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
    if (ch >= 'A' && ch <= 'Z')
      ch += 'a'-'A';
    if (ch >= 'a' && ch <= 'z')
    word += ch;
    else if (!word.empty()) {
      tree.add(word);
      word.clear();
    }
  }
  if (!word.empty())
    tree.add(word);
  file.close();
}

void printFreq(BST<std::string>& tree) {
  std::vector<BST<std::string>::Node*> nodes = tree.getAllNodes();
  std::sort(nodes.begin(), nodes.end(), [](const BST<std::string>::Node* a, const BST<std::string>::Node* b) {
    return a->count > b->count;
    });
  for (const auto& node : nodes) {
    std::cout << node->value << " " << node->count << "\n";
  }
}
