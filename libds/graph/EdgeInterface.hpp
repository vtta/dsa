//
//  EdgeInterface.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef Edge_hpp
#define Edge_hpp

#include <cstdio>

namespace libds {
// beginning of namespace libds

typedef enum { UNDETERMINED, TREE, CROSS, FORWARD, BACKWARD } edge_status;

template <typename edge_data_type>
class EdgeInterface {
public:
    EdgeInterface(edge_data_type const& e, int weight)
        : data(e), weight(weight), status(UNDETERMINED) {}

private:
    edge_data_type data;
    int            weight;
    edge_status    status;
};

// end of namespace libds
}
#endif /* EdgeInterface_hpp */
