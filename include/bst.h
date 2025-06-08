// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
template <typename T>
class BST {
private:
  struct Node {
      T keey;
      int countW;
      Node* leftt;
      Node* rightt;
      Node (T value) : keey (value), count (1), leftt (nullptr), rightt (nullptr) {}
  };
  Node* rootT;
  void insert (Node* node, const T& value) const {
    if (!node) {
      node = new Node (value);
    } else if (value < node -> keey) {
        insert (node -> leftt, value);
    } else if (value > node -> keey) {
        insert (node -> rightt, value);
    } else {
        node -> countW++;
    }
  }
  Node* search (Node* node, const T& value) const {
    if (!node || node -> keey == value) {
        return node; }
    if (value < node -> keey) {
      return search (node -> leftt, value); 
    } else {
      return search (node -> rightt, value);
    }
  }
  int depth (Node* node) const {
    if (!node) return 0;
    int lefttDepth = depth (node -> leftt);
    int righttDepth = depth (node -> rightt);
    return std::max(lefttDepth, righttDepth) + 1;
  }
  void collect (Node* node, std::vector<std::pair<T, int>>& out) const {
    if (!node) return;
    collect (node -> leftt, out);
    out.push_back ({node -> keey, node -> countW});
    collect (node -> rightt, out);   
  }
  void clear (Node* node) {
    if (!node) return;
    clear (node -> leftt);
    clear (node -> rightt);
    delete node;
  }
public:
  BST() : rootT (nullptr) {}
  ~BST() { clear (rootT); }
  void insert (const T& value) {
    insert (rootT, value);
  }
  bool search (const T& value) {
    return search (rootT, value) != nullptr;
  }
  int depth () const {
    return depth (rootT);
  }
  std::vector<std::pair<T, int>> getAll() const {
    std::vector<std::pair<T, int>> result;
    collect (rootT, result);
    return result;
  }
};

#endif  // INCLUDE_BST_H_
