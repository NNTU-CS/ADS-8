// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>

template<typename T>
struct Node {
  T key;
  size_t count;
  Node *left;
  Node *right;
  Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
};
template<typename T>
class BST {
private:
  Node<T>* root;
public:
  BST() : root(nullptr) {}
  ~BST();
  bool insert(const T&);
  bool search(const T&);
  size_t depth();
  void inorder(std::vector<Node<T>*>&);
  void printFrequency();
};
template<typename T>
BST<T>::~BST() {
  auto destroy = [](Node<T>* node) {
    if(node != nullptr){
      destroy(node->left);
      destroy(node->right);
      delete node;
    }
  };
  destroy(root);
}
template<typename T>
bool BST<T>::insert(const T& val) {
  if (root == nullptr) {
    root = new Node<T>(val);
    return true;
  }
  Node<T>* current = root;
  while(true) {
    if(val == current->key){
      ++current->count;
      break;
    }
    if(val < current->key) {
      if(current->left == nullptr) {
        current->left = new Node<T>(val);
        break;
      }
      else{
        current = current->left;
      }
    }
    else {
      if(current->right == nullptr) {
        current->right = new Node<T>(val);
        break;
      }
      else{
        current = current->right;
      }
    }
  }
  return true;
}
template<typename T>
bool BST<T>::search(const T& val) {
  Node<T>* current = root;
  while(current != nullptr && current->key != val) {
    if(val < current->key) {
      current = current->left;
    }
    else {
      current = current->right;
    }
  }
  return current != nullptr;
}
template<typename T>
size_t BST<T>::depth(Node<T>* node) {
  if(node == nullptr) return 0;
  return 1 + std::max(depth(node->left), depth(node->right));
}
template<typename T>
size_t BST<T>::depth(){
  return depth(root);
}
template<typename T>
void BST<T>::inorder(std::vector<Node<T>*>& vec, Node<T>* node) {
  if(node != nullptr) {
    inorder(vec, node->left);
    vec.push_back(node);
    inorder(vec, node->right);
  }
}
template<typename T>
void BST<T>::inorder(std::vector<Node<T>*>& vec) {
  inorder(vec, root);
}
template<typename T>
void BST<T>::printFrequency() {
  std::vector<Node<T>*> nodes;
  inorder(nodes);
  std::sort(nodes.begin(), nodes.end(),
            [](const Node<T>* a, const Node<T>* b) {
              return a->count > b->count || (a->count == b->count && a->key < b->key);
            });

  for(auto n : nodes) {
    std::cout << n->key << ": " << n->count << "\n";
  }
}
#endif  // INCLUDE_BST_H_
