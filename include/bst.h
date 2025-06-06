// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <utility>
#include <vector>
#include <algorithm>

template <typename T>
struct Node {
    T key;
    int cnt;
    Node* l;
    Node* r;
    explicit Node(const T& n) : key(n), cnt(1), l(nullptr), r(nullptr) {}
};
template <typename T>
class BST {
 public:
    BST() : rt(nullptr) {}
    ~BST() { destroyTree(rt); }
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
    void insert(const T& n) { rt = insertRecursive(rt, n); }
    int search(const T& n) const {
        Node<T>* f_n = searchNodeRecursive(rt, n);
        return f_n != nullptr ? f_n->cnt : 0;
    }
    int depth() const {
        return rt == nullptr ? 0 : depthRecursive(rt) - 1;
    }
    void getWordFrequencies(std::vector<std::pair<T, int>>& vec) const {
        getWordFrequenciesRecursive(rt, vec);
    }
 private:
    Node<T>* rt;
    Node<T>* insertRecursive(Node<T>* node, const T& n) {
        if (node == nullptr) {
            return new Node<T>(n);
        }
        if (n < node->key) {
            node->l = insertRecursive(node->l, n);
        } else if (n > node->key) {
            node->r = insertRecursive(node->r, n);
        } else {
            node->cnt++;
        }
        return node;
    }
    Node<T>* searchNodeRecursive(Node<T>* node, const T& n) const {
        if (node == nullptr || node->key == n) {
            return node;
        }
        return searchNodeRecursive(n < node->key ? node->l : node->r, n);
    }
    int depthRecursive(Node<T>* node) const {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(depthRecursive(node->l), depthRecursive(node->r));
    }
    void destroyTree(Node<T>* node) {
        if (node != nullptr) {
            destroyTree(node->l);
            destroyTree(node->r);
            delete node;
        }
    }
    void getWordFrequenciesRecursive(Node<T>* node, std::vector<std::pair<T, int>>& vec) const {
        if (node != nullptr) {
            getWordFrequenciesRecursive(node->l, vec);
            vec.emplace_back(node->key, node->cnt);
            getWordFrequenciesRecursive(node->r, vec);
        }
    }
};

#endif  // INCLUDE_BST_H_
#endif  // INCLUDE_BST_H_
