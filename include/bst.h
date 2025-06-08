// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
class BST {
 private:
  struct TreeNode {
    T data;
    int quantity;
    TreeNode* rhs;
    TreeNode* lhs;
    explicit TreeNode(const T& val)
      : data(val), quantity(1), rhs(nullptr), lhs(nullptr) {
    }
  };
  TreeNode* head;

  void eraseTree(TreeNode* current) {
    if (!current) return;
    eraseTree(current->lhs);
    eraseTree(current->rhs);
    delete current;
  }

  int findHeight(TreeNode* current) const {
    if (!current) return 0;
    return std::max(findHeight(current->lhs), findHeight(current->rhs)) + 1;
  }

  TreeNode* insert(TreeNode* current, const T& val) {
    if (!current) return new TreeNode(val);
    if (current->data == val) {
      ++current->quantity;
      return current;
    }
    if (val < current->data) {
      current->lhs = insert(current->lhs, val);
    } else {
      current->rhs = insert(current->rhs, val);
    }
    return current;
  }

  int findQuantity(TreeNode* current, const T& val) const {
    if (!current) return 0;
    if (val == current->data) return current->quantity;
    return findQuantity(val < current->data ? current->lhs : current->rhs, val);
  }

  void traverse(TreeNode* current, std::vector<std::pair<T, int>>& output) const {
    if (!current) return;
    traverse(current->lhs, output);
    output.emplace_back(current->data, current->quantity);
    traverse(current->rhs, output);
  }

 public:
  BST() : head(nullptr) {}
  ~BST() { eraseTree(head); }

  void add(const T& value) {
    head = insert(head, value);
  }

  int search(const T& value) const {
    return findQuantity(head, value);
  }

  int depth() const {
    return findHeight(head) - 1;
  }

  std::vector<std::pair<T, int>> array_words() const {
    std::vector<std::pair<T, int>> output;
    traverse(head, output);
    return output;
  }
};

#endif  // INCLUDE_BST_H_
