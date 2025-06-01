// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

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
        Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, T key) {
        if (!node) return new Node(key);
        if (key == node->key) {
            node->count++;
            return node;
        }
        if (key < node->key) 
            node->left = insert(node->left, key);
        else 
            node->right = insert(node->right, key);
        return node;
    }

    int depth(Node* node) const {
        if (!node) return 0;
        int left_depth = depth(node->left);
        int right_depth = depth(node->right);
        return 1 + (left_depth > right_depth ? left_depth : right_depth);
    }

    Node* search(Node* node, T key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key)
            return search(node->left, key);
        else
            return search(node->right, key);
    }

    void collectNodes(Node* node, std::vector<Node*>& nodes) const {
        if (!node) return;
        nodes.push_back(node);
        collectNodes(node->left, nodes);
        collectNodes(node->right, nodes);
    }

public:
    BST() : root(nullptr) {}
    
    void insert(T key) {
        root = insert(root, key);
    }

    int depth() const {
        return depth(root);
    }

    int search(T key) const {
        Node* result = search(root, key);
        return result ? result->count : 0;
    }

    std::vector<std::pair<T, int>> getAll() const {
        std::vector<Node*> nodePtrs;
        collectNodes(root, nodePtrs);
        std::vector<std::pair<T, int>> result;
        for (Node* node : nodePtrs) {
            result.push_back(std::make_pair(node->key, node->count));
        }
        return result;
    }
};

#endif  // INCLUDE_BST_H_
