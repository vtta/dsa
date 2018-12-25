//
//  RedBlackTree.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef RedBlackTree_hpp
#define RedBlackTree_hpp

#include "../tree/BinarySearchTree.hpp"

namespace libds {

template <typename T>
class RedBlackTree : public BinarySearchTree<T> {
    using node           = BinaryNode<T>;
    using node_ptr       = node*;
    using node_const_ptr = const node_ptr;
    using _base          = BinarySearchTree<T>;
    using self_type      = RedBlackTree<T>;
    using reference      = self_type&;
    using const_ref      = self_type const&;

private:
    bool isBlack(node_ptr p) const { return (!p || (RB_BLACK == p->color)); }
    bool isRed(node_ptr p) const { return !isBlack(p); }
    bool isBlackHeightUpdated(node_ptr p) const {
        return node::stature(p->lChild) == node::stature(p->rChild) &&
               p->height == (isRed(p) ? node::stature(p->lChild)
                                      : node::stature(p->lChild) + 1);
    }

protected:
    void solveDoubleRed(node_ptr x) {
        if (node::isRoot(x)) {
            _base::_root->color = RB_BLACK;
            ++_base::_root->height;
            return;
        }
        node_ptr p = x->parent;
        if (isBlack(p)) { return; }
        node_ptr g = p->parent, u = node::uncle(x);
        if (isBlack(u)) {
            if (node::isLChild(x) == node::isLChild(p)) {
                p->color = RB_BLACK;
            } else {
                x->color = RB_BLACK;
            }
            g->color = RB_RED;
            _base::rotateAndConnect(x);
        } else {
            p->color = RB_BLACK;
            ++p->height;
            u->color = RB_BLACK;
            ++u->height;
            if (!node::isRoot(g)) { g->color = RB_RED; }
            solveDoubleRed(g);
        }
    }

    void solveDoubleBlack(node_ptr r) {
        node_ptr p = r ? r->parent : _base::_hot;
        if (!p) { return; }
        node_ptr s = node::sibling(r);
        if (isBlack(s)) {
            node_ptr t = nullptr;
            if (isRed(s->rChild)) { t = s->rChild; }
            if (isRed(s->lChild)) { t = s->lChild; }
            if (t) {
                rb_color old_color = p->color;
                node_ptr b         = _base::rotateAndConnect(t);
                if (node::hasLChild(b)) {
                    b->lChild->color = RB_BLACK;
                    updateHeight(b->lChild);
                }
                if (node::hasRChild(b)) {
                    b->rChild->color = RB_BLACK;
                    updateHeight(b->rChild);
                }
                b->color = old_color;
                updateHeight(b);
            } else {
                s->color = RB_RED;
                --s->height;
                if (isRed(p)) {
                    p->color = RB_BLACK;
                } else {
                    --p->height;
                    solveDoubleBlack(p);
                }
            }
        } else {  // BB-3
            s->color    = RB_BLACK;
            p->color    = RB_RED;
            node_ptr t  = node::isLChild(s) ? s->lChild : s->rChild;
            _base::_hot = p;
            _base::rotateAndConnect(t);
            solveDoubleBlack(r);
        }
    }

    int updateHeight(node_ptr x) {
        x->height =
            std::max(node::stature(x->lChild), node::stature(x->rChild));
        return isBlack(x) ? ++(x->height) : x->height;
    }

public:
    node_ptr insert(T const& e) {
        node_ptr& x = _base::search(e);
        if (x) { return x; }
        x = new node(e, _base::_hot, nullptr, nullptr, -1);
        ++_base::_size;
        solveDoubleRed(x);
        return x ? x : _base::_hot->parent;
    }
    bool remove(T const& e) {
        node_ptr& x = _base::search(e);
        if (!x) { return false; }
        node_ptr r = _base::removeAt(x, _base::_hot);
        if (!(--_base::_size)) { return true; }
        if (!_base::hot()) {
            _base::_root->color = RB_BLACK;
            updateHeight(_base::_root);
            return true;
        }
        if (isBlackHeightUpdated(_base::hot())) { return true; }
        if (isRed(r)) {
            r->color = RB_BLACK;
            ++r->height;
            return true;
        }
        solveDoubleBlack(r);
        return true;
    }
    friend std::ostream& operator<<(std::ostream& out, const_ref rb_tree) {
        out << rb_tree.root()->toStringRB("", "");
        return out;
    }
};

// end of namespace libds
}

#endif /* RedBlackTree_hpp */
