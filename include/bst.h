// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

template <typename KeyType>
class BST {
 private:
    struct TreeNode {
        KeyType data;
        int frequency;
        TreeNode* leftChild;
        TreeNode* rightChild;

        explicit TreeNode(const KeyType& key)
            : data(key), frequency(1), leftChild(nullptr), rightChild(nullptr) {}
    };

    TreeNode* root_;

    TreeNode* addNode(TreeNode* node, const KeyType& key) {
        if (node == nullptr) {
            return new TreeNode(key);
        }
        if (key == node->data) {
            ++node->frequency;
        } else if (key < node->data) {
            node->leftChild = addNode(node->leftChild, key);
        } else {
            node->rightChild = addNode(node->rightChild, key);
        }
        return node;
    }

    int calculateHeight(TreeNode* node) const {
        if (node == nullptr) {
            return -1;
        }
        int leftHeight = calculateHeight(node->leftChild);
        int rightHeight = calculateHeight(node->rightChild);
        return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
    }

    void inorderTraversal(TreeNode* node, std::vector<std::pair<KeyType, int>>& container) const {
        if (node == nullptr) return;
        inorderTraversal(node->leftChild, container);
        container.emplace_back(node->data, node->frequency);
        inorderTraversal(node->rightChild, container);
    }

    void destroyTree(TreeNode* node) {
        if (node == nullptr) return;
        destroyTree(node->leftChild);
        destroyTree(node->rightChild);
        delete node;
    }

 public:
    BST() : root_(nullptr) {}
    ~BST() { destroyTree(root_); }

    void insert(const KeyType& key) {
        root_ = addNode(root_, key);
    }

    int findFrequency(const KeyType& key) const {
        TreeNode* current = root_;
        while (current != nullptr) {
            if (key == current->data) {
                return current->frequency;
            }
            current = (key < current->data) ? current->leftChild : current->rightChild;
        }
        return 0;
    }

    int height() const {
        return calculateHeight(root_);
    }

    int depth() const {
        return height();
    }

    int search(const KeyType& key) const {
        return findFrequency(key);
    }

    void displayFrequency(std::ostream& os) const {
        std::vector<std::pair<KeyType, int>> freqList;
        inorderTraversal(root_, freqList);

        std::sort(freqList.begin(), freqList.end(),
                  [](const auto& lhs, const auto& rhs) {
                      if (lhs.second != rhs.second)
                          return lhs.second > rhs.second;
                      return lhs.first < rhs.first;
                  });

        for (const auto& entry : freqList) {
            os << entry.first << " " << entry.second << "\n";
        }
    }

    bool empty() const {
        return root_ == nullptr;
    }
};

#endif  // INCLUDE_BST_H_
