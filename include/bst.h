// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

template <typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
private:
    Node<T>* root;

    Node<T>* insert(Node<T>* node, const T& key) {
        if (!node) return new Node<T>(key);
        if (key == node->key) {
            node->count++;
            return node;
        }
        if (key < node->key) {
            node->left = insert(node->left, key);
        } else {
            node->right = insert(node->right, key);
        }
        return node;
    }

    Node<T>* searchNode(Node<T>* node, const T& key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        return key < node->key ? searchNode(node->left, key) : searchNode(node->right, key);
    }

    int depth(Node<T>* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }

    void destroy(Node<T>* node) {
        if (node) {
            destroy(node->left);
            destroy(node->right);
            delete node;
        }
    }

    void inOrder(Node<T>* node, std::vector<Node<T>*>& nodes) const {
        if (!node) return;
        inOrder(node->left, nodes);
        nodes.push_back(node);
        inOrder(node->right, nodes);
    }

public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& key) { root = insert(root, key); }

    int search(const T& key) const {
        Node<T>* node = searchNode(root, key);
        return node ? node->count : 0;
    }

    int depth() const { return depth(root); }

    std::vector<Node<T>*> getAllNodes() const {
        std::vector<Node<T>*> nodes;
        inOrder(root, nodes);
        return nodes;
    }
};

#endif  // INCLUDE_BST_H_
