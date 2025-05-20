// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>

template <typename T>
class BST {
   private:
    struct Node {
      T key;
      int count;
      Node* left;
      Node* right;
      explicit Node(const T& k)
          : key(k), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    void destroy(Node* node) {
      if (!node) return;
      destroy(node->left);
      destroy(node->right);
      delete node;
    }

    Node* insert(Node* node, const T& key) {
      if (!node) {
        return new Node(key);
      }
      if (key < node->key) {
        node->left = insert(node->left, key);
      } else if (node->key < key) {
        node->right = insert(node->right, key);
      } else {
        node->count++;
      }
      return node;
    }

    int search(Node* node, const T& key) const {
      if (!node) return 0;
      if (key < node->key)
        return search(node->left, key);
      else if (node->key < key)
        return search(node->right, key);
      else
        return node->count;
    }

    int depth(Node* node) const {
      if (!node) return -1;
      int dl = depth(node->left);
      int dr = depth(node->right);
      return 1 + (dl > dr ? dl : dr);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& v) const {
      if (!node) return;
      collect(node->left, v);
      v.emplace_back(node->key, node->count);
      collect(node->right, v);
    }

   public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& key) { root = insert(root, key); }
    int search(const T& key) const { return search(root, key); }
    int depth() const { return depth(root); }

    std::vector<std::pair<T, int>> toVector() const {
      std::vector<std::pair<T, int>> v;
      collect(root, v);
      return v;
    }
};


#endif  // INCLUDE_BST_H_
