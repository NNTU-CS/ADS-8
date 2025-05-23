// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <vector>
#include <string>
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
    const Node* search(const Node* node, const T& key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        return search(key < node->key ? node->left : node->right, key);
    }
    int depth(const Node* node) const {
        if (!node) return 0;
        return 1 + std::max(depth(node->left), depth(node->right));
    }
    void inOrder(const Node* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inOrder(node->left, result);
        result.emplace_back(node->key, node->count);
        inOrder(node->right, result);
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
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
    void insert(const T& key) { insert(root, key); }
    bool search(const T& key) const { return search(root, key) != nullptr; }
    int getCount(const T& key) const {
        const Node* node = search(root, key);
        return node ? node->count : 0;
    }
    int depth() const { return depth(root); }
    std::vector<std::pair<T, int>> getAll() const {
        std::vector<std::pair<T, int>> result;
        result.reserve(10000);
        inOrder(root, result);
        return result;
    }
};
#endif  // INCLUDE_BST_H_
