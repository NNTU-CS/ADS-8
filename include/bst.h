// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <functional>

template <typename T>
class BST {
public:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(T value) : key(value), count(1), left(nullptr), right(nullptr) {}
    };

private:
    Node* rootNode;

    Node* insert(Node* currentNode, T value) {
        if (!currentNode) return new Node(value);
        if (value == currentNode->key) {
            currentNode->count++;
        }
        else if (value < currentNode->key) {
            currentNode->left = insert(currentNode->left, value);
        }
        else {
            currentNode->right = insert(currentNode->right, value);
        }
        return currentNode;
    }

    Node* search(Node* currentNode, T value) const {
        if (!currentNode || currentNode->key == value) return currentNode;
        if (value < currentNode->key) return search(currentNode->left, value);
        return search(currentNode->right, value);
    }

    int depth(Node* currentNode) const {
        if (!currentNode) return 0;
        int leftSubtree = depth(currentNode->left);
        int rightSubtree = depth(currentNode->right);
        return 1 + (leftSubtree > rightSubtree ? leftSubtree : rightSubtree);
    }

    void inOrder(Node* currentNode, std::function<void(Node*)> visit) const {
        if (!currentNode) return;
        inOrder(currentNode->left, visit);
        visit(currentNode);
        inOrder(currentNode->right, visit);
    }

public:
    BST() : rootNode(nullptr) {}

    void insert(T value) {
        rootNode = insert(rootNode, value);
    }

    int getCount(T value) const {
        Node* foundNode = search(rootNode, value);
        return foundNode ? foundNode->count : 0;
    }

    int depth() const {
        return depth(rootNode)-1;
    }

    void inOrder(std::function<void(Node*)> visit) const {
        inOrder(rootNode, visit);
    }
};
#endif  // INCLUDE_BST_H_
