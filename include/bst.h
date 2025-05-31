// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 public:
  BST() : root_(nullptr) {}
  ~BST() { Clear(root_); }

  void Insert(const T& key) { Insert(root_, key); }
  int Depth() const { return Depth(root_); }
  bool Search(const T& key) const { return Search(root_, key) != nullptr; }
  std::vector<std::pair<T, int>> ToVector() const {
    std::vector<std::pair<T, int>> result;
    InOrder(root_, result);
    return result;
  }

 private:
  struct Node {
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    T key;
    int count;
    Node* left;
    Node* right;
  };

  Node* root_;

  void Insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
    } else if (key < node->key) {
      Insert(node->left, key);
    } else if (key > node->key) {
      Insert(node->right, key);
    } else {
      node->count++;
    }
  }

  int Depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(Depth(node->left), Depth(node->right));
  }

  Node* Search(Node* node, const T& key) const {
    if (!node || node->key == key) return node;
    return (key < node->key) ? Search(node->left, key) : Search(node->right, key);
  }

  void InOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    InOrder(node->left, result);
    result.push_back({node->key, node->count});
    InOrder(node->right, result);
  }

  void Clear(Node* node) {
    if (!node) return;
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
};

#endif  // INCLUDE_BST_H_
