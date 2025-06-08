// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <vector>
#include <map>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        Node(const T& k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        }
        else if (key < node->key) {
            insert(node->left, key);
        }
        else if (key > node->key) {
            insert(node->right, key);
        }
        else {
            node->count++;
        }
    }

    Node* search(Node* node, const T& key) const {
        if (!node || node->key == key)
            return node;
        return (key < node->key)
               ? search(node->left, key)
               : search(node->right, key);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int l = depth(node->left);
        int r = depth(node->right);
        return 1 + std::max(l, r);
    }

    void inorder(Node* node,
std::vector<std::pair<T, int>>& output) const {
        if (!node) return;
        inorder(node->left, output);
        output.push_back({ node->key, node->count });
        inorder(node->right, output);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

 public:
    BST() : root(nullptr) {}

    ~BST() {
        destroy(root);
    }

    void insert(const T& key) {
        insert(root, key);
    }

    int depth() const {
        return depth(root);
    }

    bool search(const T& key) const {
        return search(root, key) != nullptr;
    }

    void collect(
std::vector<std::pair<T, int>>& output) const {
        inorder(root, output);
    }
};

#endif  // INCLUDE_BST_H_
