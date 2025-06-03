// Copyright 2021 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    Node(const T& value)
        : key(value), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void insert(Node*& node, const T& value) {
    if (!node)
      node = new Node(value);
    else if (value < node->key)
      insert(node->left, value);
    else if (value > node->key)
      insert(node->right, value);
    else
      node->count++;
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return std::max(leftDepth, rightDepth) + 1;
  }

  Node* search(Node* node, const T& value) const {
    if (!node || node->key == value) return node;
    if (value < node->key)
      return search(node->left, value);
    else
      return search(node->right, value);
  }

  void inOrder(Node* node, std::vector<std::pair<T, int>>& vec) const {
    if (!node) return;
    inOrder(node->left, vec);
    vec.push_back({node->key, node->count});
    inOrder(node->right, vec);
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

  void insert(const T& value) { insert(root, value); }

  int depth() const { return depth(root); }

  bool search(const T& value) const { return search(root, value) != nullptr; }

  void getWords(std::vector<std::pair<T, int>>& vec) const {
    inOrder(root, vec);
  }
};

#endif  // INCLUDE_BST_H_

