//
//  Pair.hpp
//  libds
//
//  Created by v tta on 12/12/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef Pair_hpp
#define Pair_hpp

namespace libds {
// beginning of namespace libds
template <typename first_elem_type, typename second_elem_type>
struct Pair {
    first_elem_type  first;
    second_elem_type second;
    Pair(first_elem_type first_elem) : first(first_elem), second() {}
    Pair(first_elem_type first_elem, second_elem_type second_elem)
        : first(first_elem), second(second_elem) {}
};

// end of namespace libds
}

#endif /* Pair_hpp */
