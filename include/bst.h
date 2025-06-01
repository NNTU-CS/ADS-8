#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
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

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    Node* insert(Node* node, const T& key) {
        if (!node) {
            return new Node(key);
        }
        if (key == node->key) {
            node->count++;
        } else if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }
        return node;
    }

    int search(Node* node, const T& key) const {
        if (!node) return 0;
        if (key == node->key) return node->count;
        if (key < node->key) return search(node->left, key);
        return search(node->right, key);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    template<typename Func>
    void inorder(Node* node, Func f) const {
        if (!node) return;
        inorder(node->left, f);
        f(node);
        inorder(node->right, f);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& key) {
        root = insert(root, key);
    }

    int search(const T& key) const {
        return search(root, key);
    }

    int depth() const {
        return depth(root);
    }

    template<typename Func>
    void inorder(Func f) const {
        inorder(root, f);
    }
};

#endif // BST_H
