//
//  Stack.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef Stack_hpp
#define Stack_hpp

#include "../linear/SingleList.hpp"

namespace libds {
// begining of namespace libds

template <typename value_type>
class Stack : private SingleList<value_type> {
    using node_type       = SingleListNode<value_type>;
    using node_ptr        = node_type *;
    using value_const_ref = value_type const &;
    using _base           = SingleList<value_type>;

public:
    value_type pop() { return _base::erase(_base::front()); }
    void push(value_const_ref e) { _base::push_front(e); }

    value_type top() const { return _base::head()->next->data; }

    int  size() const { return _base::size(); }
    bool empty() const { return _base::empty(); }
};

// end of namespace libds
}

#endif /* Stack_hpp */
