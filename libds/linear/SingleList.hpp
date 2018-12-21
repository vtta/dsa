//
//  SingleList.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef SingleList_hpp
#define SingleList_hpp

namespace libds {
// beginning of namespace libds

template <typename value_type>
class SingleListNode {
    using pointer         = SingleListNode<value_type> *;
    using value_const_ref = value_type const &;

public:
    value_type data;
    pointer    next;
    SingleListNode() : next(nullptr) {}
    SingleListNode(value_type e, pointer s = nullptr) : data(e), next(s) {}

    pointer insert_as_succ(value_const_ref e) {
        pointer x   = new SingleListNode(e, next);
        return next = x;
    }
};

template <typename value_type>
class SingleList {
    using node_type       = SingleListNode<value_type>;
    using node_ptr        = SingleListNode<value_type> *;
    using value_const_ref = value_type const &;

private:
    int      _size;
    node_ptr header, trailer;

protected:
    int delete_all_nodes() {
        int res = 0;
        for (node_ptr p = header->next, succ = nullptr; p != trailer;) {
            succ = p->next;
            delete p;
            ++res;
            p = succ;
        }
        return res;
    }

public:
    SingleList() : _size(0) {
        header       = new node_type;
        trailer      = new node_type;
        header->next = trailer;
    }
    ~SingleList() {
        delete_all_nodes();
        delete header;
        delete trailer;
    }

    value_type &operator[](int r) {
        node_ptr p = header->next;
        for (int i = 0; i < r; ++i) { p = p->next; }
        return p->data;
    }

    value_type erase(node_ptr p) {
        node_ptr prev_of_p = header;
        while (prev_of_p->next != p) { prev_of_p = prev_of_p->next; }
        prev_of_p->next = p->next;
        value_type res  = p->data;
        delete p;
        --_size;
        return res;
    }

    bool empty() const { return front() == tail(); }
    int  size() const { return _size; }

    node_ptr head() const { return header; }
    node_ptr tail() const { return trailer; }
    node_ptr front() { return header->next; }
    node_ptr back() {
        node_ptr res = head();
        while (res->next != tail()) { res = res->next; }
        return res;
    }

    node_ptr push_front(value_const_ref e) { return insert_after(head(), e); }
    node_ptr push_back(value_const_ref e) { return insert_before(tail(), e); }
    node_ptr insert_after(node_ptr p, value_const_ref e) {
        ++_size;
        return p->insert_as_succ(e);
    }
    node_ptr insert_before(node_ptr p, value_const_ref e) {
        node_ptr prev_of_p = header;
        while (prev_of_p->next != p) { prev_of_p = prev_of_p->next; }
        ++_size;
        return prev_of_p->insert_as_succ(e);
    }

    static void swap_data(node_ptr x, node_ptr y) {
        (x == nullptr || y == nullptr) ?: swap_data(*x, *y);
    }
    static void swap_data(node_type &x, node_type &y) {
        node_type t = x;
        x.data      = y.data;
        y.data      = t.data;
    }
};

// end of namespace libds
}
#endif /* SingleList_hpp */
