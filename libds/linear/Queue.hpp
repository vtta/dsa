//
//  Queue.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef Queue_hpp
#define Queue_hpp

#include "../linear/SingleList.hpp"

namespace libds {
// begining of namespace libds

template <typename value_type>
class Queue : public SingleList<value_type> {
    using node_type       = SingleListNode<value_type>;
    using node_ptr        = node_type *;
    using value_const_ref = value_type const &;
    using _base           = SingleList<value_type>;

public:
    value_type pop() { return _base::erase(_base::front()); }
    void push(value_const_ref e) { _base::push_back(e); }

    value_type top() { return _base::front()->data; }
    value_type front() { return _base::front()->data; }
    value_type back() { return _base::back()->data; }
};

// end of namespace libds
}
#endif /* Queue_hpp */
