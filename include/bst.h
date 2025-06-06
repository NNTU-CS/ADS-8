// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>

template <typename T>
struct Node {
  T key;
  int cnt;
  Node* left;
  Node* right;

  explicit Node(const T& value) : key(value), cnt(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
 public:
  BST() : root_(nullptr) {}

  ~BST() { Destroy(root_); }

  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;

  void insert(const T& value) { root_ = InsertNode(root_, value); }

  int search(const T& value) const {
    Node<T>* node = root_;
    while (node != nullptr) {
      if (value < node->key) {
        node = node->left;
      } else if (node->key < value) {
        node = node->right;
      } else {
        return node->cnt;
      }
    }
    return 0;
  }

  int depth() const { return ComputeDepth(root_) - 1; }

  void getWordFrequencies(std::vector<std::pair<T, int>>& output) const {
    TraverseInOrder(root_, output);
  }

 private:
  Node<T>* root_;

  Node<T>* InsertNode(Node<T>* node, const T& value) {
    if (node == nullptr) {
      return new Node<T>(value);
    }
    if (value == node->key) {
      ++node->cnt;
    } else if (value < node->key) {
      node->left = InsertNode(node->left, value);
    } else {
      node->right = InsertNode(node->right, value);
    }
    return node;
  }

  int ComputeDepth(Node<T>* node) const {
    if (node == nullptr) {
      return 0;
    }
    int left_depth = ComputeDepth(node->left);
    int right_depth = ComputeDepth(node->right);
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
  }

  void TraverseInOrder(Node<T>* node, std::vector<std::pair<T, int>>& output) const {
    if (node == nullptr) {
      return;
    }
    TraverseInOrder(node->left, output);
    output.emplace_back(node->key, node->cnt);
    TraverseInOrder(node->right, output);
  }

  void Destroy(Node<T>* node) {
    if (node == nullptr) {
      return;
    }
    Destroy(node->left);
    Destroy(node->right);
    delete node;
  }
};

#endif  // INCLUDE_BST_H_
