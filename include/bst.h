// Copyright 2025 NNTU-CS
#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>

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

    void insert(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
        } else if (value < node->key) {
            insert(node->left, value);
        } else if (value > node->key) {
            insert(node->right, value);
        } else {
            node->count++;
        }
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return std::max(leftDepth, rightDepth) + 1;
    }

    Node* search(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value < node->key)
            return search(node->left, value);
        else if (value > node->key)
            return search(node->right, value);
        else
            return node;
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
        if (!node) return;
        inorder(node->left, out);
        out.emplace_back(node->key, node->count);
        inorder(node->right, out);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& value) {
        insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& value) const {
        return search(root, value) != nullptr;
    }

    std::vector<std::pair<T, int>> getAllElements() const {
        std::vector<std::pair<T, int>> result;
        inorder(root, result);
        return result;
    }
};

#endif // BST_H
