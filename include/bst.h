// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>

template<typename T>
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

    void insert(Node*& node, const T& key) {
        if (!node)
            node = new Node(key);
        else if (key < node->key)
            insert(node->left, key);
        else if (key > node->key)
            insert(node->right, key);
        else
            node->count++;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int l = depth(node->left);
        int r = depth(node->right);
        return 1 + std::max(l, r);
    }

    Node* search(Node* node, const T& key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        return key < node->key ? search(node->left, key) : search(node->right, key);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void inOrder(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        inOrder(node->left, vec);
        vec.push_back({node->key, node->count});
        inOrder(node->right, vec);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& key) { insert(root, key); }
    int depth() const { return depth(root); }
    bool search(const T& key) const { return search(root, key) != nullptr; }

    std::vector<std::pair<T, int>> toVector() const {
        std::vector<std::pair<T, int>> vec;
        inOrder(root, vec);
        return vec;
    }
};

#endif  // INCLUDE_BST_H_
