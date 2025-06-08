// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <string>
#include <utility>

template <typename T>
class BST {
 private:
    struct Node {
        T info;  // key → info
        int kol;  // count → kol
        Node* left;
        Node* right;
        explicit Node(const T& k) : info(k), kol(1), left(nullptr), right(nullptr) {}
    };
    Node* root;
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }
    void insert(Node*& node, const T& info) {  // key → info
        if (!node) {
            node = new Node(info);
        } else if (info == node->info) {
            node->kol++;
        } else {
            info < node->info ? insert(node->left, info) : insert(node->right, info);
        }
    }
    int Search(Node* node, const T& info) const {  // key → info
        return !node ? 0 :
               info == node->info ? node->kol :
               Search(info < node->info ? node->left : node->right, info);
    }
    int Depth(Node* node) const {
        return !node ? -1 :
               1 + std::max(Depth(node->left), Depth(node->right));
    }
    void inorder(Node* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        inorder(node->left, vec);
        vec.push_back({node->info, node->kol});
        inorder(node->right, vec);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }
    void insert(const T& info) { insert(root, info); }  // key → info
    int search(const T& info) const { return Search(root, info); }  // key → info
    int depth() const { return Depth(root); }
    std::vector<std::pair<T, int>> getAll() const {
        std::vector<std::pair<T, int>> vec;
        inorder(root, vec);
        return vec;
    }
};

#endif  // INCLUDE_BST_H_
