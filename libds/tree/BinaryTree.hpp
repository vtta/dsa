//
//  BinaryTree.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef BinaryTree_hpp
#define BinaryTree_hpp

#include "./BinaryNode.hpp"
namespace libds {
// begining of namespace libds

template <typename T>
class BinaryTree {
    using pointer   = BinaryTree<T> *;
    using const_ref = BinaryTree<T> const &;
    using node      = BinaryNode<T>;
    using node_ptr  = node *;

private:
protected:
    int      _size;
    node_ptr _root;

    virtual int updateHeight(node_ptr x) {
        return x->height = 1 + std::max(node::stature(x->lChild),
                                        node::stature(x->rChild));
    }
    void updateHeightAbove(node_ptr x) {
        while (x) {
            updateHeight(x);
            x = x->parent;
        }
    }
    node_ptr &ptrFromParentTo(node_ptr x) {
        return node::isRoot(x) ? _root
                               : (node::isLChild(x) ? x->parent->lChild
                                                    : x->parent->rChild);
    }
    static void release(node_ptr x) { return x->release(x); }

public:
    BinaryTree() : _size(0), _root(nullptr) {}
    ~BinaryTree() {
        if (0 < size()) { remove(root()); }
    }
    int      size() const { return _size; }
    bool     empty() const { return !root(); }
    node_ptr root() const { return _root; }
    node_ptr insertAsRoot(T const &e) {
        _size         = 1;
        return root() = new BinaryNode<T>(e);
    }
    node_ptr insertAsLChildOf(node_ptr x, T const &e) {
        ++_size;
        x->insertAsLChild(e);
        updateHeightAbove(x);
        return x->lChild;
    }
    node_ptr insertAsRChildOf(node_ptr x, T const &e) {
        ++_size;
        x->insertAsRChild(e);
        updateHeightAbove(x);
        return x->rChild;
    }
    node_ptr attachAsLChildOf(node_ptr x, pointer &t) {
        x->lChild                        = t->root();
        if (x->lChild) x->lChild->parent = x;
        _size += t->_size;
        updateHeightAbove(x);
        t->_root = nullptr;
        t->_size = 0;
        // delete t;
        t = nullptr;
        return x;
    }
    node_ptr attachAsRChildOf(node_ptr x, pointer &t) {
        x->rChild                        = t->root();
        if (x->rChild) x->rChild->parent = x;
        _size += t->_size;
        updateHeightAbove(x);
        t->_root = nullptr;
        t->_size = 0;
        // release(t);
        // delete t;
        t = nullptr;
        return x;
    }
    int remove(node_ptr x) {
        ptrFromParentTo(x) = nullptr;
        updateHeightAbove(x->parent);
        int n = removeRecursivelyAt(x);
        _size -= n;
        return n;
    }
    static int removeRecursivelyAt(node_ptr x) {
        if (!x) return 0;
        int n =
            1 + removeRecursivelyAt(x->lChild) + removeRecursivelyAt(x->rChild);
        delete x;
        // release(x);
        return n;
    }
    pointer secede(node_ptr x) {
        ptrFromParentTo(x) = nullptr;
        updateHeightAbove(x->parent);
        pointer t = new BinaryTree<T>;
        t->_root  = x;
        x->parent = nullptr;
        t->_size  = x->size();
        _size -= t->_size;
        return t;
    }
    template <typename VST>
    void travLevel(VST &visit) {
        if (empty()) return;
        root()->travLevel(visit);
    }
    template <typename VST>
    void travPre(VST &visit) {
        if (empty()) return;
        root()->travPre(visit);
    }
    template <typename VST>
    void travIn(VST &visit) {
        if (empty()) return;
        root()->travIn(visit);
    }
    template <typename VST>
    void travPost(VST &visit) {
        if (empty()) return;
        root()->travPost(visit);
    }
    bool operator<(const_ref t) { return root() && root() < t.root(); }
    bool operator==(const_ref t) { return root() && (root() == t.root()); }
    bool operator<=(const_ref t) { return ((*this) < t) || ((*this) == t); }
    bool operator>(const_ref t) { return !((*this) <= t); }
    bool operator>=(const_ref t) { return !((*this) < t); }
    bool operator!=(const_ref t) { return !((*this) == t); }
    friend std::ostream &operator<<(std::ostream &out, const_ref tree) {
        out << tree.root()->toString("", "");
        return out;
    }
};
// end of namespace libds
}
#endif /* BinaryTree_hpp */
