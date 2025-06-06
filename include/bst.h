// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <utility>

template <typename T>
class BST {
 private:
  struct node {
    T data;
    int count;
    node* left;
    node* right;
    explicit node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
  };

  node* root;

  void insert(node*& root, const T& value) {
    if (!root) {
      root = new node(value);
    } else if (value == root->data) {
      root->count++;
    } else if (value < root->data) {
      insert(root->left, value);
    } else {
      insert(root->right, value);
    }
  }

  int search(node* root, const T& value) const {
    if (!root) return 0;
    if (value == root->data) return root->count;
    if (value < root->data) return search(root->left, value);
    return search(root->right, value);
  }

int depth(node* root) const {
    if (root == nullptr) return -1;
    return 1 + std::max(depth(root->left), depth(root->right));
}

  void inorder(node* root, std::vector<std::pair<T, int>>& result) const {
    if (!root) return;
    inorder(root->left, result);
    result.push_back({root->data, root->count});
    inorder(root->right, result);
  }

  void clear(node* root) {
    if (!root) return;
    clear(root->left);
    clear(root->right);
    delete root;
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
