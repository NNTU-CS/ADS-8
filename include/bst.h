// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <queue>
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& v)
        : value(v), count(1), left(nullptr), right(nullptr) {}
  };
  Node* root;

  void clearNodes(Node* n) {
    if (!n) return;
    clearNodes(n->left);
    clearNodes(n->right);
    delete n;
  }

  void collectPostOrder(Node* n, std::vector<std::pair<T, int>>& out) const {
    if (!n) return;
    collectPostOrder(n->left, out);
    collectPostOrder(n->right, out);
    out.emplace_back(n->value, n->count);
  }

 public:
  BST() : root(nullptr) {}
  ~BST() { clearNodes(root); }

  void insert(const T& v) {
    if (!root) {
      root = new Node(v);
      return;
    }
    Node* cur = root;
    while (true) {
      if (v < cur->value) {
        if (cur->left) {
          cur = cur->left;
        } else {
          cur->left = new Node(v);
          return;
        }
      } else if (v > cur->value) {
        if (cur->right) {
          cur = cur->right;
        } else {
          cur->right = new Node(v);
          return;
        }
      } else {
        cur->count++;
        return;
      }
    }
  }

  int search(const T& v) const {
    Node* cur = root;
    while (cur) {
      if (v < cur->value) {
        cur = cur->left;
      } else if (v > cur->value) {
        cur = cur->right;
      } else {
        return cur->count;
      }
    }
    return 0;
  }

  int depth() const {
    if (!root) return -1;
    std::queue<Node*> q;
    q.push(root);
    int levels = -1;
    while (!q.empty()) {
      int sz = q.size();
      levels++;
      for (int i = 0; i < sz; ++i) {
        Node* n = q.front();
        q.pop();
        if (n->left) q.push(n->left);
        if (n->right) q.push(n->right);
      }
    }
    return levels;
  }

  void getAll(std::vector<std::pair<T, int>>& out) const {
    collectPostOrder(root, out);
  }
};


#endif  // INCLUDE_BST_H_
