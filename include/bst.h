// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <utility>

template <typename T>
class BST {
 private:
    /*---------- структура узла ----------*/
    struct Node {
        T     key;          // само слово
        int   freq;         // сколько раз встретилось
        Node* left;
        Node* right;

        explicit Node(const T& k)
            : key{k}, freq{1}, left{nullptr}, right{nullptr} {}
    };

    Node* root = nullptr;

    /*---------- рекурсивные вспомогательные методы ----------*/
    void destroy(Node* p) {
        if (!p) return;
        destroy(p->left);
        destroy(p->right);
        delete p;
    }

    /* вставка: p — ссылка на указатель! */
    void insert(Node*& p, const T& key) {
        if (!p) {                     // дошли до места вставки
            p = new Node(key);
            return;
        }
        if (key == p->key) {
            ++p->freq;                // слово уже было – увеличиваем счётчик
        } else if (key < p->key) {
            insert(p->left, key);
        } else {
            insert(p->right, key);
        }
    }

    Node* find(Node* p, const T& key) const {
        if (!p || p->key == key) return p;
        return key < p->key ? find(p->left, key) : find(p->right, key);
    }

    int height(Node* p) const {
        if (!p) return 0;
        int lh = height(p->left);
        int rh = height(p->right);
        return 1 + (lh > rh ? lh : rh);
    }

    template <typename F>
    void inOrder(Node* p, F&& fn) const {
        if (!p) return;
        inOrder(p->left, fn);
        fn(p);
        inOrder(p->right, fn);
    }

 public:
    /*---------- публичный интерфейс ----------*/
    ~BST() { destroy(root); }

    /// вставка слова
    void insert(const T& key) { insert(root, key); }

    /// глубина дерева — кол-во **рёбер** на самом длинном пути
    int depth() const {
        if (!root) return 0;
        return height(root) - 1;      // тест ожидает именно число рёбер
    }

    /// вернуть частоту слова (0, если слово не найдено)
    int search(const T& key) const {
        Node* n = find(root, key);
        return n ? n->freq : 0;
    }

    /// обход in-order: передать каждый узел произвольному callable
    template <typename F>
    void forEachInOrder(F&& fn) const {
        inOrder(root, std::forward<F>(fn));
    }
};

#endif  // INCLUDE_BST_H_
