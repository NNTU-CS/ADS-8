// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <cstddef>
#include <utility>

template <typename T>
class BST {
 public:
  struct Node {
    T key;
    int count = 1;
    Node* left = nullptr;
    Node* right = nullptr;
  };

  BST() = default;
  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;
  ~BST() { Clear(root_); }

  void Insert(const T& value) { InsertImpl(root_, value); }

  int search(const T& value) const {
    Node* node = root_;
    while (node) {
      if (value < node->key) {
        node = node->left;
      } else if (node->key < value) {
        node = node->right;
      } else {
        return node->count;
      }
    }
    return 0;
  }

  std::size_t depth() const { return DepthImpl(root_); }

  template <typename F>
  void InOrder(F&& f) const { InOrderImpl(root_, std::forward<F>(f)); }

 private:
  Node* root_ = nullptr;

  static void InsertImpl(Node*& node, const T& value) {
    if (!node) {
      node = new Node{value};
      return;
    }
    if (value < node->key) {
      InsertImpl(node->left, value);
    } else if (node->key < value) {
      InsertImpl(node->right, value);
    } else {
      ++node->count;
    }
  }

  static std::size_t DepthImpl(Node* node) {
    if (!node) return 0;
    std::size_t l = DepthImpl(node->left);
    std::size_t r = DepthImpl(node->right);
    return (l > r ? l : r) + 1;
  }

  template <typename F>
  static void InOrderImpl(Node* node, F&& f) {
    if (!node) return;
    InOrderImpl(node->left, f);
    f(node);
    InOrderImpl(node->right, f);
  }

  static void Clear(Node* node) {
    if (!node) return;
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
};

#endif // INCLUDE_BST_H_
