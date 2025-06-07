// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <vector>

template <typename T>
class BST {
 private:
  struct TreeNode {
    T data;
    int times;
    TreeNode *rightNode, *leftNode;
    explicit TreeNode(const T& x) : data(x), times(1), rightNode(nullptr), leftNode(nullptr) {}
  };
  TreeNode* rootNode;
  TreeNode* push(TreeNode* curr, const T& x) {
    if (!curr) return new TreeNode(x);
    if (x == curr->data) {
      ++curr->times;
    } else if (x < curr->data) {
      curr->leftNode = push(curr->leftNode, x);
    } else {
      curr->rightNode = push(curr->rightNode, x);
    }
    return curr;
  }
  int measureDepth(TreeNode* curr) {
    return curr ? 1 + std::max(measureDepth(curr->leftNode), measureDepth(curr->rightNode)) : 0;
  }
  int findTimes(TreeNode* curr, const T& x) {
    while (curr) {
      if (x == curr->data) return curr->times;
      curr = (x < curr->data) ? curr->leftNode : curr->rightNode;
    }
    return 0;
  }
  void freeTree(TreeNode* curr) {
    if (!curr) return;
    freeTree(curr->leftNode);
    freeTree(curr->rightNode);
    delete curr;
  }
  void inOrder(TreeNode* curr, std::vector<std::pair<T, int>>& out) const {
    if (!curr) return;
    inOrder(curr->leftNode, out);
    out.emplace_back(curr->data, curr->times);
    inOrder(curr->rightNode, out);
  }
 public:
  BST() : rootNode(nullptr) {}
  ~BST() {
    freeTree(rootNode);
  }
  void add(const T& x) {
    rootNode = push(rootNode, x);
  }
  int search(const T& x) {
    return findTimes(rootNode, x);
  }
  int depth() {
    return measureDepth(rootNode) - 1;
  }
  std::vector<std::pair<T, int>> words() const {
    std::vector<std::pair<T, int>> out;
    inOrder(rootNode, out);
    return out;
  }
};

#endif  // INCLUDE_BST_H_
