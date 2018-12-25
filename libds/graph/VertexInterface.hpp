//
//  VertexInterface.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <cstdio>
#include <climits>

namespace libds {
// beginning of namespace

typedef enum { UNDISCOVERED, DISCOVERED, VISITED } vertex_status;

template <typename vertex_data_type>
class VertexInterface {
public:
    VertexInterface(vertex_data_type const& d = (vertex_data_type)0)
        : data(d),
          in_degree(0),
          out_degree(0),
          status(UNDISCOVERED),
          d_time(-1),
          f_time(-1),
          parent(-1),
          priority(INT_MAX) {}

private:
    vertex_data_type data;
    int              in_degree, out_degree;
    vertex_status    status;
    int              d_time, f_time;
    int              parent;
    int              priority;
};

// end of namespace libds
}
#endif /* VertexInterface_hpp */
