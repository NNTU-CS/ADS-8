// bst.h
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

template<typename Key>
class WordTree {
 private:
    struct FreqNode {
        Key word;
        int freq;
        FreqNode* left;
        FreqNode* right;
        explicit FreqNode(const Key& w)
            : word(w), freq(1), left(nullptr), right(nullptr) {}
    };

    FreqNode* root = nullptr;

    void collect(FreqNode* node, std::vector<std::pair<Key,int>>& out) const {
        if (!node) return;
        collect(node->left, out);
        out.emplace_back(node->word, node->freq);
        collect(node->right, out);
    }

    void clearSubtree(FreqNode* node) {
        if (!node) return;
        clearSubtree(node->left);
        clearSubtree(node->right);
        delete node;
    }

    int height(FreqNode* node) const {
        if (!node) return -1;
        int hl = height(node->left);
        int hr = height(node->right);
        return 1 + (hl > hr ? hl : hr);
    }

    FreqNode* insertRec(FreqNode* node, const Key& w) {
        if (!node) {
            return new FreqNode(w);
        }
        if (w < node->word) {
            node->left = insertRec(node->left, w);
        } else if (node->word < w) {
            node->right = insertRec(node->right, w);
        } else {
            ++node->freq;
        }
        return node;
    }

    FreqNode* removeRec(FreqNode* node, const Key& w) {
        if (!node) return nullptr;
        if (w < node->word) {
            node->left = removeRec(node->left, w);
        } else if (node->word < w) {
            node->right = removeRec(node->right, w);
        } else {
            if (!node->left) {
                FreqNode* tmp = node->right;
                delete node;
                return tmp;
            }
            if (!node->right) {
                FreqNode* tmp = node->left;
                delete node;
                return tmp;
            }
            FreqNode* succ = node->right;
            while (succ->left) succ = succ->left;
            node->word = succ->word;
            node->freq = succ->freq;
            node->right = removeRec(node->right, succ->word);
        }
        return node;
    }

    int lookup(FreqNode* node, const Key& w) const {
        if (!node) return 0;
        if (w < node->word) return lookup(node->left, w);
        if (node->word < w) return lookup(node->right, w);
        return node->freq;
    }

 public:
    WordTree() = default;
    ~WordTree() { clear(); }

    void add(const Key& w) {
        root = insertRec(root, w);
    }

    void del(const Key& w) {
        root = removeRec(root, w);
    }

    void clear() {
        clearSubtree(root);
        root = nullptr;
    }

    int search(const Key& w) const {
        return lookup(root, w);
    }

    int depth() const {
        return height(root);
    }

    std::vector<std::pair<Key,int>> getFreqs() const {
        std::vector<std::pair<Key,int>> out;
        collect(root, out);
        return out;
    }
};

#endif  // INCLUDE_BST_H_