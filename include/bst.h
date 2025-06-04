// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#pragma once
#include <iostream>
#include <functional>

template<typename T>
class BST {
 private:
    struct Node
    {
        T        key;
        int      freq;          // сколько раз встретилось слово
        Node*    left;
        Node*    right;

        explicit Node(const T& k)
            : key{k}, freq{1}, left{nullptr}, right{nullptr} {}
    };

    Node* root = nullptr;

 public:
    ~BST() { destroy(root); }

    void insert(const T& key) { insert(root, key); }

    int depth() const {
        if (!root) return 0;
        return height(root) - 1;
    }
    int search(const T& key) const {
        Node* n = find(root, key);
        return n ? n->freq : 0;
    }

    template<typename F>
    void forEachInOrder(F&& fn) const { inOrder(root, std::forward<F>(fn)); }
};

#endif  // INCLUDE_BST_H_
