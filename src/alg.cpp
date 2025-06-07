// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <cctype>
#include "bst.h"

using namespace std;

void makeTree(BST<string>& tree, const char* filename) {
  ifstream file(filename);
  if (!file.is_open()) {
    cerr << "Error opening the file!\n";
    return;
  }
  string word;
  char c;
  while(file.get(c)) {
    if(isalpha(c)){
      word += tolower(c);
    }
    else if(word.length() > 0) {
      tree.insert(word);
      word.clear();
    }
  }
  file.close();
}
void printFreq(BST<string>& tree) {
  ofstream output("result/freq.txt");
  if(output.fail()){
    cerr << "Error writing to file!\n";
    return;
  }
  vector<Node<string>*> nodes;
  tree.inorder(nodes);
  sort(nodes.begin(), nodes.end(), [](const Node<string>* a, const Node<string>* b) {
    return a->count > b->count || (a->count == b->count && a->key < b->key);
  });
  for(auto n : nodes) {
    output << n->key << ": " << n->count << endl;
  }
  output.close();
}
