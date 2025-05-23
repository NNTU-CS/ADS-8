// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

template<typename T>
class BST {
 private:
  struct WordNode {
    T word;
    int frequency;
    WordNode* left_branch;
    WordNode* right_branch;
    WordNode(T val)
        : word(val), frequency(1), left_branch(nullptr), right_branch(nullptr) {}
  };
  WordNode* tree_root;

  WordNode* insert_word(WordNode* node, T val) {
    if (!node) return new WordNode(val);
    if (val < node->word) {
      node->left_branch = insert_word(node->left_branch, val);
    } else if (val > node->word) {
      node->right_branch = insert_word(node->right_branch, val);
    } else {
      node->frequency++;
    }
    return node;
  }

  WordNode* delete_word(WordNode* node, T val) {
    if (!node) return nullptr;
    if (val < node->word) {
      node->left_branch = delete_word(node->left_branch, val);
    } else if (val > node->word) {
      node->right_branch = delete_word(node->right_branch, val);
    } else {
      WordNode* temp;
      if (!node->left_branch) {
        temp = node->right_branch;
        delete node;
        return temp;
      } else if (!node->right_branch) {
        temp = node->left_branch;
        delete node;
        return temp;
      }
      temp = node->right_branch;
      while (temp->left_branch) temp = temp->left_branch;
      node->word = temp->word;
      node->frequency = temp->frequency;
      node->right_branch = delete_word(node->right_branch, temp->word);
    }
    return node;
  }

  void clear_tree(WordNode* node) {
    if (!node) return;
    clear_tree(node->left_branch);
    clear_tree(node->right_branch);
    delete node;
  }

  int find_word(WordNode* node, T val) const {
    if (!node) return 0;
    if (val < node->word) return find_word(node->left_branch, val);
    if (val > node->word) return find_word(node->right_branch, val);
    return node->frequency;
  }

  int calc_depth(WordNode* node) const {
    if (!node) return -1;
    return 1 + std::max(calc_depth(node->left_branch),
                        calc_depth(node->right_branch));
  }

  void collect_stats(WordNode* node,
                     std::vector<std::pair<T, int>>& stats) const {
    if (!node) return;
    collect_stats(node->left_branch, stats);
    stats.emplace_back(node->word, node->frequency);
    collect_stats(node->right_branch, stats);
  }

 public:
  BST() : tree_root(nullptr) {}
  ~BST() { clear_tree(tree_root); }

  void add(T val) { tree_root = insert_word(tree_root, val); }

  void del(T val) { tree_root = delete_word(tree_root, val); }

  void clear() {
    clear_tree(tree_root);
    tree_root = nullptr;
  }

  int search(T val) const { return find_word(tree_root, val); }

  int depth() const { return calc_depth(tree_root); }

  std::vector<std::pair<T, int>> getFreqs() const {
    std::vector<std::pair<T, int>> stats;
    collect_stats(tree_root, stats);
    return stats;
  }
};

#endif  // INCLUDE_BST_H_
