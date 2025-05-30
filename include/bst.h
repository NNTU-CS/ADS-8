// Copyright 2021 NNTU-CS
#include  <iostream>
#include  <string>
#include  <algorithm>
#include  <vector>

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template<typename T>
class BST {
 private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& n) : data(n), count(1), left(nullptr),
                              right(nullptr) {}
  };
  Node* root;
  Node* addNode(Node* node, const T& value) {
    if (!node) return new Node(value);
    if (value < node->data)
      node->left = addNode(node->left, value);
    else if (value > node->data)
      node->right = addNode(node->right, value);
    else
      node->count++;
    return node;
  }
  Node* searchNode(Node* node, const T& value) const {
    if (!node || node->data == value)
      return node;
    else if (value < node->data)
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
      result.emplace_back(node->data, node->count);
      inorderNode(node->left, result);
    }
  }
  static void clearNode(Node* node) {
    if (node) {
      clearNode(node->left);
      clearNode(node->right);
      delete node;
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    clear();
  }
  void add(const T& value) {
    root = addNode(root, value);
  }
  int search(const T& value) const {
    Node* result = searchNode(root, value);
    return result ? result->count : 0;
  }
  int depth() const {
    if (!root) return 0;
    return depthNode(root) - 1;
  }
  void getSorted(std::vector<std::pair<T, int>>& result) const {
    inorderNode(root, result);
  }
  void clear() {
    clearNode(root);
    root = nullptr;
  }
};

#endif  // INCLUDE_BST_H_
