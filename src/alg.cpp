// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include  <cctype>
#include  <algorithm>
#include  <string>
#include  "bst.h"

template<typename T>
void sortRec(BST<T>& t, const std::vector<T>& w, int l, int r) {
  if (l > r)
    return;
  int mid = (l + r) / 2;
  t.add(w[mid]);
  sortRec(t, w, l, mid - 1);
  sortRec(t, w, mid + 1, r);
}
template<typename T>
void addSorted(BST<T>& t, const std::vector<T>& w) {
  if (w.empty())
    return;
  std::vector<T> sortW = w;
  std::sort(sortW.begin(), sortW.end());
  sortRec(t, sortW, 0, sortW.size() - 1);
}

void makeTree(BST<std::string>& tree, const char* filename) {
  std::ifstream file(filename);
  if (!file) {
    std::cerr << "File opening error!" << std::endl;
    return;
  }
  std::string word;
  int ch;
  std::vector<std::string> words;
  while ((ch = file.get()) != EOF) {
    if (std::isalpha(ch)) {
      word += static_cast<char>(std::tolower(ch));
    } else {
      if (!word.empty()) {
        words.push_back(word);
        word.clear();
      }
    }
  }
  if (!word.empty())
    words.push_back(word);
  file.close();
  addSorted(tree, words);
}
void printFreq(BST<std::string>& tree) {
  std::vector<std::pair<std::string, int>> result;
  tree.getSorted(result);
  std::ofstream outFile("result/freq.txt");
  for (const auto& pair : result) {
    std::cout << pair.first << ": " << pair.second << std::endl;
    outFile << pair.first << " " << pair.second << std::endl;
  }
  outFile.close();
}
