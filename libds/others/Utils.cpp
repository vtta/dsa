//
//  Utils.cpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#include "Utils.hpp"
namespace libds {
// beginning of namespace libds

int rand() {
    std::srand((unsigned int)time(nullptr));
    return std::rand();
}

template <typename T>
void swap(T& x, T& y) {
    return std::swap(x, y);
}

unsigned long primeNLT(unsigned long x) {
    unsigned long primes[26] = {
        53,        97,        193,      389,       769,       1543,
        3079,      6151,      12289,    24593,     49157,     98317,
        196613,    393241,    786433,   1572869,   3145739,   6291469,
        12582917,  25165843,  50331653, 100663319, 201326611, 402653189,
        805306457, 1610612741};
    for (auto i = 0; i < 26; ++i) {
        if (primes[i] >= x) { return primes[i]; }
    }
    throw std::out_of_range("prime too large");
}

// end of namespace libds
}
