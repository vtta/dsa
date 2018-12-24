//
//  DictionaryInterface.hpp
//  libds
//
//  Created by v tta on 12/23/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef DictionaryInterface_hpp
#define DictionaryInterface_hpp

#include "../others/Pair.hpp"

namespace libds {
// beginning of namespace libds

template <typename key_type, typename value_type>
struct DictionaryInterface {
    virtual int         size() const           = 0;
    virtual value_type& at(key_type const&)    = 0;
    virtual bool        erase(key_type const&) = 0;
};

// end of namespace libds
}

#endif /* DictionaryInterface_hpp */
