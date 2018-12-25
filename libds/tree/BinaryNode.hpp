//
//  BinaryNode.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef BinaryNode_hpp
#define BinaryNode_hpp

#include "../linear/Stack.hpp"
#include "../linear/Queue.hpp"
#include <string>
#include <iostream>

namespace libds {
// begining of namespace libds

typedef enum { RB_RED, RB_BLACK } rb_color;

template <typename T>
class BinaryNode {
    using pointer   = BinaryNode<T> *;
    using const_ptr = BinaryNode<T> const *;
    using const_ref = BinaryNode<T> const &;

protected:
    template <typename VST>
    static void travPre_I(pointer x, VST &visit) {
        Stack<pointer> s;
        while (true) {
            for (auto i = x; i; i = i->lChild) {
                visit(i->data);
                s.push(i->rChild);
            }
            if (s.empty()) break;
            x = s.top();
            s.pop();
        }
    }
    template <typename VST>
    static void travIn_I(pointer x, VST &visit) {
        Stack<pointer> s;
        while (true) {
            for (auto i = x; i; i = i->lChild) s.push(i);
            if (s.empty()) break;
            x = s.top();
            s.pop();
            visit(x->data);
            x = x->rChild;
        }
    }
    template <typename VST>
    static void travPost_I(pointer x, VST &visit);
    template <typename VST>
    void travLevel_I(pointer x, VST &visit) {
        Queue<pointer> q;
        q.push(x);
        while (!q.empty()) {
            x = q.top();
            q.pop();
            visit(x->data);
            if (hasLChild(x)) q.push(x->lChild);
            if (hasRChild(x)) q.push(x->rChild);
        }
    }
    static void release(pointer x) { delete x; }

public:
    T        data;
    pointer  parent;
    pointer  lChild;
    pointer  rChild;
    int      height;
    int      npl;
    rb_color color;
    BinaryNode()
        : parent(nullptr),
          lChild(nullptr),
          rChild(nullptr),
          height(0),
          npl(1),
          color(RB_RED) {}
    BinaryNode(T e, pointer parent = nullptr, pointer lChild = nullptr,
               pointer rChild = nullptr, int height = 0, int npl = 1,
               rb_color color = RB_RED)
        : data(e),
          parent(parent),
          lChild(lChild),
          rChild(rChild),
          height(height),
          npl(npl),
          color(color) {}
    int     size();
    pointer insertAsLChild(T const &e) {
        return lChild = new BinaryNode(e, this);
    }
    pointer insertAsRChild(T const &e) {
        return rChild = new BinaryNode(e, this);
    }
    pointer succ() {
        pointer s = this;
        if (hasRChild()) {
            s                      = rChild;
            while (hasLChild(s)) s = s->lChild;
        } else {
            while (isRChild(s)) s = s->parent;
            s                     = s->parent;
        }
        return s;
    }
    template <typename VST>
    void travLevel(VST &);
    template <typename VST>
    void travPre(VST &visit) {}
    template <typename VST>
    void travIn(VST &);
    template <typename VST>
    void travPost(VST &);
    bool operator<(const_ref bn) { return data < bn.data; }
    bool operator==(const_ref bn) { return data == bn.data; }
    bool operator<=(const_ref bn) { return *this < bn || *this == bn; }
    bool operator>(const_ref bn) { return !(*this <= bn); }
    bool operator>=(const_ref bn) { return !(*this < bn); }
    bool operator!=(const_ref bn) { return !(*this == bn); }

    bool isRoot() const { return parent == nullptr; }
    bool isLChild() const { return hasParent() && (parent->lChild == this); }
    bool isRChild() const { return hasParent() && (parent->rChild == this); }
    bool hasChild() const { return hasLChild() || hasRChild(); }
    bool hasParent() const { return parent != nullptr; }
    bool hasLChild() const { return lChild; }
    bool hasRChild() const { return rChild; }
    bool hasBothChild() const { return hasLChild() && hasRChild(); }
    bool hasSibling() const { return hasParent() && parent->hasBothChild(); }
    bool isLeaf() const { return !hasChild(); }

    static bool hasParent(pointer p) { return p->parent; }
    static bool isRoot(pointer p) { return !hasParent(p); }
    static bool isLChild(pointer p) {
        return p->parent && p->parent->lChild == p;
    }
    static bool isRChild(pointer p) {
        return p->parent && p->parent->rChild == p;
    }
    static bool hasChild(pointer p) { return hasLChild(p) || hasRChild(p); }
    static bool hasLChild(pointer p) { return p->lChild; }
    static bool hasRChild(pointer p) { return p->rChild; }
    static bool hasBothChild(pointer p) { return hasLChild(p) && hasRChild(p); }
    static bool hasSibling(pointer p) {
        return hasParent(p) && hasBothChild(p->parent);
    }
    static bool isLeaf(pointer p) { return !hasChild(p); }

    static int stature(pointer p) { return p ? p->height : -1; }
    static pointer sibling(pointer x) {
        if (hasParent(x) && hasBothChild(x->parent)) {
            return isLChild(x) ? x->parent->rChild : x->parent->lChild;
        }
        return nullptr;
    }
    static pointer uncle(pointer x) {
        if (hasParent(x) && hasBothChild(x->parent) &&
            hasBothChild(x->parent->parent)) {
            return isLChild(x->parent) ? x->parent->parent->rChild
                                       : x->parent->parent->lChild;
        }
        return nullptr;
    }

    std::string toString(std::string prefix, std::string childPrefix) const {
        std::string firstLine  = prefix + std::to_string(data) + "\n";
        std::string firstChild = "";
        std::string lastChild  = "";
        if (hasBothChild()) {
            firstChild =
                lChild->toString(childPrefix + "├── ", childPrefix + "│   ");
            lastChild =
                rChild->toString(childPrefix + "└── ", childPrefix + "    ");
        } else if (hasLChild()) {
            lastChild =
                lChild->toString(childPrefix + "└── ", childPrefix + "    ");
        } else if (hasRChild()) {
            lastChild =
                rChild->toString(childPrefix + "└── ", childPrefix + "    ");
        }
        return firstLine + firstChild + lastChild;
    }
    std::string toStringRB(std::string prefix, std::string childPrefix) const {
        std::string firstLine = prefix + std::to_string(data) + " " +
                                (color == RB_RED ? "R" : "B") + "\n";
        std::string firstChild = "";
        std::string lastChild  = "";
        if (hasBothChild()) {
            firstChild =
                lChild->toStringRB(childPrefix + "├── ", childPrefix + "│   ");
            lastChild =
                rChild->toStringRB(childPrefix + "└── ", childPrefix + "    ");
        } else if (hasLChild()) {
            lastChild =
                lChild->toStringRB(childPrefix + "└── ", childPrefix + "    ");
        } else if (hasRChild()) {
            lastChild =
                rChild->toStringRB(childPrefix + "└── ", childPrefix + "    ");
        }
        return firstLine + firstChild + lastChild;
    }
    friend std::ostream &operator<<(std::ostream &out, const_ref node) {
        // print_ostream(out, &node);
        out << node.toString("", "");
        return out;
    }
};

// end of namespace libds
}
#endif /* BinaryNode_hpp */
