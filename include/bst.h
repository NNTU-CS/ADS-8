// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

template<typename T>
class BST {
 private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;

        explicit Node(const T& val)
            : key(val), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

    int calcDepth(Node* node) const {
        if (!node) return 0;
        int l = calcDepth(node->left);
        int r = calcDepth(node->right);
        return 1 + (l > r ? l : r);
    }

    void collect(Node* node, std::vector<std::pair<T, int>>& list) const {
        if (!node) return;
        collect(node->left, list);
        list.emplace_back(node->key, node->count);
        collect(node->right, list);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }

    void insert(const T& val) {
        if (!root) {
            root = new Node(val);
            return;
        }
        Node* cur = root;
        while (true) {
            if (val == cur->key) {
                ++cur->count;
                return;
            } else if (val < cur->key) {
                if (!cur->left) {
                    cur->left = new Node(val);
                    return;
                }
                cur = cur->left;
            } else {
                if (!cur->right) {
                    cur->right = new Node(val);
                    return;
                }
                cur = cur->right;
            }
        }
    }

    int search(const T& val) const {
        Node* cur = root;
        while (cur) {
            if (val == cur->key) return cur->count;
            cur = (val < cur->key) ? cur->left : cur->right;
        }
        return 0;
    }

    int depth() const {
        return calcDepth(root) - 1;
    }

    std::vector<std::pair<T, int>> getSortedByFrequency() const {
        std::vector<std::pair<T, int>> result;
        collect(root, result);
        std::sort(result.begin(), result.end(),
                  [](const auto& a, const auto& b) {
                      return a.second > b.second;
                  });
        return result;
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
};


#endif  // INCLUDE_BST_H_
