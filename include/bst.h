// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <string>
#include <functional>

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

    Node* insert(Node* node, const T& value) {
        if (!node) return new Node(value);
        if (value < node->key) node->left = insert(node->left, value);
        else if (value > node->key) node->right = insert(node->right, value);
        else ++node->count;
        return node;
    }

    Node* search(Node* node, const T& value) const {
        if (!node) return nullptr;
        if (value < node->key) return search(node->left, value);
        if (value > node->key) return search(node->right, value);
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int dl = depth(node->left);
        int dr = depth(node->right);
        return std::max(dl, dr) + 1;
    }

    template<typename Vis>
    void traverseInOrder(Node* node, Vis vis) const {
        if (!node) return;
        traverseInOrder(node->left, vis);
        vis(node->key, node->count);
        traverseInOrder(node->right, vis);
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
        root = insert(root, value);
    }

    int search(const T& value) const {
        Node* n = search(root, value);
        return n ? n->count : 0;
    }

    int depth() const {
        if (!root) return 0;
        return depth(root) - 1;
    }

    template<typename Vis>
    void traverseInOrder(Vis vis) const {
        traverseInOrder(root, vis);
    }

    Node* getRoot() const {
        return root;
    }
};

#endif  // INCLUDE_BST_H_
