// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>

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

  void insert(Node*& node, const T& key) {
    if (!node) {
      node = new Node(key);
    } else if (key < node->key) {
      insert(node->left, key);
    } else if (key > node->key) {
      insert(node->right, key);
    } else {
      node->count++;
    }
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return 1 + std::max(left_depth, right_depth);
  }

  Node* search(Node* node, const T& key) const {
    if (!node || node->key == key) {
      return node;
    }
    if (key < node->key) {
      return search(node->left, key);
    }
    return search(node->right, key);
  }

  void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.emplace_back(node->key, node->count);
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
  ~BST() { clear(root); }

  void insert(const T& key) { insert(root, key); }

  int depth() const { return depth(root); }

  int search(const T& key) const {
    Node* result = search(root, key);
    return result ? result->count : 0;
  }

  std::vector<std::pair<T, int>> to_vector() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
