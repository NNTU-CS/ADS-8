// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>

template <typename T>
class FrequencyTree {
 private:
  struct TreeNode {
    T data;
    int frequency;
    TreeNode* left;
    TreeNode* right;

    explicit TreeNode(const T& val)
        : data(val), frequency(1), left(nullptr), right(nullptr) {}
  };

  TreeNode* root_;

  void clearSubtree(TreeNode* node) {
    if (!node) return;
    clearSubtree(node->left);
    clearSubtree(node->right);
    delete node;
  }

  int calculateDepth(TreeNode* node) const {
    if (!node) return -1;
    return 1 + std::max(calculateDepth(node->left), 
                       calculateDepth(node->right));
  }

  TreeNode* findNode(TreeNode* node, const T& value) const {
    if (!node) return nullptr;
    if (value == node->data) return node;
    return findNode(value < node->data ? node->left : node->right, value);
  }

  void addNode(TreeNode*& node, const T& value) {
    if (!node) {
      node = new TreeNode(value);
      return;
    }
    if (value == node->data) {
      node->frequency++;
    } else {
      addNode(value < node->data ? node->left : node->right, value);
    }
  }

  void traverseInOrder(TreeNode* node, 
                      std::vector<std::pair<T, int>>* result) const {
    if (!node) return;
    traverseInOrder(node->left, result);
    result->emplace_back(node->data, node->frequency);
    traverseInOrder(node->right, result);
  }

 public:
  FrequencyTree() : root_(nullptr) {}
  ~FrequencyTree() { clearSubtree(root_); }

  void add(const T& value) { addNode(root_, value); }

  int getDepth() const {
    int d = calculateDepth(root_);
    return d < 0 ? 0 : d;
  }

  int getFrequency(const T& value) const {
    TreeNode* node = findNode(root_, value);
    return node ? node->frequency : 0;
  }

  std::vector<std::pair<T, int>> getAllItems() const {
    std::vector<std::pair<T, int>> items;
    traverseInOrder(root_, &items);
    return items;
  }
};
#endif  // INCLUDE_BST_H_
