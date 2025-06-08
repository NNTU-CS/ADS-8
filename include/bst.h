// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <vector>
#include <utility>
template <typename T>
class BST {
  private:
  struct Node {
      T keey;
      int countW;
      Node* leftt;
      Node* rightt;
      Node (T value) : key (value), count (1), left (nullptr), right (nullptr) {}
  };
  Node* rootT;
  void insert (Node* node, const T& value) const {
    if (!node) {
      node = new Node (value);
    } else if (value < node -> key) {
        insert(node -> left, value);
    } else if (value > node -> key) {
        insert(node -> right, value);
    } else {
        node -> countW++;
    }
  }
  Node* search (Node* node, const T& value) const {
    if (!node || node -> key == value) {
        return node; }
    if (value < node -> key) {
      return search(node -> left, value); 
    } else {
      return search(node -> right, value);
    }
  }
  int depth (Node* node) const {
    if (!node) return 0;
    int lefttDepth = depth(node -> left);
    int righttDepth = depth(node -> right);
    return std::max(lefttDepth, righttDepth) + 1;
  }
  void collect (Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    collect(node -> left, out);
    out.push_back({node -> key, node -> countW});
    collect(node -> right, out);   
  }
  void clear (Node* node) {
    if (!node) return;
    clear(node -> left);
    clear(node -> right);
    delete node;
  }
  public:
  BST() : rootT (nullptr) {}
  ~BST() { clear(rootT); }
  void insert (const T& value) {
    insert(rootT, value);
  }
  bool search (const T& value) {
    return search(rootT, value) != nullptr;
  }
  int depth () const {
    return depth(rootT);
  }
  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    collect(rootT, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
