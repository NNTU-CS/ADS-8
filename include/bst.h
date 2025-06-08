// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <string>
#include <utility>

template <typename T>
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
    void Clear(Node* node) {
        if (!node) return;
        Clear(node->left);
        Clear(node->right);
        delete node;
    }
    void Insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        } else if (key == node->key) {
            node->count++;
        } else {
            key < node->key ? insert(node->left, key) : insert(node->right, key);
        }
    }
    int Search(Node* node, const T& key) const {
        return !node ? 0 :
               key == node->key ? node->count :
               Search(key < node->key ? node->left : node->right, key);
    }
    int Depth(Node* node) const {
        return !node ? -1 :
               1 + std::max(Depth(node->left), Depth(node->right));
    }
    void InOrder(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        inorder(node->left, vec);
        vec.push_back({node->key, node->count});
        inorder(node->right, vec);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    void Insert(const T& key) { Insert(root, key); }
    int Search(const T& key) const { return Search(root, key); }
    int Depth() const { return Depth(root); }
    std::vector<std::pair<T, int>> getAll() const {
        std::vector<std::pair<T, int>> vec;
        InOrder(root, vec);
        return vec;
    }
};

#endif  // INCLUDE_BST_H_
