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
        T key;
        int count;
        Node* left;
        Node* right;

        Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
        } else if (key < node->key) {
            insert(node->left, key);
        } else if (key > node->key) {
            insert(node->right, key);
        } else {
            node->count++;
        }
    }

    Node* find(Node* node, const T& key) const {
        if (!node) return nullptr;
        if (key < node->key) return find(node->left, key);
        if (key > node->key) return find(node->right, key);
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void inorder(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        inorder(node->left, vec);
        vec.push_back({node->key, node->count});
        inorder(node->right, vec);
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

    void insert(const T& key) {
        insert(root, key);
    }

    int search(const T& key) const {
        Node* node = find(root, key);
        return node ? node->count : 0;
    }

    int depth() const {
        return depth(root);
    }

    void toVector(std::vector<std::pair<T, int>>& vec) const {
        inorder(root, vec);
    }
};

#endif  // INCLUDE_BST_H_
