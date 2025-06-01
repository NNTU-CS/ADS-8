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
    explicit Node(const T& value) : key(value), count(1), right(nullptr), left(nullptr) {}
  };
  Node* root;

  Node* addNode(Node*& node, const T& value) {
    if (node == nullptr) {
      node = new Node(value);
      return node;
    }
    if (node->key == value) {
      ++node->count;
      return node;
    }
    if (value < node->key) {
      return addNode(node->left, value);
    } else {
      return addNode(node->right, value);
    }
  }

  int getDepth(const Node* node) const {
    if (node == nullptr) return 0;
    int leftDepth = getDepth(node->left);
    int rightDepth = getDepth(node->right);
    return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
  }

  int searchNode(const Node* node, const T& value) const {
    if (node == nullptr) return 0;
    if (value == node->key) return node->count;
    if (value < node->key) {
      return searchNode(node->left, value);
    } else {
      return searchNode(node->right, value);
    }
  }

  void clear(Node* node) {
    if (node != nullptr) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }

  void inOrder(const Node* node, std::vector<std::pair<T, int>>& result) const {
    if (node != nullptr) {
      inOrder(node->left, result);
      result.push_back({node->key, node->count});
      inOrder(node->right, result);
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void add(const T& value) {
    addNode(root, value);
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
