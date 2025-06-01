// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* right;
    Node* left;
    explicit Node(const T& value)
      : key(value), count(1), right(nullptr), left(nullptr) {
    }
  };
  Node* root;
  Node* addNode(Node* node, const T& value) {
    if (!node) return new Node(value);
    if (node->key == value) {
      ++node->count;
      return node;
    }
    if (value < node->key) {
      node->left = addNode(node->left, value);
    } else {
      node->right = addNode(node->right, value);
    }
    return node;
  }
  int getDepth(Node* node) const {
    if (!node) return 0;
    return std::max(getDepth(node->left), getDepth(node->right)) + 1;
  }
  int searchNode(Node* node, const T& value) const {
    if (!node) return 0;
    if (value == node->key) return node->count;
    return searchNode(value < node->key ? node->left : node->right, value);
  }
  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
  void inOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inOrder(node->left, result);
    result.emplace_back(node->key, node->count);
    inOrder(node->right, result);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }
  void add(const T& value) {
    root = addNode(root, value);
  }
  int search(const T& value) const {
    return searchNode(root, value);
  }
  int depth() const {
    return getDepth(root) - 1;
  }
  std::vector<std::pair<T, int>> array_words() const {
    std::vector<std::pair<T, int>> result;
    inOrder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
