// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <vector>
#include <algorithm>

emplate <typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    Node* insert(Node* node, const T& key) {
        if (!node) return new Node(key);
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        } else {
            node->count++;
        }
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inOrder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inOrder(node->left, result);
        result.emplace_back(node->key, node->count);
        inOrder(node->right, result);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& key) {
        root = insert(root, key);
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int>> inOrder() const {
        std::vector<std::pair<T, int>> result;
        inOrder(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
