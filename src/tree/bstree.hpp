//
// Created by vtta 🍉 on 2020/1/20.
//

#ifndef DSA_BSTREE_HPP
#define DSA_BSTREE_HPP

#include <functional>
#include <utility>

#include "common.hpp"

namespace dsa {

template <typename K, typename Cmp = std::less<K>>
class bstree {
protected:
    struct node {
        node *left, *right, *parent;
        K key;
        node(K key = K(), node *left = nullptr, node *right = nullptr,
             node *parent = nullptr)
            : key(key), left(left), right(right), parent(parent) {}
    };
    node *root_{};
    Cmp cmp_{};
    u64 size_{};

public:
    bstree() = default;
    ~bstree() = default;

    auto root() const { return root_; }
    auto size() const { return size_; }
    auto empty() const { return root_ == nullptr; }

    node *find(K const &k);
    std::pair<node *, bool> insert(K const &k);

    template <typename Fn>
    void pre_order(node *x, Fn &f);
    template <typename Fn>
    void in_order(node *x, Fn &f);
    template <typename Fn>
    void post_order(node *x, Fn &f);

    void to_dot() const;
};

}  // namespace dsa

#endif  // DSA_BSTREE_HPP
