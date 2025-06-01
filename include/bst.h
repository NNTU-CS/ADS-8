// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <functional> // для std::function

template <typename T>
class BST {
public:  // Сделали Node публичным, чтобы была возможность использовать вне класса
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

private:
    Node* root;

    Node* insert(Node* node, T value) {
       // pritf("%s", node);
        //pritf("%s", value);
        if (!node) return new Node(value);
        if (value == node->key) {
            node->count++;
        }
        else if (value < node->key) {
            node->left = insert(node->left, value);
        }
        else {
            node->right = insert(node->right, value);
        }
        return node;
    }

    Node* search(Node* node, T value) const {
          if (!node || node->key == value) return node;
        if (value < node->key) return search(node->left, value);
        return search(node->right, value);
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int leftDepth = depth(node->left);
        int rightDepth = depth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }


    void inOrder(Node* node, std::function<void(Node*)> visit) const {
        if (!node) return;
        inOrder(node->left, visit);
        visit(node);
        inOrder(node->right, visit);
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

    void insert(T value) {
        root = insert(root, value);
    }

    int depth() const {
        return depth(root);
    }

    bool search(T value) const {
        return search(root, value) != nullptr;
    }

    int getCount(T value) const {
        Node* node = search(root, value);
        return node ? node->count : 0;
    }

    void inOrder(std::function<void(Node*)> visit) const {
        inOrder(root, visit);
    }

};


#endif  // INCLUDE_BST_H_
