// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

template<typename T>
class BST {
 private:
  struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
    Node(const T& d) : data(d), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;
  void addNode(Node*& node, const T& value);
  int depth(Node* node) const;
  Node* searchNode(Node* node, const T& value) const;
  void inorder(Node* node, vector<pair<T, int>>& result) const;
  void clear(Node* node);

 public:
  BST() : root(nullptr) {}
  ~BST() { clear(root); }
  void add(const T& value) { addNode(root, value); }
  int depthOb() const { return depth(root); }
  Node* search(const T& value) const { return searchNode(root, value); }
  void toVector(vector<pair<T, int>>& result) const { inorder(root, result); }
};

template<typename T>
void BST<T>::addNode(Node*& node, const T& value) {
  if (!node)
    node = new Node(value);
  else if (value == node->data)
    node->count++;
  else if (value < node->data)
    addNode(node->left, value);
  else
    addNode(node->right, value);
}

template<typename T>
int BST<T>::depth(Node* node) const {
  if (!node)
    return 0;
  return 1 + max(depth(node->left), depth(node->right));
}

template<typename T>
typename BST<T>::Node* BST<T>::searchNode(Node* node, const T& value) const {
  if (!node)
    return nullptr;
  if (value == node->data)
    return node;
  if (value < node->data)
    return search(node->left, value);
  else
    return search(node->right, value);
}

template<typename T>
void BST<T>::inorder(Node* node, vector<pair<T, int>>& result) const {
  if (!node)
    return;
  inorder(node->left, result);
  result.push_back({ node->data, node->count });
  inorder(node->right, result);
}

template<typename T>
void BST<T>::clear(Node* node) {
  if (!node) return;
  clear(node->left);
  clear(node->right);
  delete node;
}
#endif  // INCLUDE_BST_H_
