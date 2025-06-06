// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
  struct Node {
    T value;
    size_t count;
    Node* left;
    Node* right;
    explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  void destroy(Node* node) {
    if (node) {
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  }

  Node* insert(Node* node, const T& value) {
    if (!node) return new Node(value);
    if (value < node->value) {
      node->left = insert(node->left, value);
    } else if (value > node->value) {
      node->right = insert(node->right, value);
    } else {
      node->count++;
    }
    return node;
  }

  Node* search(Node* node, const T& value) const {
    if (!node || node->value == value) return node;
    if (value < node->value) return search(node->left, value);
    return search(node->right, value);
  }

  size_t depth(Node* node) const {
    if (!node) return 0;
    return 1 + std::max(depth(node->left), depth(node->right));
  }

  void inOrder(Node* node, std::vector<std::pair<T, size_t>>& result) const {
    if (node) {
      inOrder(node->left, result);
      result.emplace_back(node->value, node->count);
      inOrder(node->right, result);
    }
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { destroy(root); }

  void insert(const T& value) { root = insert(root, value); }

  bool search(const T& value) const { return search(root, value) != nullptr; }

  size_t depth() const { return depth(root); }

  std::vector<std::pair<T, size_t>> getSortedByFreq() const {
    std::vector<std::pair<T, size_t>> result;
    inOrder(root, result);
    std::sort(result.begin(), result.end(),
              [](const auto& a, const auto& b) {
                return a.second > b.second || (a.second == b.second && a.first < b.first);
              });
    return result;
  }
};

void makeTree(BST<std::string>& tree, const char* filename);
void printFreq(BST<std::string>& tree);

#endif  // INCLUDE_BST_H_
