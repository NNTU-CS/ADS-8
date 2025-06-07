// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    Node(const  T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

  void insert(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value == node->value) {
      node->count++;
    } else if (value < node->value) {
      insert(node->left, value);
    } else {
      insert(node->right, value);
    }
  }

  int depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  Node* search(Node* node, const T& value) const {
    if (!node || node->value == value) {
      return node;
    }
    if (value < node->value) {
      return search(node->left, value);
    } else {
      return search(node->right, value);
    }
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.emplace_back(node->value, node->count);
    inorder(node->right, result);
  }

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}

  ~BST() {
    clear(root);
  }

  void insert(const T& value) {
    insert(root, value);
  }

  int depth() const {
    return depth(root);
  }

  Node* search(const T& value) const {
    return search(root, value);
  }

  std::vector<std::pair<T, int>> getSortedByFrequency() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);

    std::sort(result.begin(), result.end(), [](const auto& a, const auto& b) {
      return a.second > b.second;
      });

    return result;
  }
};
#endif  // INCLUDE_BST_H_
