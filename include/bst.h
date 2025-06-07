// Copyright 2025 NNTU-CS

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>

template <typename T>
class BST {
 private:
  struct Node {
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    T key;
    int count;
    Node* left;
    Node* right;
  };

  Node* root;

  Node* insert(Node* node, const T& key) {
    if (!node) return new Node(key);
    if (key == node->key) {
      node->count++;
      return node;
    }
    if (key < node->key)
      node->left = insert(node->left, key);
    else
      node->right = insert(node->right, key);
    return node;
  }

  int depth(Node* node) const {
    if (!node) return -1;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  int searchCount(Node* node, const T& key) const {
    if (!node) return 0;
    if (key == node->key) return node->count;
    if (key < node->key)
      return searchCount(node->left, key);
    else
      return searchCount(node->right, key);
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

  int depth() const {
    return depth(root);
  }

  int search(const T& key) const {
    return searchCount(root, key);
  }
};

#endif  // INCLUDE_BST_H_
