// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <memory>
#include <utility>
#include <algorithm>

template <typename T>
class BST {
    struct TreeNode {
        T value;
        int occurrences;
        std::unique_ptr<TreeNode> left;
        std::unique_ptr<TreeNode> right;

        explicit TreeNode(const T& val)
            : value(val), occurrences(1), left(nullptr), right(nullptr) {}
    };

    std::unique_ptr<TreeNode> root;

    // Внутренние вспомогательные методы
    void insert_helper(std::unique_ptr<TreeNode>& node, const T& val) {
        if (!node) {
            node = std::make_unique<TreeNode>(val);
            return;
        }

        if (val < node->value) {
            insert_helper(node->left, val);
        } else if (val > node->value) {
            insert_helper(node->right, val);
        } else {
            node->occurrences++;
        }
    }

    const TreeNode* find_helper(const TreeNode* node, const T& val) const {
        if (!node) return nullptr;
        
        if (val < node->value) {
            return find_helper(node->left.get(), val);
        } else if (val > node->value) {
            return find_helper(node->right.get(), val);
        }
        return node;
    }

    int calculate_depth(const TreeNode* node) const {
        if (!node) return 0;
        return 1 + std::max(calculate_depth(node->left.get()),
                           calculate_depth(node->right.get()));
    }

    template <typename Visitor>
    void traverse_helper(const TreeNode* node, Visitor visit) const {
        if (!node) return;
        traverse_helper(node->left.get(), visit);
        visit(node->value, node->occurrences);
        traverse_helper(node->right.get(), visit);
    }

public:
    BST() = default;
    ~BST() = default;

    // Запрещаем копирование
    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;

    // Разрешаем перемещение
    BST(BST&&) noexcept = default;
    BST& operator=(BST&&) noexcept = default;

    // Публичный интерфейс с сохранением оригинальных имен
    void insert(const T& value) {
        insert_helper(root, value);
    }

    int search(const T& value) const {
        const TreeNode* found = find_helper(root.get(), value);
        return found ? found->occurrences : 0;
    }

    int depth() const {
        return root ? calculate_depth(root.get()) - 1 : 0;
    }

    template <typename Action>
    void in_order(Action action) const {
        traverse_helper(root.get(), action);
    }
};
#endif  // INCLUDE_BST_H_
