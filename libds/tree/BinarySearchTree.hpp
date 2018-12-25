//
//  BinarySearchTree.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef BinarySearchTree_hpp
#define BinarySearchTree_hpp

#include "./BinaryTree.hpp"

namespace libds {
// begining of namespace libds

template <typename T>
class BinarySearchTree : public BinaryTree<T> {
    using node           = BinaryNode<T>;
    using node_ptr       = node *;
    using node_const_ptr = const node_ptr;
    using reference      = BinarySearchTree<T> &;
    using const_ref      = BinarySearchTree<T> const &;
    using _base          = BinarySearchTree<T>;

private:
protected:
    node_ptr _hot;
    node_ptr hot() const { return _hot; }

    node_ptr connect34(node_ptr l, node_ptr m, node_ptr r, node_ptr t0,
                       node_ptr t1, node_ptr t2, node_ptr t3) {
        l->lChild = t0;
        if (t0) { t0->parent = l; }
        l->rChild = t1;
        if (t1) { t1->parent = l; }
        r->lChild = t2;
        if (t2) { t2->parent = r; }
        r->rChild = t3;
        if (t3) { t3->parent = r; }
        m->lChild = l;
        m->rChild = r;
        l->parent = m;
        r->parent = m;
        return m;
    }

    /// @brief x is a not null grandchild
    node_ptr rotateAt(node_ptr x) {
        if (!x || !x->parent || !x->parent->parent) {
            throw "pointer cannot be null";
        }
        node_ptr p = x->parent, g = p->parent;
        if (node::isLChild(p)) {
            if (node::isLChild(x)) {
                p->parent = g->parent;

                return connect34(x, p, g, x->lChild, x->rChild, p->rChild,
                                 g->rChild);
            } else {
                x->parent = g->parent;
                return connect34(p, x, g, p->lChild, x->lChild, x->rChild,
                                 g->rChild);
            }
        } else {
            if (node::isRChild(x)) {
                p->parent = g->parent;
                return connect34(g, p, x, g->lChild, p->lChild, x->lChild,
                                 x->rChild);
            } else {
                x->parent = g->parent;
                return connect34(g, x, p, g->lChild, x->lChild, x->rChild,
                                 p->rChild);
            }
        }
    }

    node_ptr rotateAndConnect(node_ptr x) {
        if (!x || !x->parent || !x->parent->parent) {
            // throw;
            return nullptr;
        }
        node_ptr g   = x->parent->parent;
        node_ptr res = nullptr;
        if (node::isRoot(g)) {
            res = _base::_root = _base::rotateAt(x);
        } else {
            if (node::isLChild(g)) {
                node_ptr &ptr2g = g->parent->lChild;
                res = ptr2g = _base::rotateAt(x);
            } else {
                node_ptr &ptr2g = g->parent->rChild;
                res = ptr2g = _base::rotateAt(x);
            }
        }
        return res;
    }

    // static node_ptr &searchIn(node_ptr &v, T const &e, node_ptr &hot) {
    //     if (!v || (e == v->data)) return v;
    //     return searchIn((e < v->data ? v->lChild : v->rChild), e, hot = v);
    // }

    static node_ptr &searchIn(node_ptr &v, T const &e, node_ptr &hot) {
        auto equals = [&](T const &e, node_ptr &v) {
            return !v || e == v->data;
        };
        if (equals(e, v)) { return v; }
        hot = v;
        do {
            node_ptr &c = (e < hot->data) ? hot->lChild : hot->rChild;
            if (equals(e, c)) { return c; }
            hot = c;
        } while (true);
    }

    static node_ptr removeAt(node_ptr &x, node_ptr &hot) {
        node_ptr w = x, succ = nullptr;
        if (!node::hasLChild(x))
            succ = x = x->rChild;
        else if (!node::hasRChild(x))
            succ = x = x->lChild;
        else {
            w = w->succ();
            std::swap(x->data, w->data);
            node_ptr u                       = w->parent;
            (u == x ? u->rChild : u->lChild) = succ = w->rChild;
        }
        hot = w->parent;
        if (succ) { succ->parent = hot; }
        // release(w);
        delete w;
        return succ;
    }

public:
    BinarySearchTree() {
        // _hot = _base::_root = new node;
    }
    virtual node_ptr &search(T const &e) {
        node_ptr &root = _base::_root;
        if (!root) {
            return root =
                       new node(e, nullptr, nullptr, nullptr, 0, 1, RB_BLACK);
        }
        return searchIn(root, e, _hot = nullptr);
    }
    virtual node_ptr insert(T const &e) {
        node_ptr &x = search(e);
        if (x) return x;
        x = new node(e, _hot);
        _base::updateHeightAbove(x);
        return x;
    }
    virtual bool remove(T const &e) {
        node_ptr &x = search(e);
        if (!x) return false;
        removeAt(x, _hot);
        --_base::_size;
        _base::updateHeightAbove(_hot);
        _base::ptrFromParentTo(x) = nullptr;
        delete x;
        return true;
    }
};

// end of namespace libds
}
#endif /* BinarySearchTree_hpp */
