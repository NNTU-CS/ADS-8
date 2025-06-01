// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T key;
    int count;
    Node *right, *left;
    explicit Node(const T& value) : key(value), count(1), right(nullptr), left(nullptr) {}
  };
  Node* root;
  Node* addNode(Node* root, const T& value) {
    if (root == nullptr) {
      return new Node(value);
    }
    if (root->key == value) {
      ++root->count;
      return root;
    }
    if (root->key > value) {
      root->left = addNode(root->left, value);
    } else {
      root->right = addNode(root->right, value);
    }
    return root;
  }
  int getDepth(Node* root) {
    if (root == nullptr) return 0;
    int left_depth = getDepth(root->left);
    int right_depth = getDepth(root->right);
    return (left_depth >= right_depth ? left_depth : right_depth) + 1;
  }
  int searchNode(Node* root, const T& value) {
    if (root == nullptr) return 0;
    if (value == root->key) return root->count;
    if (value < root->key) return searchNode(root->left, value);
    else return searchNode(root->right, value);
    }
  void clear(Node* root) {
    if (root == nullptr) return;
    clear(root->left);
    clear(root->right);
    delete root;
  }
  void Order(Node* root, std::vector<std::pair<T, int>>& res) const {
    if (root == nullptr) return;
    Order(root->left, res);
    res.push_back({ root->key, root->count });
    Order(root->right, res);
  }

 public:
  BST(): root(nullptr) {}
  ~BST() {
    clear(root);
  }
  void add(const T& value) {
    root = addNode(root, value);
  }
  int search(const T& value) {
    return searchNode(root, value);
  }
  int depth() {
    return getDepth(root)-1;
  }
  std::vector<std::pair<T, int>> array_words() const {
    std::vector<std::pair<T, int>> result;
    Order(root, result);
    return result;
  }
};
#endif  // INCLUDE_BST_H_
