// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <string>
#include <vector>
#include <utility>
#include <algorithm>

template <typename T>
struct TreeNode {
  T key;
  int occurrences;
  TreeNode* left;
  TreeNode* right;

  explicit TreeNode(const T& value)
      : key(value), occurrences(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class BST {
 public:
  BST();
  ~BST();

  // Вставка слова (при существовании ++occurrences)
  void insert(const T& value);

  // Возвращает число вхождений слова (0, если нет)
  int search(const T& value) const;

  // Возвращает глубину (высоту) дерева:
  // 0, если пустое; иначе — максимальное число узлов от корня до листа включительно.
  int depth() const;

  // Возвращает общее число узлов (уникальных ключей)
  int count() const;

  // Обходит дерево «in-order» и заполняет вектор парами {ключ, occurrences}
  void collect(std::vector<std::pair<T, int>>* output) const;

 private:
  TreeNode<T>* rootPtr;

  TreeNode<T>* addNode(TreeNode<T>* node, const T& value);
  TreeNode<T>* findNode(TreeNode<T>* node, const T& value) const;
  int computeDepth(TreeNode<T>* node) const;
  int computeCount(TreeNode<T>* node) const;
  void destroy(TreeNode<T>* node);
  void collectInOrder(TreeNode<T>* node,
                      std::vector<std::pair<T, int>>* output) const;
};

template <typename T>
BST<T>::BST() : rootPtr(nullptr) {}

template <typename T>
BST<T>::~BST() {
  destroy(rootPtr);
}

template <typename T>
void BST<T>::insert(const T& value) {
  rootPtr = addNode(rootPtr, value);
}

template <typename T>
TreeNode<T>* BST<T>::addNode(TreeNode<T>* node, const T& value) {
  if (node == nullptr) {
    return new TreeNode<T>(value);
  }
  if (value < node->key) {
    node->left = addNode(node->left, value);
  } else if (value > node->key) {
    node->right = addNode(node->right, value);
  } else {
    node->occurrences++;
  }
  return node;
}

template <typename T>
int BST<T>::search(const T& value) const {
  TreeNode<T>* found = findNode(rootPtr, value);
  return (found ? found->occurrences : 0);
}

template <typename T>
TreeNode<T>* BST<T>::findNode(TreeNode<T>* node, const T& value) const {
  if (node == nullptr) {
    return nullptr;
  }
  if (value < node->key) {
    return findNode(node->left, value);
  } else if (value > node->key) {
    return findNode(node->right, value);
  } else {
    return node;
  }
}

template <typename T>
int BST<T>::depth() const {
  return computeDepth(rootPtr);
}

template <typename T>
int BST<T>::computeDepth(TreeNode<T>* node) const {
  if (node == nullptr) {
    return 0;
  }
  int leftDepth = computeDepth(node->left);
  int rightDepth = computeDepth(node->right);
  return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
}

template <typename T>
int BST<T>::count() const {
  return computeCount(rootPtr);
}

template <typename T>
int BST<T>::computeCount(TreeNode<T>* node) const {
  if (node == nullptr) {
    return 0;
  }
  return 1 + computeCount(node->left) + computeCount(node->right);
}

template <typename T>
void BST<T>::collect(std::vector<std::pair<T, int>>* output) const {
  collectInOrder(rootPtr, output);
}

template <typename T>
void BST<T>::collectInOrder(
    TreeNode<T>* node,
    std::vector<std::pair<T, int>>* output) const {
  if (node == nullptr) {
    return;
  }
  collectInOrder(node->left, output);
  output->emplace_back(node->key, node->occurrences);
  collectInOrder(node->right, output);
}

template <typename T>
void BST<T>::destroy(TreeNode<T>* node) {
  if (node == nullptr) {
    return;
  }
  destroy(node->left);
  destroy(node->right);
  delete node;
}

#endif  // INCLUDE_BST_H_
