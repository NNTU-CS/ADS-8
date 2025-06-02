// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct node {
    T key;
    int count;
    node* right, * left;
    explicit node(const T& value) : key(value), count(1), right(nullptr), left(nullptr) {}
  };
  node* root;
  node* addNode(node* root, const T& value) {
    if (root == nullptr) {
      return new node(value);
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
  int get_depth(node* root) {
    if (root == nullptr) return 0;
    int left_depth = get_depth(root->left);
    int right_depth = get_depth(root->right);
    return (left_depth >= right_depth ? left_depth : right_depth) + 1;
  }
  int search_node(node* root, const T& value) {
    if (root == nullptr) return 0;
    if (value == root->key) return root->count;
    if (value < root->key) return search_node(root->left, value);
    else return search_node(root->right, value);
    }
  void clear(node* root) {
    if (root == nullptr) return;
    clear(root->left);
    clear(root->right);
    delete root;
  }
  void Order(node* root, std::vector<std::pair<T, int>>& res) const {
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
    return search_node(root, value);
  }
  int depth() {
    return get_depth(root)-1;
  }
  std::vector<std::pair<T, int>> array_words() const {
    std::vector<std::pair<T, int>> result;
    Order(root, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
