// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <utility>
#include <algorithm>

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

    void insert(Node*& node, const T& key) {
        if (node == nullptr) {
            node = new Node(key);
        } else if (key == node->key) {
            ++node->count;
        } else if (key < node->key) {
            insert(node->left, key);
        } else {
            insert(node->right, key);
        }
    }

    Node* search(Node* node, const T& key) const {
        if (node == nullptr || node->key == key) return node;
        return (key < node->key)
                   ? search(node->left, key)
                   : search(node->right, key);
    }

    int depth(Node* node) const {
        if (node == nullptr) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node == nullptr) return;
        inorder(node->left, result);
        result.emplace_back(node->key, node->count);
        inorder(node->right, result);
    }

    void destroy(Node* node) {
        if (node == nullptr) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() { destroy(root); }

    void insert(const T& key) { insert(root, key); }

    bool search(const T& key) const { return search(root, key) != nullptr; }

    int depth() const { return depth(root); }

    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> result;
        inorder(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
