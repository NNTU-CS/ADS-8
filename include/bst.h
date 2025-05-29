// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

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

    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;

  void insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
    } else if (key == node->key) {
      node->count++;
    } else if (key < node->key) {
      insert(node->left, key);
    } else {
      insert(node->right, key);
    }
  }

  Node* search(Node* node, const T& key) const {
    if (!node || node->key == key) {
      return node;
    }
    return key < node->key ? search(node->left, key) : search(node->right, key);
  }

  int depth(Node* node) const {
    if (!node) {
      return 0;
    }
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) {
      return;
    }
    inorder(node->left, result);
    result.emplace_back(node->key, node->count);
    inorder(node->right, result);
  }

  void destroy(Node* node) {
    if (!node) {
      return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

 public:
  BST() : root_(nullptr) {}

  ~BST() { destroy(root_); }

  void insert(const T& key) { insert(root_, key); }

  bool search(const T& key) const { return search(root_, key) != nullptr; }

  int depth() const { return depth(root_); }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> result;
    inorder(root_, result);
    return result;
  }
};

#endif  // BST_H

