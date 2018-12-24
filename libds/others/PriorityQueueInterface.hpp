//
//  PriorityQueueInterface.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef PriorityQueue_hpp
#define PriorityQueue_hpp

namespace libds {
// begining of namespace libds

template <typename value_type>
struct PriorityQueueInterface {
    using value_const_ref = value_type const&;

    virtual void       insert(value_const_ref) = 0;
    virtual value_type max() const             = 0;
    virtual value_type eraseMax()              = 0;
};

// end of namespace libds
}

#endif /* PriorityQueue_hpp */
