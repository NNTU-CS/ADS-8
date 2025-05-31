// Copyright 2021 NNTU-CS
#ifndef BST_H
#define BST_H

#include <iostream>
#include <algorithm>
#include <string>

template <typename T>
class BST {
public:
    BST() : root(nullptr), tree_size(0) {}

    void insert(const T& value) {
        root = insertNode(root, value);
        ++tree_size;
    }

    int depth() const {
        return nodeDepth(root);
    }

    int size() const {
        return tree_size;
    }

private:
    struct Node {
        T data;
        std::unique_ptr<Node> left;
        std::unique_ptr<Node> right;

        Node(const T& val) : data(val), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<Node> root;
    int tree_size;

    std::unique_ptr<Node> insertNode(std::unique_ptr<Node>& node, const T& value) {
        if (!node) {
            return std::make_unique<Node>(value);
        }
        if (value < node->data) {
            node->left = insertNode(node->left, value);
        } else {
            node->right = insertNode(node->right, value);
        }
        return std::move(node);
    }

    int nodeDepth(const std::unique_ptr<Node>& node) const {
        if (!node) return 0;
        return 1 + std::max(nodeDepth(node->left), nodeDepth(node->right));
    }
};

#endif // BST_H
