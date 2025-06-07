// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <string>
#include <algorithm>
#include <vector>
#include <stack>

template <typename T>
class BST {
 private:
    struct Node {
        T value;
        int freq;
        Node* left;
        Node* right;
        explicit Node(const T& v) : value(v), freq(1), left(nullptr), right(nullptr) {}
    };
    Node* root;

    // Функция для вычисления глубины дерева
    int getDepth(Node* node) {
        if (!node) return 0;
        int left = getDepth(node->left);
        int right = getDepth(node->right);
        return 1 + (left > right ? left : right);
    }

 public:
    BST() : root(nullptr) {}
    ~BST() {
        std::stack<Node*> stack;
        if (root) stack.push(root);
        while (!stack.empty()) {
            Node* current = stack.top();
            stack.pop();
            if (current->left) stack.push(current->left);
            if (current->right) stack.push(current->right);
            delete current;
        }
    }

    // Вставка элемента в дерево
    void insert(const T& value) {
        if (!root) {
            root = new Node(value);
            return;
        }
        Node* current = root;
        while (true) {
            if (value == current->value) {
                current->freq++;
                return;
            } else if (value < current->value) {
                if (!current->left) {
                    current->left = new Node(value);
                    return;
                }
                current = current->left;
            } else {
                if (!current->right) {
                    current->right = new Node(value);
                    return;
                }
                current = current->right;
            }
        }
    }

    // Поиск частоты слова в дереве
    int search(const T& value) {
        Node* current = root;
        while (current) {
            if (value == current->value) return current->freq;
            current = (value < current->value) ? current->left : current->right;
        }
        return 0;
    }

    // Получение глубины дерева
    int depth() {
        if (!root) return 0;
        return getDepth(root) - 1;
    }

    // Получение всех слов по частоте
    std::vector<std::pair<T, int>> getWordsByFrequency() {
        std::vector<std::pair<T, int>> result;
        std::stack<Node*> stack;
        Node* current = root;
        while (current || !stack.empty()) {
            while (current) {
                stack.push(current);
                current = current->left;
            }
            current = stack.top();
            stack.pop();
            result.push_back({current->value, current->freq});
            current = current->right;
        }
        std::sort(result.begin(), result.end(),
                  [](const auto& a, const auto& b) { return a.second > b.second; });
        return result;
    }

    BST(const BST&) = delete;
    BST& operator=(const BST&) = delete;
};
#endif  // INCLUDE_BST_H_
