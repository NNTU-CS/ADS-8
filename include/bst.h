// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& val) : data(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void insert(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value == node->data) {
      node->count++;
    } else if (value < node->data) {
      insert(node->left, value);
    } else {
      insert(node->right, value);
    }
  }

  int search(Node* node, const T& value) const {
    if (!node) return 0;
    if (value == node->data) return node->count;
    if (value < node->data) return search(node->left, value);
    return search(node->right, value);
  }

int depth(Node* node) const {
    if (node == nullptr) return -1;
    return 1 + std::max(depth(node->left), depth(node->right));
}

  void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inorder(node->left, result);
    result.push_back({node->data, node->count});
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

  void insert(const T& value) {
    insert(root, value);
  }

  int search(const T& value) const {
    return search(root, value);
  }

  int depth() const {
    return depth(root);
  }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> result;
    inorder(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
