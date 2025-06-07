// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  struct TreeNode {
    T key;
    int freq;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(const T& val)
        : key(val), freq(1), left(nullptr), right(nullptr) {}
  };

  TreeNode* root;

  TreeNode* insert(TreeNode* curr, const T& val) {
    if (!curr) return new TreeNode(val);

    if (val == curr->key) {
      curr->freq++;
    } else if (val < curr->key) {
      curr->left = insert(curr->left, val);
    } else {
      curr->right = insert(curr->right, val);
    }
    return curr;
  }

  int getHeight(TreeNode* node) const {
    if (!node) return 0;
    int lh = getHeight(node->left);
    int rh = getHeight(node->right);
    return 1 + (lh > rh ? lh : rh);
  }

  int find(TreeNode* node, const T& val) const {
    if (!node) return 0;
    if (val == node->key) return node->freq;
    return val < node->key ? find(node->left, val) : find(node->right, val);
  }

  void destroy(TreeNode* node) {
    if (!node) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
  }

  void inOrder(TreeNode* node, std::vector<std::pair<T, int>>& result) const {
    if (!node) return;
    inOrder(node->left, result);
    result.emplace_back(node->key, node->freq);
    inOrder(node->right, result);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { destroy(root); }

  void add(const T& val) { root = insert(root, val); }

  int search(const T& val) const { return find(root, val); }

  int depth() const { return getHeight(root) - 1; }

  std::vector<std::pair<T, int>> getWords() const {
    std::vector<std::pair<T, int>> out;
    inOrder(root, out);
    return out;
  }
};

#endif  // INCLUDE_BST_H_
