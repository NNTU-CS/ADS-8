// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <cstddef>
#include <functional>

template <typename T>
class BST {
 private:
    struct Node {
        T key;
        std::size_t frequency;
        Node* left;
        Node* right;

        explicit Node(const T& k)
            : key(k), frequency(1), left(nullptr), right(nullptr) {}
    };

    Node* root_;

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    void add(Node*& node, const T& value) {
        if (!node) {
            node = new Node(value);
            return;
        }
        if (value == node->key) {
            ++node->frequency;
        } else if (value < node->key) {
            add(node->left, value);
        } else {
            add(node->right, value);
        }
    }

    int computeDepth(Node* node) const {
        if (!node) return 0;
        int leftDepth = computeDepth(node->left);
        int rightDepth = computeDepth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    template <typename F>
    void traverse(Node* node, F&& func) const {
        if (!node) return;
        traverse(node->left, func);
        func(node->key, node->frequency);
        traverse(node->right, func);
    }

 public:
    BST() : root_(nullptr) {}
    ~BST() { destroy(root_); }

    void insert(const T& value) {
        add(root_, value);
    }

    int search(const T& value) const {
        Node* current = root_;
        while (current) {
            if (value == current->key) return static_cast<int>(current->frequency);
            current = (value < current->key) ? current->left : current->right;
        }
        return 0;
    }

    int depth() const {
        return root_ ? computeDepth(root_) - 1 : 0;
    }

    template <typename F>
    void inorder(F&& func) const {
        traverse(root_, std::forward<F>(func));
    }
};

#endif  // INCLUDE_BST_H_
