// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
  struct Node {
    T data;
    int frequency;
    Node* left;
    Node* right;
        
    Node(const T& value) : data(value), frequency(1), left(nullptr), right(nullptr) {}
  };
    
  Node* root;
    
    // Helper function to insert a node
  Node* insertHelper(Node* node, const T& value) {
    if (node == nullptr) {
      return new Node(value);
    }
        
    if (value == node->data) {
      node->frequency++;
    } else if (value < node->data) {
      node->left = insertHelper(node->left, value);
    } else {
      node->right = insertHelper(node->right, value);
    }
        
    return node;
  }
    
  int depthHelper(Node* node) const {
    if (node == nullptr) return 0;
    return 1 + std::max(depthHelper(node->left), depthHelper(node->right));
  }
    
    // Helper function to delete the tree
  void deleteTree(Node* node) {
    if (node == nullptr) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
  }
    
    // Helper function to collect frequency data
  void collectFrequencyData(Node* node, std::vector<std::pair<T, int>>& data) const {
    if (node == nullptr) return;
    data.push_back({node->data, node->frequency});
    collectFrequencyData(node->left, data);
    collectFrequencyData(node->right, data);
  }

 public:
  BST() : root(nullptr) {}
    
  ~BST() {
    deleteTree(root);
  }
    
    // Insert a value into the tree
  void insert(const T& value) {
    root = insertHelper(root, value);
  }
    
    // Get the depth (height) of the tree
  int depth() const {
    return depthHelper(root);
  }
    
    // Search for a value in the tree, returns frequency if found, 0 if not found
  int search(const T& value) const {
    Node* current = root;
    while (current != nullptr) {
      if (value == current->data) {
        return current->frequency;
      }
      if (value < current->data) {
        current = current->left;
      } else {
        current = current->right;
      }
    }
  return 0;
  }
    
    // Get sorted frequency data
  std::vector<std::pair<T, int>> getFrequencyData() const {
    std::vector<std::pair<T, int>> data;
    collectFrequencyData(root, data);
    std::sort(data.begin(), data.end(),
           [](const auto& a, const auto& b) {
      return a.second > b.second;
    });
    return data;
  }
};
#endif  // INCLUDE_BST_H_
