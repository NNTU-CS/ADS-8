// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <algorithm>

template<typename T>
struct Node {
    T key;
    int count;
    Node* left;
    Node* right;
    explicit Node(const T& k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
 private:
    Node<T>* root = nullptr;

    Node<T>* insertRec(Node<T>* node, const T& val) {
        if (!node) return new Node<T>(val);
        if (val < node->key) {
            node->left = insertRec(node->left, val);
        } else if (node->key < val) {
            node->right = insertRec(node->right, val);
        } else {
            ++node->count;
        }
        return node;
    }

    int height(Node<T>* node) const {
        if (!node) return 0;
        int l = height(node->left);
        int r = height(node->right);
        return 1 + (l > r ? l : r);
    }

    int lookup(Node<T>* node, const T& val) const {
        if (!node) return 0;
        if (val < node->key) {
            return lookup(node->left, val);
        }
        if (node->key < val) {
            return lookup(node->right, val);
        }
        return node->count;
    }

    void collect(Node<T>* node, std::vector<Node<T>*>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.push_back(node);
        collect(node->right, out);
    }

    void clear(Node<T>* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

 public:
    BST() = default;
    ~BST() { clear(root); }

    void insert(const T& val) {
        root = insertRec(root, val);
    }

    int search(const T& val) const {
        return lookup(root, val);
    }

    int depth() const {
        int h = height(root);
        return h > 0 ? h - 1 : 0;
    }

    std::vector<Node<T>*> getNodes() const {
        std::vector<Node<T>*> out;
        collect(root, out);
        return out;
    }
};

#endif  // INCLUDE_BST_H_