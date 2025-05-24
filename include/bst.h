// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

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
    Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
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

  int getDepth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(getDepth(node->left), getDepth(node->right));
  }

  int find(Node* node, const T& value) const {
    if (!node) return 0;
    if (value < node->key) return find(node->left, value);
    if (value > node->key) return find(node->right, value);
    return node->count;
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    inorder(node->left, out);
    out.push_back({node->key, node->count});
    inorder(node->right, out);
  }

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { destroy(root); }

  void insert(const T& value) { insert(root, value); }
  int getDepth() const { return getDepth(root); }
  int find(const T& value) const { return find(root, value); }
  std::vector<std::pair<T, int>> getAllElements() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_

#endif  // INCLUDE_BST_H_
