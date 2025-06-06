// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include <vector>
#include <algorithm>
#include  "bst.h"
using namespace std;

void makeTree(BST<string>& tree, const char* filename) {
  ifstream file(filename);
  if (!file) {
    cout << "File error!" << endl;
    return;
  }
  string word;
  char ch;
  while (file.get(ch)) {
    if (isalpha(static_cast<unsigned char>(ch))) {
      word += tolower(ch);
    } else {
      if (!word.empty()) {
        tree.add(word);
        word.clear();
      }
    }
  }
  if (!word.empty())
    tree.add(word);
    file.close();
}
void printFreq(BST<string>& tree) {
  vector<std::pair<std::string, int>> words;
  tree.toVector(words);
  sort(words.begin(), words.end(),
      [](const pair<string, int>& a, const pair<string, int>& b) {
      return a.second > b.second;
      });
  ofstream out("result/freq.txt");
  if (!out) {
    cout << "Cannot write to result/freq.txt" << endl;
    return;
  }
  for (auto& pair : words) {
    cout << pair.first << ": " << pair.second << endl;
    out << pair.first << ": " << pair.second << endl;
  }
  out.close();
}
