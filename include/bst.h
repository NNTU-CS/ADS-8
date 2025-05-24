// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root = nullptr;

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* insert(Node* node, const T& value) {
    if (!node) return new Node(value);
    if (value < node->key) {
      node->left = insert(node->left, value);
    } else if (value > node->key) {
      node->right = insert(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  Node* find(Node* node, const T& value) const {
    if (!node) return nullptr;
    if (value < node->key) return find(node->left, value);
    if (value > node->key) return find(node->right, value);
    return node;
  }

  int depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    inorder(node->left, out);
    out.emplace_back(node->key, node->count);
    inorder(node->right, out);
  }

 public:
  BST() = default;
  ~BST() {
    clear(root);
  }

  void insert(const T& value) {
    root = insert(root, value);
  }

  Node* search(const T& value) const {
    return find(root, value);
  }

  int getDepth() const {
    return depth(root);
  }

  std::vector<std::pair<T, int>> getAllElements() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_

