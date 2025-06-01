// Copyright 2021 NNTU-CS
#ifndef INCLUDE_UNIQUE bstH 
#define INCLUDE_UNIQUE bstH 
#include <memory>
#include <utility>
#include <vector>
#include <cstdlib>

template <class TT>
class BSTree {
private:
    class Node {
    public:
        TT data;
        int cnt;
        std::unique_ptr<Node> lptr;
        std::unique_ptr<Node> rptr;

        explicit Node(const TT& val) : data(val), cnt{1}, lptr{nullptr}, rptr{nullptr} {}

        bool cmpLess(const TT& v) const { return data < v; }
        bool isEqual(const TT& v) const { return data == v; }
    };

    std::unique_ptr<Node> root;
    
public:
    BSTree() { }

    void insert(const TT& value) {
        if (!root) {
            root = std::make_unique<Node>(value);
            return;
        }
        Node* current = root.get();
        while (true) {
            if (current->isEqual(value)) {
                current->cnt++;
                return;
            }
            if (current->cmpLess(value)) {
                if (current->rptr) { current = current->rptr.get(); }
                else { current->rptr = std::make_unique<Node>(value); return; }
            } else {
                if (current->lptr) { current = current->lptr.get(); }
                else { current->lptr = std::make_unique<Node>(value); return; }
            }
        }
    }

    int lookup(const TT& value) const {
        const Node *curr = root.get();
        while (curr) {
            if (curr->isEqual(value)) return curr->cnt;
            curr = (curr->data < value) ? curr->rptr.get() : curr->lptr.get();
        }
        return 0;
    }

    int calcDepth() const {
        int max_depth = 0;
        std::vector<std::pair<const Node*, int>> stack;
        if (root) stack.push_back({root.get(), 1});
        while (!stack.empty()) {
            const auto& pair = stack.back();
            const Node* node = pair.first;
            int current_depth = pair.second;
            stack.pop_back();
            if (current_depth > max_depth) max_depth = current_depth;
            if (node->lptr) stack.push_back({node->lptr.get(), current_depth + 1});
            if (node->rptr) stack.push_back({node->rptr.get(), current_depth + 1});
        }
        return max_depth - 1;
    }

    std::vector<std::pair<TT, int>> elements() const {
        std::vector<std::pair<TT, int>> result;
        if (!root) return result;

        std::vector<std::pair<const Node*, bool>> stack;
        stack.push_back({root.get(), false});
        while (!stack.empty()) {
            const auto& elem = stack.back();
            const Node* node = elem.first;
            bool visited = elem.second;
            stack.pop_back();
            if (visited) {
                result.push_back({node->data, node->cnt});
                continue;
            }
            if (node->rptr) stack.push_back({node->rptr.get(), false});
            stack.push_back({node, true});
            if (node->lptr) stack.push_back({node->lptr.get(), false});
        }
        return result;
    }
};

#endif  // INCLUDE_UNIQUE bstH
