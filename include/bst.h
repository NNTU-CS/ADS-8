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
    explicit Node(const T& v) : key(v), count(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
 private:
    Node<T>* root = nullptr;

    void insert(Node<T>*& n, const T& v) {
        if (!n) n = new Node<T>(v);
        else if (v < n->key) insert(n->left, v);
        else if (v > n->key) insert(n->right, v);
        else n->count++;
    }

    int height(Node<T>* n) const {
        if (!n) return 0;
        return 1 + std::max(height(n->left), height(n->right));
    }

    bool search(Node<T>* n, const T& v) const {
        if (!n) return false;
        if (n->key == v) return true;
        return v < n->key ? search(n->left, v) : search(n->right, v);
    }

    void collect(Node<T>* n, std::vector<Node<T>*>& out) const {
        if (!n) return;
        collect(n->left, out);
        out.push_back(n);
        collect(n->right, out);
    }

 public:
    void insert(const T& v) { insert(root, v); }

    int depth() const {
        int h = height(root);
        return h > 0 ? h - 1 : 0;
    }

    bool search(const T& v) const { return search(root, v); }

    std::vector<Node<T>*> getNodes() const {
        std::vector<Node<T>*> v;
        collect(root, v);
        return v;
    }
};

#endif  // INCLUDE_BST_H_