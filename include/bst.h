// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>

template <typename T>
class BST {
  struct Node {
    T      key;
    int    count;
    Node*  left;
    Node*  right;
    Node(const T& k): key(k), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

  void destroy(Node* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  Node* insert(Node* node, const T& key) {
    if (!node) {
      return new Node(key);
    }
    if (key < node->key) {
      node->left = insert(node->left, key);
    } else if (node->key < key) {
      node->right = insert(node->right, key);
    } else {
      node->count++;
    }
    return node;
  }

  int search(Node* node, const T& key) const {
    if (!node) return 0;
    if (key < node->key)        return search(node->left, key);
    if (node->key < key)        return search(node->right, key);
    return node->count;
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int dl = depth(node->left);
    int dr = depth(node->right);
    return (dl > dr ? dl : dr) + 1;
  }

  void traverse(Node* node, std::vector<std::pair<T,int>>& elems) const {
    if (!node) return;
    traverse(node->left, elems);
    elems.emplace_back(node->key, node->count);
    traverse(node->right, elems);
  }

 public:
  BST(): root(nullptr) {}
  ~BST() { destroy(root); }

  void insert(const T& key) {
    root = insert(root, key);
  }

  int search(const T& key) const {
    return search(root, key);
  }

  int depth() const {
    int d = depth(root);
    if (d > 0) return d - 1;
    return 0;
  }

  std::vector<std::pair<T,int>> toVector() const {
    std::vector<std::pair<T,int>> elems;
    traverse(root, elems);
    return elems;
  }
};

#endif  // INCLUDE_BST_H_
