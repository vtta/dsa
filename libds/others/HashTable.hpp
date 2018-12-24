//
//  HashTable.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef HashTable_hpp
#define HashTable_hpp

#include "../others/DictionaryInterface.hpp"
#include "../linear/BitSet.hpp"
#include "../others/Utils.hpp"

namespace libds {
// beginning of namespace libds

template <typename key_type, typename value_type,
          typename hasher_type = Hasher<key_type>>
class HashTable : public DictionaryInterface<key_type, value_type> {
    using pair_type     = Pair<key_type, value_type>;
    using pair_ptr      = pair_type*;
    using key_const_ref = key_type const&;

private:
    pair_ptr* ht;

    int bucket_size;
    int item_size;

    hasher_type hasher;
    BitSet      lazyRemoval;

protected:
    int probe4Hit(key_const_ref k) const {
        int r = hasher(k) % bucket_size;
        while ([&]() {
            return ((ht[r] != nullptr) && (k != ht[r]->first)) ||
                   ((ht[r] == nullptr) && lazyRemoval.test(r));
        }()) {
            r = (r + 1) % bucket_size;
        }
        return r;
    }
    int probe4Free(key_const_ref k) const {
        int r = hasher(k) % bucket_size;
        while (ht[r]) { r = (r + 1) % bucket_size; }
        return r;
    }
    void rehash() {
        auto old_bucket_size = bucket_size;
        auto old_ht          = ht;
        bucket_size          = (int)primeNLT(bucket_size * 2);
        item_size            = 0;
        ht                   = new pair_ptr[bucket_size]();
        lazyRemoval = BitSet(bucket_size);
        for (auto i = 0; i < old_bucket_size; ++i) {
            if (old_ht[i]) { at(old_ht[i]->first) = old_ht[i]->second; }
        }
        delete[] old_ht;
    }

public:
    HashTable(int b = 53)
        : bucket_size((int)primeNLT(b)),
          item_size(),
          hasher(hasher_type()),
          lazyRemoval(bucket_size) {
        ht = new pair_ptr[bucket_size]();
    }
    ~HashTable() {
        for (auto i = 0; i < bucket_size; ++i) {
            // if (ht[i]) { delete ht[i]; }
        }
        delete[] ht;
    }

    int size() const { return item_size; }

    value_type& at(key_const_ref k) {
        int r = probe4Hit(k);
        if (!ht[r]) {
            ht[r] = new pair_type(k);
            ++item_size;
            if (item_size * 2 > bucket_size) {
                rehash();
                return at(k);
            }
        }
        return ht[r]->second;
    }
    bool erase(key_const_ref k) {
        int r = probe4Hit(k);
        if (!ht[r]) { return false; }
        delete ht[r];
        ht[r] = nullptr;
        lazyRemoval.set(r);
        --item_size;
        return true;
    }
};

// end of namespace libds
}

#endif /* HashTable_hpp */
