// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T value;
        int count;
        Node* left;
        Node* right;
        int height;

        explicit Node(const T& val)
            : value(val), count(1), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    int getHeight(Node* node) const {
        return node ? node->height : 0;
    }

    void updateHeight(Node* node) {
        if (node) {
            node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    int getBalance(Node* node) const {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);

        if (value == node->value) {
            node->count++;
            return node;
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        } else {
            node->right = insert(node->right, value);
        }

        updateHeight(node);

        int balance = getBalance(node);

        if (balance > 1 && value < node->left->value) {
            return rotateRight(node);
        }

        if (balance < -1 && value > node->right->value) {
            return rotateLeft(node);
        }

        if (balance > 1 && value > node->left->value) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && value < node->right->value) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    int searchCount(Node* node, const T& value) const {
        if (!node) return 0;
        if (value == node->value) return node->count;
        if (value < node->value)
            return searchCount(node->left, value);
        return searchCount(node->right, value);
    }

    int depth(Node* node) const {
        return getHeight(node);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        collect(node->left, result);
        result.push_back({node->value, node->count});
        collect(node->right, result);
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

    void insert(const T& value) {
        root = insert(root, value);
    }

    int search(const T& value) const {
        return searchCount(root, value);
    }

    int depth() const {
        return depth(root);
    }

    std::vector<std::pair<T, int>> getAllNodes() const {
        std::vector<std::pair<T, int>> result;
        collect(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
