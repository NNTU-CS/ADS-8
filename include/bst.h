// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <iostream>
#include <functional>

template<typename T>
class BST
{
private:
    struct Node
    {
        T        key;       // само слово
        int      freq;      // счётчик повторений
        Node*    left;
        Node*    right;

        explicit Node(const T& k)
            : key{k}, freq{1}, left{nullptr}, right{nullptr} {}
    };

    Node* root = nullptr;

/* ---------- служебные рекурсивные функции ---------- */
    void destroy(Node* p)
    {
        if (!p) return;
        destroy(p->left);
        destroy(p->right);
        delete p;
    }

    void insert(Node*& p, const T& key)
    {
        if (!p)
        {
            p = new Node(key);
            return;
        }
        if (key == p->key)
        {
            ++p->freq;
        }
        else if (key < p->key)
            insert(p->left, key);
        else
            insert(p->right, key);
    }

    Node* find(Node* p, const T& key) const
    {
        if (!p || key == p->key) return p;
        return key < p->key ? find(p->left, key) : find(p->right, key);
    }

    int height(Node* p) const
    {
        if (!p) return 0;
        int lh = height(p->left);
        int rh = height(p->right);
        return 1 + (lh > rh ? lh : rh);
    }

    template<typename F>
    void inOrder(Node* p, F&& fn) const
    {
        if (!p) return;
        inOrder(p->left, fn);
        fn(p);
        inOrder(p->right, fn);
    }

public:
/* ----------------- публичный интерфейс ----------------- */
    ~BST() { destroy(root); }

    void insert(const T& key) { insert(root, key); }
    int depth() const { return height(root); }
    bool search(const T& key) const { return find(root, key) != nullptr; }
    template<typename F>
    void forEachInOrder(F&& fn) const { inOrder(root, std::forward<F>(fn)); }
};

#endif  // INCLUDE_BST_H_
