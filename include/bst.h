// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <algorithm>  // для std::max
template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    Node(T value) : key(value), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  void insert(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value < node->key) {
      insert(node->left, value);
    } else if (value > node->key) {
      insert(node->right, value);
    } else {
      node->count++;
    }
  }
  Node* search(Node* node, const T& value) const {
    if (!node || node->key == value) return node;
    if (value < node->key)
      return search(node->left, value);
    else
      return search(node->right, value);
  }
  int depth(Node* node) const {
    if (!node) return 0;
    return std::max(depth(node->left), depth(node->right)) + 1;
  }
  void collect(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    collect(node->left, out);
    out.push_back({node->key, node->count});
    collect(node->right, out);
  }
  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }
 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(const T& value) {
    insert(root, value);
  }
  bool search(const T& value) {
    return search(root, value) != nullptr;
  }
  int depth() const {
    return depth(root);
  }
  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    collect(root, result);
    return result;
  }
};
#endif  // INCLUDE_BST_H_
