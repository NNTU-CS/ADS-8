// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <vector>
#include <algorithm>
#include <string>

template <typename T>
class BST {
 private:
  struct Node {
    explicit Node(const T& k)
      : key(k), count(1), left(nullptr), right(nullptr) {}
    T key;
    int count;
    Node* left;
    Node* right;
  };

  Node* root;
    Node* insertRec(Node* node, const T& key) {
        if (!node) return new Node(key);
        if (key == node->key) {
            node->count++;
        } else if (key < node->key) {
            node->left = insertRec(node->left, key);
        } else {
            node->right = insertRec(node->right, key);
        }
        return node;
    }
    int depthRec(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depthRec(node->left), depthRec(node->right));
    }
    Node* searchRec(Node* node, const T& key) const {
        if (!node || node->key == key) return node;
        return searchRec(key < node->key ? node->left : node->right, key);
    }
    void collectNodes(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        collectNodes(node->left, vec);
        vec.emplace_back(node->key, node->count);
        collectNodes(node->right, vec);
    }
    void deleteTree(Node* node) {
        if (!node) return;
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { deleteTree(root); }
    void insert(const T& key) { root = insertRec(root, key); }
    int depth() const { return depthRec(root); }
    int search(const T& key) const {
        Node* node = searchRec(root, key);
        return node ? node->count : 0;
    }
    std::vector<std::pair<T, int>> getAll() const {
        std::vector<std::pair<T, int>> result;
        collectNodes(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
