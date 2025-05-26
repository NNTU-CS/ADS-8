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
    explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

  void clear(Node* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
  }

  int depth(Node* node) const {
    if (!node) return 0;
    int leftDepth = depth(node->left);
    int rightDepth = depth(node->right);
    return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
  }

  Node* searchNode(Node* node, const T& value) const {
    if (!node) return nullptr;
    if (value == node->value) return node;
    if (value < node->value)
      return search(node->left, value);
    else
      return search(node->right, value);
  }

  void insert(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
      return;
    }
    if (value == node->value)
      node->count++;
    else if (value < node->value)
      insert(node->left, value);
    else
      insert(node->right, value);
  }

  void inOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inOrder(node->left, result);
    result.push_back({node->value, node->count});
    inOrder(node->right, result);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }

  void insert(const T& value) { insert(root, value); }
  int depth() const { return depth(root); }
  int search(const T& value) const {
  Node* node = search(root, value);
  return node ? node->count : 0;
}

  void getAll(std::vector<std::pair<T, int>>& result) const {
    inOrder(root, result);
  }
};

#endif  // INCLUDE_BST_H_
