//
// Created by vtta 🍉 on 2020/1/20.
//

#include "bstree.hpp"

#include <array>
#include <iostream>
#include <sstream>
#include <stack>
#include <unordered_map>
#include <vector>

namespace dsa {

template <typename K, typename Cmp>
typename bstree<K, Cmp>::node *bstree<K, Cmp>::find(const K &k) {
    auto x = root_;
    auto p = x;
    while (x != nullptr) {
        p = x;
        if (cmp_(k, x->key)) {
            x = x->left;
        } else if (cm(x->key, k)) {
            x = x->right;
        } else {
            return x;
        }
    }
    return nullptr;
}
template <typename K, typename Cmp>
std::pair<typename bstree<K, Cmp>::node *, bool> bstree<K, Cmp>::insert(
    const K &k) {
    auto x = root_;
    auto p = x;
    while (x != nullptr) {
        p = x;
        if (cmp_(k, x->key)) {
            x = x->left;
        } else if (cmp_(x->key, k)) {
            x = x->right;
        } else {
            return {x, false};
        }
    }
    x = new node(k, nullptr, nullptr, p);
    if (p == nullptr) {
        root_ = x;
    } else {
        if (cmp_(k, p->key)) {
            p->left = x;
        } else {
            p->right = x;
        }
    }
    ++size_;
    return {x, true};
}
template <typename K, typename Cmp>
template <typename Fn>
void bstree<K, Cmp>::pre_order(bstree::node *x, Fn &f) {
    std::stack<node *> s;
    auto vst_along_left = [&](node *x) {
        while (x != nullptr) {
            f(x->key);
            s.push(x->right);
            x = x->left;
        }
    };
    while (true) {
        vst_along_left(x);
        if (s.empty()) {
            break;
        }
        x = s.top();
        s.pop();
    }
}
template <typename K, typename Cmp>
template <typename Fn>
void bstree<K, Cmp>::in_order(bstree::node *x, Fn &f) {
    std::stack<node *> s;
    auto go_along_left = [&](node *x) {
        while (x != nullptr) {
            s.push(x);
            x = x->left;
        }
    };
    while (true) {
        go_along_left(x);
        if (s.empty()) {
            break;
        }
        x = s.top();
        f(x->key);
        s.pop();
        x = x->right;
    }
}
template <typename K, typename Cmp>
template <typename Fn>
void bstree<K, Cmp>::post_order(bstree::node *x, Fn &f) {
    if (x == nullptr) {
        return;
    }
    // all pointers in the stack are not nullptr
    std::stack<node *> s;
    do {
        while (x) {
            if (x->right) {
                s.push(x->right);
            }
            s.push(x);
            x = x->left;
        }
        x = s.top();
        s.pop();
        // need to traverse right sub-tree
        if (x->right && !s.empty() && s.top() == x->right) {
            s.pop();
            s.push(x);
            x = x->right;
        } else {
            // both left and right sub-trees are traversed
            f(x->key);
            // root of the sub-tree is traversed
            // need to pop a new node from stack
            x = nullptr;
        }
    } while (!s.empty());
}
template <typename K, typename Cmp>
void bstree<K, Cmp>::to_dot() const {
    std::unordered_map<node *, u64> node2id{};
    std::vector<node *> nodes{};
    // traversal
    {
        u64 id = 0;
        node *x = root();
        std::stack<node *> s;
        while (true) {
            while (x != nullptr) {
                s.push(x);
                x = x->left;
            }
            if (s.empty()) {
                break;
            }
            x = s.top();
            s.pop();
            {
                nodes.push_back(x);
                node2id[x] = id;
                id += 1;
            }
            x = x->right;
        }
    }
    // generate graph file
    {
        std::ostringstream g;
        g << "digraph G {" << std::endl;
        g << "    node [shape=record, height=.1];" << std::endl;
        g << "    // all the nodes" << std::endl;
        for (auto i = 0UL; i < nodes.size(); ++i) {
            g << "    node" << i << " [label=\"<f0>|<f1>" << nodes[i]->key
              << "|<f2>\"];" << std::endl;
        }
        g << "    // all the edges" << std::endl;
        for (auto i = 0UL; i < nodes.size(); ++i) {
            if (nodes[i]->left) {
                g << "    \"node" << i << "\":f0->\"node"
                  << node2id[nodes[i]->left] << "\":f1;" << std::endl;
            }
            if (nodes[i]->right) {
                g << "    \"node" << i << "\":f2->\"node"
                  << node2id[nodes[i]->right] << "\":f1;" << std::endl;
            }
        }
        g << "}" << std::endl;
        std::cout << g.str();
    }
}

}  // namespace dsa

#ifdef ENABLE_DOCTEST_IN_LIBRARY
#include "doctest.h"
TEST_CASE("binary search tree sanity test") {
    struct accu {
        std::stringstream buf;
        void operator()(int x) { buf << x << " "; }
    };
    dsa::bstree<int> tree;
    std::array arr{7, 5, 3, 1, 2, 4, 8, 9, 6};
    //            7
    //          /  \
    //        5     8
    //      /  \     \
    //     3    6     9
    //   /  \
    //  1    4
    //   \
    //    2
    for (auto const &i : arr) {
        CHECK(tree.insert(i).second);
    }
    CHECK_EQ(arr.size(), tree.size());
    for (auto const &i : arr) {
        CHECK(!tree.insert(i).second);
    }
    CHECK_EQ(arr.size(), tree.size());
    {
        accu f;
        tree.pre_order(tree.root(), f);
        CHECK_EQ(f.buf.str(), "7 5 3 1 2 4 6 8 9 ");
    }
    {
        accu f;
        tree.in_order(tree.root(), f);
        CHECK_EQ(f.buf.str(), "1 2 3 4 5 6 7 8 9 ");
    }
    {
        accu f;
        tree.post_order(tree.root(), f);
        CHECK_EQ(f.buf.str(), "2 1 4 3 6 5 9 8 7 ");
    }
    // tree.to_dot();
}
#endif  // ENABLE_DOCTEST_IN_LIBRARY
