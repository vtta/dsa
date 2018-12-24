//
//  CompleteHeap.hpp
//  libds
//
//  Created by v tta on 12/19/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef CompleteHeap_hpp
#define CompleteHeap_hpp

#include "../others/PriorityQueueInterface.hpp"
#include "../linear/Vector.hpp"

namespace libds {
// begining of namespace libds

template <typename value_type>
class CompleteHeap : public PriorityQueueInterface<value_type>,
                     public Vector<value_type> {
    using _base_vec       = Vector<value_type>;
    using _base_pq        = PriorityQueueInterface<value_type>;
    using value_const_ref = value_type const&;
    using value_const_ptr = value_type*;

protected:
    int percolateDown(int i) {
        int j;
        while (i != (j = properParent(i))) {
            std::swap(_base_vec::_elem[i], _base_vec::_elem[j]);
            i = j;
        }
        return i;
    }
    int percolateUp(int i) {
        while (hasParent(i)) {
            int j = parent(i);
            if (_base_vec::_elem[i] < _base_vec::_elem[j]) { break; }
            std::swap(_base_vec::_elem[i], _base_vec::_elem[j]);
            i = j;
        }
        return i;
    }
    void heapify() {
        for (auto i = lastInternal(); isInside(i); --i) { percolateDown(i); }
    }

    bool isInside(int i) const { return -1 < i && i < _base_vec::size(); }
    int parent(int i) const { return (i - 1) / 2; }
    int lastInternal() const { return parent(_base_vec::size() - 1); }
    int lChild(int i) const { return 2 * i + 1; }
    int rChild(int i) const { return 2 * i + 2; }
    bool hasParent(int i) const { return i > 0; }
    bool hasLChild(int i) const { return isInside(lChild(i)); }
    bool hasRChild(int i) const { return isInside(rChild(i)); };
    int properParent(int i, int n = _base_vec::size()) {
        auto bigger = [&](int i, int j) {
            return _base_vec::_elem[i] >= _base_vec::_elem[j] ? i : j;
        };
        return hasRChild(i) ? bigger(bigger(i, lChild(i)), rChild(i))
                            : (hasLChild(i) ? bigger(i, lChild(i)) : i);
    }

public:
    CompleteHeap() {}
    CompleteHeap(value_const_ptr V, int n) {
        _base_vec::copy_from(V, 0, n);
        heapify();
    }
    CompleteHeap(value_const_ptr V, int lo, int hi) {
        _base_vec::copy_from(V, lo, hi);
        heapify();
    }

    void insert(value_const_ref elem) {
        _base_vec::insert(elem);
        percolateUp(_base_vec::size() - 1);
    }
    value_type max() const { return _base_vec::_elem[0]; }
    value_type eraseMax() {
        value_type m        = max();
        _base_vec::_elem[0] = _base_vec::remove(_base_vec::size() - 1);
        percolateDown(0);
        return m;
    }
};
// end of namespace libds
}

#endif /* CompleteHeap_hpp */
