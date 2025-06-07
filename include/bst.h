// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <functional>
#include <utility>

template <typename T>
class BST {
    struct Node {
        T           key;
        std::size_t count;
        Node*       left;
        Node*       right;
        explicit Node(const T& k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

    static void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    static void insert(Node*& n, const T& value) {
        if (!n) {
            n = new Node(value);
            return;
        }
        if (value == n->key) ++n->count;
        else if (value < n->key) insert(n->left, value);
        else                     insert(n->right, value);
    }

    static int depth_nodes(Node* n) {
        if (!n) return 0;
        int l = depth_nodes(n->left);
        int r = depth_nodes(n->right);
        return 1 + (l > r ? l : r);
    }

 public:
    BST() = default;
    ~BST() { clear(root); }

    void insert(const T& value)              { insert(root, value); }


    int search(const T& value) const {
        Node* n = root;
        while (n) {
            if (value == n->key)  return static_cast<int>(n->count);
            n = (value < n->key) ? n->left : n->right;
        }
        return 0;
    }


    int depth() const {
        if (!root) return 0;
        return depth_nodes(root) - 1;   
    }

    template <typename F>
    void inorder(F&& f) const {
        std::function<void(Node*)> walk = [&](Node* n){
            if (!n) return;
            walk(n->left);
            f(n->key, n->count);
            walk(n->right);
        };
        walk(root);
    }
};

#endif  // INCLUDE_BST_H_
