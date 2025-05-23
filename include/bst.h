// Copyright 2021 NNTU-CS
#ifndef BST_H
#define BST_H

#include <string>
#include <vector>
#include <utility>

template <typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void insert(Node*& node, const T& key) {
        if (!node) {
            node = new Node(key);
            return;
        }
        if (key == node->key) {
            node->count++;
        } else if (key < node->key) {
            insert(node->left, key);
        } else {
            insert(node->right, key);
        }
    }

    int search(Node* node, const T& key) const {
        if (!node) return 0;
        if (key == node->key) return node->count;
        return search(key < node->key ? node->left : node->right, key);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int left = depth(node->left);
        int right = depth(node->right);
        return 1 + (left > right ? left : right);
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

    void insert(const T& key) { insert(root, key); }
    int search(const T& key) const { return search(root, key); }
    int depth() const { return depth(root); }
};

#endif // BST_H
