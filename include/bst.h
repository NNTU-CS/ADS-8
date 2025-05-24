// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>

template<typename T>
struct Node {
    T key;
    int freq;
    Node<T>* left;
    Node<T>* right;

    explicit Node(const T& k) : key(k), freq(1), left(nullptr), right(nullptr) {}
};

template<typename T>
class BST {
 private:
    Node<T>* root;

    class Helper {
     public:
        static void traverse(Node<T>* node, std::vector<WordFrequencyPair>& list) {
            if (node == nullptr) return;
            traverse(node->left, list);
            list.emplace_back(node->key, node->freq);
            traverse(node->right, list);
        }
    };

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    bool search(const T&);
    void insert(const T&);
    int depth(Node<T>* node);
    void inorderTraversal(Node<T>* node);

 private:
    void clear(Node<T>* node) {
        if (node != nullptr) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};

#endif  // INCLUDE_BST_H_
