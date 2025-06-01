// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <string>
#include <utility>
template <typename T>
class BST {
 private:
  struct Knot {
    T key;
    int count;
    std::unique_ptr<Knot> left;
    std::unique_ptr<Knot> right;
    explicit Knot(const T& k)
        : key(k), count(1), left(nullptr), right(nullptr) {}
  };

 public:
  BST() = default;
  ~BST() = default;
  void addEl(const T& key) {
    addEl(root, key);
  }
  int search(const T& key) const {
    return findEl(root.get(), key);
  }
  int depth() const {
    return calcHeight(root.get());
  }
  std::vector<std::pair<T, int>> getAllEl() const {
    std::vector<std::pair<T, int>> elements;
    inorder(root.get(), elements);
    return elements;
  }

  BST(const BST&) = delete;
  BST& operator=(const BST&) = delete;
  BST(BST&&) = default;
  BST& operator=(BST&&) = default;
};
#endif  // INCLUDE_BST_H_
