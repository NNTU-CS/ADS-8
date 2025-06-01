// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <iostream>
#include <string>
#include <algorithm>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        int cnt;
        Node* lft;
        Node* rght;
        explicit Node(T k) : key(k), cnt(1), lft(nullptr), rght(nullptr) {}
    };

    Node* root;

    Node* insrt(Node* node, T value) {
        if (!node) return new Node(value);
        if (value == node->key) {
            node->cnt++;
        } else if (value < node->key) {
            node->lft = insrt(node->lft, value);
        } else {
            node->rght = insrt(node->rght, value);
        }
        return node;
    }

    int depth(Node* node) const {
        if (!node) return -1;
        int lDepth = depth(node->lft);
        int rDepth = depth(node->rght);
        return std::max(lDepth, rDepth) + 1;
    }

    Node* search(Node* node, T value) const {
        if (!node || node->key == value) {
            return node;
        }
        if (value < node->key) {
            return search(node->lft, value);
        } else {
            return search(node->rght, value);
        }
    }

    template <typename Func>
    void inOrd(Node* node, Func visit) const {
        if (!node) return;
        inOrd(node->lft, visit);
        visit(node);
        inOrd(node->rght, visit);
    }

    void clear(Node* node) {
        if (!node) return;
        clear(node->lft);
        clear(node->rght);
        delete node;
    }

 public:
    using Node = struct Node;
    BST() : root(nullptr) {}
    ~BST() {
        clear(root);
    }

    void insrt(T value) {
        root = insrt(root, value);
    }

    int depth() const {
        return depth(root);
    }

    int search(T value) const {
        Node* found = search(root, value);
        return found ? found->cnt : 0;
    }

    template <typename Func>
    void inOrd(Func visit) const {
        inOrd(root, visit);
    }
};

#endif  // INCLUDE_BST_H_
