// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>  // Для отладки

#include <algorithm>
#include <vector>
#include <utility>
#include <iostream>

template <typename T>
class BST {
private:
    struct TreeNode {
        T key;
        int freq;
        TreeNode* left;
        TreeNode* right;

        explicit TreeNode(const T& val)
            : key(val), freq(1), left(nullptr), right(nullptr) {}
    };

    TreeNode* root;

    TreeNode* insert(TreeNode* curr, const T& val) {
        if (!curr) return new TreeNode(val);

        if (val == curr->key) {
            curr->freq++;
        } else if (val < curr->key) {
            curr->left = insert(curr->left, val);
        } else {
            curr->right = insert(curr->right, val);
        }
        return curr;
    }

    int getHeight(TreeNode* node) const {
        if (!node) return -1;
        int lh = getHeight(node->left);
        int rh = getHeight(node->right);
        return 1 + std::max(lh, rh);
    }

    int findFreq(TreeNode* node, const T& val) const {
        if (!node) return 0;
        if (val == node->key) return node->freq;
        return val < node->key ? findFreq(node->left, val) : findFreq(node->right, val);
    }

    void destroy(TreeNode* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void inOrder(TreeNode* node, std::vector<std::pair<T, int>>& result) const {
        if (!node) return;
        inOrder(node->left, result);
        result.emplace_back(node->key, node->freq);
        inOrder(node->right, result);
    }

    TreeNode* copyTree(TreeNode* node) const {
        if (!node) return nullptr;
        TreeNode* newNode = new TreeNode(node->key);
        newNode->freq = node->freq;
        newNode->left = copyTree(node->left);
        newNode->right = copyTree(node->right);
        return newNode;
    }

public:
    BST() : root(nullptr) {}
    
    BST(const BST& other) {
        root = copyTree(other.root);
    }
    
    BST(BST&& other) noexcept : root(other.root) {
        other.root = nullptr;
    }
    
    ~BST() {
        destroy(root);
    }
    
    BST& operator=(const BST& other) {
        if (this != &other) {
            destroy(root);
            root = copyTree(other.root);
        }
        return *this;
    }
    
    BST& operator=(BST&& other) noexcept {
        if (this != &other) {
            destroy(root);
            root = other.root;
            other.root = nullptr;
        }
        return *this;
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    bool search(const T& value) const {
        TreeNode* curr = root;
        while (curr) {
            if (value == curr->key) return true;
            if (value < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    int depth() const {
        return getHeight(root);
    }

    int getCount(const T& value) const {
        return findFreq(root, value);
    }

    std::vector<std::pair<T, int>> inOrder() const {
        std::vector<std::pair<T, int>> result;
        inOrder(root, result);
        return result;
    }
};

#endif  // INCLUDE_BST_H_
