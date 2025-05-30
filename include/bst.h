// Copyright 2021 NNTU-CS
#include <iostream>
#include <string>

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template<typename T>
class BST {
 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;
    Node(const T& n) : value(n), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  Node* addNode(Node* node, const T& value) {
    if (!node) return new Node(value);
    if (value < node->value)
      node->left = addNode(node->left, value);
    else if (value > node->value)
      node->right = addNode(node->right, value);
    else
      node->count++;
    return node;
  }
  Node* searchNode(Node* node, const T& value) const {
    if (!node || node->value == value)
      return node;
    if (value < node->value)
      return searchNode(node->left, value);
    else
      return searchNode(node->right, value);
  }
  int depthNode(Node* node) const {
    if (!node) return 0;
    int leftDepth = depthNode(node->left);
    int rightDepth = depthNode(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }
  void inorderNode(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node) {
      inorderNode(node->right, result);
      result.emplace_back(node->value, node->count);
      inorderNode(node->left, result);
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    clear(root);
  }
  void add(const T& value) {
    root = addNode(root, value);
  }
  bool search(const T& value) const {
    return searchNode(root, value) != nullptr;
  }
  int depth() const {
    return depthNode(root);
  }
  void getSorted(std::vector<std::pair<T, value>>& result) const {
    inorderNode(root, result);
  }
  void clear(Node* node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }
};

#endif  // INCLUDE_BST_H_
