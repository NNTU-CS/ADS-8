// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  Node* insert(Node* node, T value) {
    if (!node) return new Node(value);
    if (value == node->key) {
      node->count++;
    } else if (value < node->key) {
      node->left = insert(node->left, value);
    } else {
      node->right = insert(node->right, value);
    }
    return node;
  }
  int depth(Node* node) const {
    if (!node) return 0;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }
  Node* search(Node* node, T value) const {
    if (!node) return nullptr;
    if (value == node->key) return node;
    if (value < node->key) return search(node->left, value);
    return search(node->right, value);
  }
  void delTree(Node* node) {
    if (node) {
      delTree(node->left);
      delTree(node->right);
      delete node;
    }
  }
  void printFreqX(Node* node, std::vector<std::pair<T, int>>& freqList) const {
    if (node) {
        printFreqX(node->left, freqList);
        freqList.emplace_back(node->key, node->count);
        printFreqX(node->right, freqList);
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { delTree(root); }
  void insert(T value) {
    root = insert(root, value);
  }
  int depth() const {
    return depth(root);
  }
  int search(T value) const {
    Node* found = search(root, value);
    return found ? found->count : 0;
  }
  int getCount(T value) const {
    Node* found = search(root, value);
    return found ? found->count : 0;
  }
  void printFreq(std::ostream& out = std::cout) const {
    std::vector<std::pair<T, int>> freqList;
    printFreqX(root, freqList);
    std::sort(freqList.begin(), freqList.end(),
        [](const auto& a, const auto& b) { return a.second > b.second; });
    for (const auto& entry : freqList) {
      out << entry.first << ": " << entry.second << std::endl;
    }
  }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);
#endif  // INCLUDE_BST_H_
