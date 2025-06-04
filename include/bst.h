// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <algorithm>
template <typename T>
class BST {
 private:
   struct Node {
    T data;
    int count;
    Node* left;
    Node* right;
  };
   Node* root;
   Node* addNode(Node* root, T value);
   Node* delNode(Node* root, T value);
   void delTree(Node* root);
   int searchNode(Node* root, T value);
   void printTree(Node* root);
   int getHeight(Node* root);

 public:
   BST() : root(nullptr) {}
   ~BST();
   void add(T value);
   void del(T value);
   void clear();
   int search(T value);
   void print();
   int depth();
};

template <typename T>
typename BST<T>::Node* BST<T>::addNode(Node* root, T value) {
  if (root == nullptr) {
    root = new Node;
    root->data = value;
    root->count = 1;
    root->left = root->right = nullptr;
  } else if (value < root->data) {
    root->left = addNode(root->left, value);
  } else if (value > root->data) {
    root->right = addNode(root->right, value);
  } else
    root->count++;
  return root;
}


template <typename T>
BST<T>::~BST() {
  clear();
}

template <typename T>
void BST<T>::add(T value) {
  root = addNode(root, value);
}

template <typename T>
int BST<T>::searchNode(Node* root, T value) {
  if (root == nullptr)
    return 0;
  else if (value < root->data)
    return searchNode(root->left, value);
  else if (value > root->data)
    return searchNode(root->right, value);
  else
    return root->count;
}

template <typename T>
int BST<T>::search(T value) {
  return searchNode(root, value);
}

template <typename T>
void BST<T>::printTree(Node* root) {
  if (root == nullptr) return;
  printTree(root->left);
  for (int i = 0; i < root->count; i++) std::cout << root->data << " ";
  printTree(root->right);
}

template <typename T>
void BST<T>::print() {
  printTree(root);
  return;
}

template <typename T>
int BST<T>::getHeight(Node* root) {
  if (root == nullptr) return -1;
  int left = getHeight(root->left);
  int right = getHeight(root->right);
  return std::max(left, right) + 1;
}

template <typename T>
int BST<T>::depth() {
  return getHeight(root);
}

template <typename T>
void BST<T>::delTree(Node* root) {
  if (root == nullptr) return;
  delTree(root->left);
  delTree(root->right);
  delete root;
}

template <typename T>
void BST<T>::clear() {
  delTree(root);
  root = nullptr;
}

template <typename T>
typename BST<T>::Node* BST<T>::delNode(Node* root, T value) {
  Node *p, *v;
  if (root == nullptr)
    return root;
  else if (value < root->data)
    root->left = delNode(root->left, value);
  else if (value > root->data)
    root->right = delNode(root->right, value);
  else {
    p = root;
    if (root->right == nullptr)
      root = root->left;
    else if (root->left == nullptr)
      root = root->right;
    else {
      v = root->left;
      if (v->right != nullptr) {
        while (v->right->right != nullptr) v = v->right;
        root->data = v->right->data;
        root->count = v->right->count;
        p = v->right;
        v->right = v->right->left;
      } else {
        root->data = v->data;
        root->count = v->count;
        p = v;
        root->left = root->left->left;
      }
    }
    delete p;
  }
  return root;
}

template <typename T>
void BST<T>::del(T value) {
  root = delNode(root, value);
}


#endif  // INCLUDE_BST_H_
