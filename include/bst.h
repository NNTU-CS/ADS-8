// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <functional>
#include <utility>

template <typename T>
class BST
{
    struct Node {
        T           key;        // само слово
        std::size_t count;      // сколько раз встретилось
        Node*       left;
        Node*       right;

        explicit Node(const T& k)
            : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root = nullptr;

/* ------------ вспомогательные рекурсивные методы ------------- */
    static void clear(Node* n) {
        if (!n) return;
        clear(n->left);
        clear(n->right);
        delete n;
    }

    static void insert(Node*& n, const T& value) {
        if (!n) {                         // пустое место — ставим новый узел
            n = new Node(value);
            return;
        }
        if (value == n->key) {            // слово уже есть — увеличиваем счётчик
            ++n->count;
        } else if (value < n->key) {      // идём влево
            insert(n->left, value);
        } else {                          // идём вправо
            insert(n->right, value);
        }
    }

    static bool search(Node* n, const T& value) {
        while (n) {
            if (value == n->key)  return true;
            n = (value < n->key) ? n->left : n->right;
        }
        return false;
    }

    static std::size_t depth(Node* n) {
        if (!n) return 0;
        std::size_t l = depth(n->left);
        std::size_t r = depth(n->right);
        return 1 + (l > r ? l : r);
    }

    template <typename F>
    static void inorder(Node* n, F&& f) {
        if (!n) return;
        inorder(n->left,  f);
        f(n->key, n->count);
        inorder(n->right, f);
    }

/* ---------------------- публичный интерфейс ------------------- */
public:
    BST() = default;
    ~BST() { clear(root); }

    void insert(const T& value)              { insert(root, value); }
    bool search(const T& value) const        { return search(root, value); }
    std::size_t depth()      const           { return depth(root); }

    /** Обход in-order.  Функция-коллбэк получает (key, count). */
    template <typename F>
    void inorder(F&& f) const { inorder(root, std::forward<F>(f)); }
};

#endif  // INCLUDE_BST_H_
