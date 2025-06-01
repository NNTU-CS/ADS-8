// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#endif  // INCLUDE_BST_H_
#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T val;
        int ocCount;
        Node* left;
        Node* right;
        explicit Node(const T& t) : val(t), ocCount(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* add(Node* node, const T& t) {
        if (!node) {
            return new Node(t);
        }
        if (t == node->val) {
            node->ocCount++;
            return node;
        }
        if (t < node->val) {
            node->left = insert(node->left, t);
        } else {
            node->right = insert(node->right, t);
        }
        return node;
    }

    int depthTree(Node* node) const {
        if (!node) return -1;
        int lDepth = depthTree(node->left);
        int rDepth = depthTree(node->right);
        return 1 + (lDepth > rDepth ? lDepth : rDepth);
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
        root = add(root, value);
    }

    int search(const T& value) const {
        Node* node = root;
        while (node) {
            if (value == node->val) {
                return node->ocCount;
            }
            if (value < node->val) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return 0;
    }

    int depth() const {
        return depthTree(root);
    }
};

#endif // INCLUDE_BST_H_
