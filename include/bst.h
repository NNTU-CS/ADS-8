#pragma once
// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <vector>
#include <utility>


template<typename T>
class BST {
private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
  };
  Node* root;

  Node* addNode(Node* root, T value) {
    if (root == nullptr) {
      return new Node{ value, 1, nullptr, nullptr };
    }

    if (value > root->data) {
      root->right = addNode(root->right, value);
    } else if (value < root->data) {
      root->left = addNode(root->left, value);
    } else {
      root->count++;
    }

    return root;
  }

  Node* delNode(Node* root, T value) {
    Node *temp1, *temp2;

    if (root == nullptr) {
      return nullptr;
    }

    if (value < root->data) {
      root->left = delNode(root->left, value);
    } else if (value > root->data) {
      root->right = delNode(root->right, value);
    } else {
      temp1 = root;
      if (root->left == nullptr) {
        root = root->right;
      } else if (root->right == nullptr) {
        root = root->left;
      } else {
        temp2 = root->right;
        if (temp2->left != nullptr) {
          while (temp2->left->left != nullptr) {
            temp2 = temp2->left;
          }

          root->data = temp2->left->data;
          root->count = temp2->left->count;
          temp1 = temp2->left;
          temp2 = temp2->left->right;
        } else {
          root->data = temp2->data;
          root->count = temp2->count;
          temp1 = temp2;
          root->right = root->right->right;
        }
      }

      delete temp1;
    }
    
    return root;
  }

  void delTree(Node*& root) {
    if (root == nullptr) {
      return;
    }

    delTree(root->left);
    delTree(root->right);
    
    delete root;
    root = nullptr;
  }

  int searchNode(Node* root, T value) {
    if (root == nullptr) {
      return 0;
    }

    if (value == root->data) {
      return root->count;
    } else if (value > root->data) {
      return searchNode(root->right, value);
    } else {
      return searchNode(root->left, value);
    }
  }

  void printTree(Node* root) {
    if (root == nullptr) {
      return;
    }

    printTree(root->left);
    for (int i = 0; i < root->count; ++i) {
      std::cout << root->data << ' ';
    }

    printTree(root->right);
  }

  int getDepth(Node* root) {
    if (root == nullptr) {
      return 0;
    }

    if (root->left == nullptr && root->right == nullptr) {
      return 0;
    }
    
    int left = getDepth(root->left);
    int right = getDepth(root->right);
    return std::max(left, right) + 1;
  }

  void getFrequencies(Node* root, std::vector<std::pair<T, int>>& frequencies) const {
    if (root == nullptr) {
      return;
    }
    getFrequencies(root->left, frequencies);
    frequencies.push_back(std::make_pair(root->data, root->count));
    getFrequencies(root->right, frequencies);
  }
public:
  BST() : root(nullptr) {}

  ~BST() {
    delTree(root);
  }

  void add(T value) {
    root = addNode(root, value);
  }

  Node* del(T value) {
    return delNode(root, value);
  }

  void clear() {
    delTree(root);
  }

  int search(T value) {
    return searchNode(root, value);
  }

  void print() {
    printTree(root);
  }

  int depth() {
    return getDepth(root);
  }

  Node* getRoot() {
    return root;
  }

  std::vector<std::pair<T, int>> getFrequencies() const {
    std::vector<std::pair<T, int>> frequencies;
    getFrequencies(root, frequencies);
    return frequencies;
  }
};

#endif  // INCLUDE_BST_H_
