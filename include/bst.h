// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
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
        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, const T& key) {
        if (!node) return new Node(key);
        if (key == node->key) {
            node->count++;
            return node;
        }
        if (key < node->key)
            node->left = insert(node->left, key);
        else
            node->right = insert(node->right, key);
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    Node* search(Node* node, const T& key) const {
        if (!node || node->key == key) return node;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
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

    bool search(const T& key) const {
        return search(root, key) != nullptr;
    }

    std::vector<std::pair<T, int>> inOrder() const {
        std::vector<std::pair<T, int>> result;
        inOrder(root, result);
        return result;
    }
};
#endif  // INCLUDE_BST_H_
