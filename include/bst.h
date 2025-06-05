// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template<typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    int height;
    Node* left;
    Node* right;

    explicit Node(const T& k)
      : key(k), count(1), height(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  int height(Node* n) const {
    return n ? n->height : 0;
  }

  int balanceFactor(Node* n) const {
    return n ? height(n->left) - height(n->right) : 0;
  }

  void updateHeight(Node* n) {
    int hl = height(n->left);
    int hr = height(n->right);
    n->height = (hl > hr ? hl : hr) + 1;
  }

  Node* rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
  }

  Node* rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
  }

  Node* balance(Node* n) {
    updateHeight(n);
    int bf = balanceFactor(n);
    if (bf > 1) {
      if (balanceFactor(n->left) < 0) {
        n->left = rotateLeft(n->left);
      }
      return rotateRight(n);
    }
    if (bf < -1) {
      if (balanceFactor(n->right) > 0) {
        n->right = rotateRight(n->right);
      }
      return rotateLeft(n);
    }
    return n;
  }

  Node* insertRec(Node* node, const T& key) {
    if (!node) {
      return new Node(key);
    }
    if (key == node->key) {
      node->count++;
      return node;
    }
    if (key < node->key) {
      node->left = insertRec(node->left, key);
    } else {
      node->right = insertRec(node->right, key);
    }
    return balance(node);
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    inorder(node->left, out);
    out.emplace_back(node->key, node->count);
    inorder(node->right, out);
  }

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  int searchRec(Node* node, const T& key) const {
    if (!node) return 0;
    if (key == node->key) return node->count;
    if (key < node->key) return searchRec(node->left, key);
    return searchRec(node->right, key);
  }

  int depthRec(Node* node) const {
    return node ? node->height : 0;
  }

 public:
  BST() : root(nullptr) {}
  ~BST() {
    destroy(root);
  }

  void insert(const T& key) {
    root = insertRec(root, key);
  }

  int search(const T& key) const {
    return searchRec(root, key);
  }

  int depth() const {
    return depthRec(root);
  }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
