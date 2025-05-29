// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& val)
        : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void Clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    Clear(node->left);
    Clear(node->right);
    delete node;
  }

  int Depth(Node* node) const {
    if (node == nullptr) {
      return -1;
    }
    int left_depth = Depth(node->left);
    int right_depth = Depth(node->right);
    return 1 + (left_depth > right_depth ? left_depth : right_depth);
  }

  Node* SearchNode(Node* node, const T& value) const {
    if (node == nullptr) {
      return nullptr;
    }
    if (value == node->value) {
      return node;
    }
    if (value < node->value) {
      return SearchNode(node->left, value);
    } else {
      return SearchNode(node->right, value);
    }
  }

  void Insert(Node*& node, const T& value) {
    if (node == nullptr) {
      node = new Node(value);
      return;
    }
    if (value == node->value) {
      ++node->count;
    } else if (value < node->value) {
      Insert(node->left, value);
    } else {
      Insert(node->right, value);
    }
  }

  void InOrder(Node* node, std::vector<std::pair<T, int>>* result) const {
    if (node == nullptr) {
      return;
    }
    InOrder(node->left, result);
    result->push_back({node->value, node->count});
    InOrder(node->right, result);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { Clear(root); }

  void insert(const T& value) { Insert(root, value); }

  int depth() const {
    int d = Depth(root);
    return d < 0 ? 0 : d;
  }

  int search(const T& value) const {
    Node* node = SearchNode(root, value);
    return node != nullptr ? node->count : 0;
  }

  void getAll(std::vector<std::pair<T, int>>* result) const {
    InOrder(root, result);
  }

  std::vector<std::pair<T, int>> toVector() const {
    std::vector<std::pair<T, int>> result;
    getAll(&result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
