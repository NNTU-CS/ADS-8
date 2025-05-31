// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <algorithm>
#include <memory>
#include <string>
#include <utility>

template <typename T>
class BST {
 public:  
  BST() : root_(nullptr), tree_size_(0) {}

  void insert(const T& value) {
    root_ = insertNode(std::move(root_), value);
    ++tree_size_;
  }

  int depth() const {
    return nodeDepth(root_);
  }

  int size() const {
    return tree_size_;
  }

 private:  
  struct Node {
    explicit Node(const T& val) : data(val), left(nullptr), right(nullptr) {}

    T data;
    std::unique_ptr<Node> left;
    std::unique_ptr<Node> right;
  };

  std::unique_ptr<Node> root_;
  int tree_size_;

  std::unique_ptr<Node> insertNode(std::unique_ptr<Node> node, const T& value) {
    if (!node) {
      return std::make_unique<Node>(value);
    }
    if (value < node->data) {
      node->left = insertNode(std::move(node->left), value);
    } else {
      node->right = insertNode(std::move(node->right), value);
    }
    return node;
  }

  int nodeDepth(const std::unique_ptr<Node>& node) const {
    if (!node) return 0;
    return 1 + std::max(nodeDepth(node->left), nodeDepth(node->right));
  }
};

#endif  // INCLUDE_BST_H_
