// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include <utility>
template <typename T>
class BST {
private:
    struct Knot {
        T key;
        int count;
        std::unique_ptr<Knot> left;
        std::unique_ptr<Knot> right;
        explicit Knot(const T& k)
            : key(k), count(1), left(nullptr), right(nullptr) {}
    };
    std::unique_ptr<Knot> root;
    void addEl(std::make_unique<Knot>& node, const T& key) {
        if (!node) {
            node = std::make_unique<Knot>(key);
        } else if (key == node->key) {
            node->count++;
        } else {
            key < node->key ? addEl(node->left, key)
                          : addEl(node->right, key);
        }
    }
    int findEl(const Knot* node, const T& key) const {
        if (!node) return 0;
        if (key == node->key) return node->count;
        return findEl(key < node->key ? node->left.get()
                                    : node->right.get(), key);
    }
    int calcHeight(const Knot* node) const {
        if (!node) return -1;
        return 1 + std::max(calcHeight(node->left.get()),
                          calcHeight(node->right.get()));
    }
    void inorder(const Knot* node, std::vector<std::pair<T, int>>& vec) const {
        if (!node) return;
        inorder(node->left.get(), vec);
        vec.emplace_back(node->key, node->count);
        inorder(node->right.get(), vec);
    }

public:
    BST() = default;
    ~BST() = default;
    void addEl(const T& key) { addEl(root, key); }
    
    int search(const T& key) const {
        return findEl(root.get(), key);
    }
    
    int depth() const {
        return calcHeight(root.get());
    }
    
    std::vector<std::pair<T, int>> getAllEl() const {
        std::vector<std::pair<T, int>> elements;
        inorder(root.get(), elements);
        return elements;
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
    
    BST(BST&&) = default;
    BST& operator=(BST&&) = default;
};
#endif  // INCLUDE_BST_H_
