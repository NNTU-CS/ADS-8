// Copyright 2021 NNTU-CS
#include <iostream>
#include <vector>
#include <algorithm>
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
template<typename T>
class BST {
public:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;
  };

private:
  Node* root;
  Node* addNode(Node*, T);
  void printTree(Node*);
  int depthTree(Node*);
  int searchNode(Node*, const T&) const;
  void delTree(Node*);
  Node* delNode(Node*, int);
  void collect(Node*, std::vector<Node*>&) const;

public:
  BST();
  ~BST();
  void add(T);
  void print();
  int depth() const;
  int search(const T&) const;
  void clear();
  void remove(int);
  std::vector<Node*> getAllNodes() const;
};

template<typename T>
BST<T>::BST() : root(nullptr) {}

template<typename T>
BST<T>::~BST() {
  if (root)
    delTree(root);
}

template<typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
  if (root == nullptr) {
    root = new Node;
    root->value = value;
    root->count = 1;
    root->left = root->right = nullptr;
  }
  else if (root->value > value) {
    root->left = addNode(root->left, value);
  }
  else if (root->value < value) {
    root->right = addNode(root->right, value);
  }
  else
    root->count++;
  return root;
}

template<typename T>
void BST<T>::add(T value) {
  root = addNode(root, value);
}

template<typename T>
void BST<T>::printTree(Node* root) {
  if (root == nullptr)
    return;
  printTree(root->left);
  std::cout << root->value << " (" << root->count << ")\n";
  printTree(root->right);
}

template<typename T>
void BST<T>::print() {
  printTree(root);
}

template<typename T>
void BST<T>::delTree(Node* root) {
  if (root == nullptr)
    return;
  delTree(root->left);
  delTree(root->right);
  delete root;
}

template<typename T>
void BST<T>::clear() {
  if (root) {
    delTree(root);
    root = nullptr;
  }
}

template<typename T>
typename BST<T>::Node* BST<T>::delNode(typename BST<T>::Node* root, int value) {
  Node* p, * v;
  if (root == nullptr)
    return root;
  else if (value < root->value)
    root->left = delNode(root->left, value);
  else if (value > root->value)
    root->right = delNode(root->right, value);
  else {
    p = root;
    if (root->right == nullptr)
      root = root->left;
    else if (root->left == nullptr)
      root = root->right;
    else {
      v = root->left;
      if (v->right) {
        while (v->right->right)
          v = v->right;
        root->value = v->right->value;
        root->count = v->right->count;
        p = v->right;
        v->right = v->right->left;
      }
      else {
        root->value = v->value;
        root->count = v->count;
        p = v;
        root->left = root->left->left;
      }
    }
    delete p;
  }
  return root;
}

template<typename T>
void BST<T>::remove(int value) {
  if (root)
    root = delNode(root, value);
}

template<typename T>
int BST<T>::depthTree(Node* root) {
  if (root == nullptr)
    return 0;
  int left = depthTree(root->left);
  int right = depthTree(root->right);
  return (left > right) ? left + 1 : right + 1;
}

template<typename T>
int BST<T>::depth() const {
  return depthTree(root);
}

template<typename T>
int BST<T>::searchNode(Node* root, const T& value) const {
  if (root == nullptr)
    return 0;
  if (root->value == value)
    return root->count;
  if (value < root->value)
    return searchNode(root->left, value);
  return searchNode(root->right, value);
}

template<typename T>
int BST<T>::search(const T& value) const {
  return searchNode(root, value);
}

template<typename T>
void BST<T>::collect(Node* root, std::vector<Node*>& nodes) const {
  if (root == nullptr)
    return;
  collect(root->left, nodes);
  nodes.push_back(root);
  collect(root->right, nodes);
}

template<typename T>
std::vector<typename BST<T>::Node*> BST<T>::getAllNodes() const {
  std::vector<Node*> nodes;
  collect(root, nodes);
  return nodes;
}
#endif  // INCLUDE_BST_H_
