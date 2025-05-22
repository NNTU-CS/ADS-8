// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node *left, *right;
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  Node* insert(Node* node, const T& key) {
    if (!node) return new Node(key);
    if (key == node->key) {
      node->count++;
      return node;
    }
    if (key < node->key) {
      node->left = insert(node->left, key);
    } else {
      node->right = insert(node->right, key);
    }
    return node;
  }

  Node* search(Node* node, const T& key) const {
    if (!node || node->key == key)
      return node;
    if (key < node->key)
      return search(node->left, key);
    return search(node->right, key);
  }

  int depth(Node* node) const {
    if (!node) return -1;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }

  void inOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inOrder(node->left, result);
    result.emplace_back(node->key, node->count);
    inOrder(node->right, result);
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

  void insert(const T& key) {
    root = insert(root, key);
  }

  int search(const T& key) const {
    Node* node = search(root, key);
    return node ? node->count : 0;
  }

  int depth() const {
    return depth(root);
  }

  std::vector<std::pair<T, int>> inOrder() const {
    std::vector<std::pair<T, int>> result;
    inOrder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
