// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T data;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& value) : data(value), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* addNode(Node* node, const T& value) {
        if (!node)
            return new Node(value);
        if (value < node->data)
            node->left = addNode(node->left, value);
        else if (value > node->data)
            node->right = addNode(node->right, value);
        else
            node->count++;
        return node;
    }

    Node* searchNode(Node* node, const T& value) const {
        if (!node)
            return nullptr;
        if (value == node->data)
            return node;
        else if (value < node->data)
            return searchNode(node->left, value);
        else
            return searchNode(node->right, value);
    }

    int depthNode(Node* node) const {
        if (!node)
            return 0;
        return 1 + std::max(depthNode(node->left), depthNode(node->right));
    }

    void inOrderTraversal(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (node) {
            inOrderTraversal(node->left, result);
            result.emplace_back(node->data, node->count);
            inOrderTraversal(node->right, result);
        }
    }

    void clearTree(Node* node) {
        if (node) {
            clearTree(node->left);
            clearTree(node->right);
            delete node;
        }
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        clearTree(root);
    }

    void add(const T& value) {
        root = addNode(root, value);
    }

    bool search(const T& value) const {
        return searchNode(root, value) != nullptr;
    }

    int depth() const {
        return depthNode(root);
    }

    void getAll(std::vector<std::pair<T, int>>& result) const {
        inOrderTraversal(root, result);
    }
};

#endif  // INCLUDE_BST_H_
