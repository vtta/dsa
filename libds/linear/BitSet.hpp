//
//  BitSet.hpp
//  libds
//
//  Created by v tta on 12/24/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef BitSet_hpp
#define BitSet_hpp

#include <climits>
#include <cmath>

namespace libds {
// beginning of namespace libds

class BitSet {
    using size_type = unsigned long;
    using self_ref  = BitSet&;

private:
    static const size_type INT_BIT = CHAR_BIT * sizeof(int);

    size_type length_in_bit;
    int*      array;

public:
    BitSet(size_type length = 64) : length_in_bit(length) {
        array = new int[std::ceil(length_in_bit / INT_BIT)]();
    }
    ~BitSet() {
        // delete[] array;
    }
    size_type size() const { return length_in_bit; }
    self_ref resize(size_type length) {
        int* old_array = array;
        array          = new int[std::ceil(length / INT_BIT)]();
        for (auto i = 0; i < std::ceil(length / INT_BIT); ++i) {
            array[i] = old_array[i];
        }
        delete[] old_array;
        return *this;
    }

    // to-do
    // size_type count() const;
    // bool any() const;
    // bool all() const;
    // bool none() const;

    bool test(size_type k) const {
        return array[k / INT_BIT] & (1U << (k % INT_BIT));
    }

    self_ref set(size_type k) {
        array[k / INT_BIT] |= (1U << (k % INT_BIT));
        return *this;
    }
    self_ref reset(size_type k) {
        array[k / INT_BIT] &= ~(1U << (k % INT_BIT));
        return *this;
    }
    self_ref flip(size_type k) {
        array[k / INT_BIT] ^= (1U << (k % INT_BIT));
        return *this;
    }

    bool operator[](size_type k) const { return test(k); }
};

// end of namespace libds
}
#endif /* BitSet_hpp */
