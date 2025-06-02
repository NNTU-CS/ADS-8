// Copyright 2021 NNTU-CS
#include <iostream>
#include  <fstream>
#include  "bst.h"
#include <algorithm>
#include <cctype>
#include <vector>

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cout << "File error!" << std::endl;
    return;
  }

  std::string currentWord;
  while (!file.eof()) {
    int ch = file.get();
    
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

struct WordFreq {
  std::string word;
  int count;
  
  bool operator<(const WordFreq& other) const {
    return count > other.count;
  }
};

void printFreq(BST<std::string>& tree) {
  std::vector<WordFreq> words;
  
  auto collect = [&words](typename BST<std::string>::Node* node) {
    words.push_back({node->key, node->count});
  };
  
  tree.inOrder(collect);
  
  std::sort(words.begin(), words.end());
  
  for (const auto& wf : words) {
    std::cout << wf.word << ": " << wf.count << std::endl;
  }
  
  std::ofstream out("result/freq.txt");
  for (const auto& wf : words) {
    out << wf.word << ": " << wf.count << std::endl;
  }
  out.close();
}
