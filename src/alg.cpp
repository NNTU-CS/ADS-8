// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <cctype>
#include  <vector>
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
    if (isalpha(ch) && (ch & 0x80) == 0) { 
      word += static_cast<char>(tolower(ch));
    }
    else {
      if (!word.empty()) {
        tree.insert(word);
        word.clear();
      }
    }
  }
  if (!word.empty()) {
    tree.insert(word);
  }
  file.close();
}

// Для сбора слов с частотами
struct WordFreq {
  std::string word;
  int count;
  WordFreq(const std::string& w, int c) : word(w), count(c) {}
};

// Вспомогательная функция для обхода
void collect(BSTNode<std::string>* node, void* arg) {
  std::vector<WordFreq>* v = static_cast<std::vector<WordFreq>*>(arg);
  v->emplace_back(node->key, node->count);
}

void printFreq(BST<std::string>& tree) {
  std::vector<WordFreq> arr;
  tree.inorder(collect, &arr);

  std::sort(arr.begin(), arr.end(), [](const WordFreq& a, const WordFreq& b) {
  return (a.count > b.count) || (a.count == b.count && a.word < b.word);
});

std::ofstream fout("result/freq.txt");
for (const auto& wf : arr) {
  std::cout << wf.word << ": " << wf.count << std::endl;
  if (fout) fout << wf.word << ": " << wf.count << std::endl;
}
fout.close();
}
