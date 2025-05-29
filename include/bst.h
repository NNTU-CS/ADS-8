// Copyright 2021 NNTU-CS
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

template <typename T>
class BST {
private:
  struct Node {
    T key;
    int count;
    Node* left = nullptr;
    Node* right = nullptr;
    explicit Node(const T& word) : key(word), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root = nullptr;
  Node* insert_helper(Node* node, const T& word) {
    if (!node) return new Node(word);
    if (word < node->key) {
      node->left = insert_helper(node->left, word);
    } else if (word > node->key) {
        node->right = insert_helper(node->right, word);
    } else {
        node->count++;
    }
    return node;
  }

  void delete_tree(Node* node) {
    if (!node) return;
    delete_tree(node->left);
    delete_tree(node->right);
    delete node;
  }

  int search_helper(Node* node, const T& key) {
    if (!node) return 0;
    if (key < node->key) {
      return search_helper(node->left, key);
    } else if (key > node->key) {
        return search_helper(node->right, key);
    } else {
        return node->count;
    }
  }

  int depth_helper(Node* node) {
    if (!node) return 0;
    int left_depth = depth(node->left);
    int right_depth = depth(node->right);
    return (right_depth > left_depth ? right_depth : left_depth);
  }

  void build(Node* node, std::vector<std::pair<T, int>>& map) {
    if (!node) return;
    build(node->left, map);
    map.emplace_back(node->key, node->count);
    build(node->right, map);
  }

public:
  BST() : root(nullptr) {}
  ~BST() { delete_tree(root); }
  void insert(const T& word) { root = insert_helper(root, word); }
  int search(const T& key) { return search_helper(root, key); }
  int depth() { return depth_helper(root); }
  std::vector<std::pair<T, int>> toVector() {
    std::vector<std::pair<T, int>> res;
    this->build(this->root, res);
    std::sort(res.begin(), res.end(), [](auto& a, auto& b) { return a.second > b.second; });
    return res;
  }
};

#endif  // INCLUDE_BST_H_
