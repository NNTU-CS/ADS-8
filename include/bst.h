// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <string>
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

  Node* find(Node* node, const T& value) const {
    if (!node || node->key == value) return node;
    if (value < node->key) return find(node->left, value);
    return find(node->right, value);
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + std::max(leftDepth, rightDepth);
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    inorder(node->left, out);
    out.emplace_back(node->key, node->count);
    inorder(node->right, out);
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

  int findCount(const T& value) const {
    Node* found = find(root, value);
    return found ? found->count : 0;
  }

  int depth() const {
    return depth(root);
  }

  std::vector<std::pair<T, int>> getAllElements() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
