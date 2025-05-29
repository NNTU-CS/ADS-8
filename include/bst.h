// Copyright 2025 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T value;          // Stores the node's value
    int count;        // Count of duplicate values
    Node* left;       // Left child pointer
    Node* right;      // Right child pointer

    explicit Node(const T& val) : value(val), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root;

  // Recursively inserts a value into the BST
  void insert(Node*& node, const T& value) {
    if (!node) {
      node = new Node(value);
    } else if (value < node->value) {
      insert(node->left, value);
    } else if (value > node->value) {
      insert(node->right, value);
    } else {
      node->count++;
    }
  }

  // Finds a node with the specified value
  Node* find(Node* node, const T& value) const {
    if (!node || node->value == value) return node;
    return find(value < node->value ? node->left : node->right, value);
  }

  // Calculates tree depth using ternary operator
  int depth(Node* node) const {
    return !node ? -1 : 1 + (depth(node->left) > depth(node->right) ?
                             depth(node->left) : depth(node->right));
  }

  // In-order traversal that populates an output vector
  void inOrder(Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    inOrder(node->left, out);
    out.emplace_back(node->value, node->count);
    inOrder(node->right, out);
  }

  // Recursively clears all nodes
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

  int findCount(const T& value) const {
    Node* found = find(root, value);
    return found ? found->count : 0;
  }

  int search(const T& value) const {
    return findCount(value);  // search simply calls findCount
  }

  int depth() const {
    return depth(root);
  }

  void getAll(std::vector<std::pair<T, int>>& result) const {
    inOrder(root, result);  // Uses output parameter
  }
};

#endif  // INCLUDE_BST_H_
