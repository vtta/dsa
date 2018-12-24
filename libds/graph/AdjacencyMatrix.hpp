//
//  AdjacencyMatrix.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef AdjacencyMatrix_hpp
#define AdjacencyMatrix_hpp

#include "GraphInterface.hpp"
#include "../linear/Vector.hpp"

namespace libds {
// beginning of namespace libds

template <typename vertex_type, typename edge_type>
class AdjacencyMatrix : public GraphInterface<vertex_type, edge_type> {
    Vector<Vertex<vertex_type>>      V;
    Vector<Vector<Edge<edge_type>*>> E;

public:
    AdjacencyMatrix() { this->_vertex_size = this->_edge_size = 0; }
    ~AdjacencyMatrix() {
        for (auto i = 0; i < this->edge_size(); ++i)
            for (auto j = 0; j < this->edge_size(); ++j) delete E.at(i).at(j);
    }

    virtual vertex_type& vertex(int v) { return V.at(v).data; }
    virtual int& in_degree(int v) { return V.at(v).in_degree; }
    virtual int& out_degree(int v) { return V.at(v).out_degree; }
    virtual int first_neighbor(int v) {
        return next_neighbor(v, this->_vertex_size);
    }
    virtual int next_neighbor(int v, int j) {
        while ((-1 < j) && (!exists(v, --j))) {}
        return j;
    }

    virtual vertex_type& status(int v) { return V.at(v).status; }
    virtual int& d_time(int v) { return V.at(v).d_time; }
    virtual int& f_time(int v) { return V.at(v).f_time; }
    virtual int& parent(int v) { return V.at(v).parent; }
    virtual int& priority(int v) { return V.at(v).priority; }

    virtual int insert(vertex_type const& vertex) {
        for (auto i = 0; i < this->edge_size(); ++i) {
            E.at(i).insert(nullptr);
        }
        ++this->_vertex_size;
        E.insert(Vector<Edge<edge_type>*>(this->vertex_size(),
                                          this->vertex_size(),
                                          (Edge<edge_type>*)nullptr));
        return V.insert(Vertex<vertex_type>(vertex));
    }
    virtual vertex_type remove(int v) {
        for (auto i = 0; i < this->edge_size(); ++i) {
            if (exists(v, i)) {
                delete E.at(v).at(i);
                --(V.at(i).in_degree);
            }
        }
        E.remove(v);
        --this->_vertex_size;
        for (auto i = 0; i < this->edge_size(); ++i) {
            if (exists(i, v)) {
                delete E.at(i).remove(i);
                --(V.at(i).out_degree);
            }
        }
        vertex_type res = vertex(v);
        V.remove(v);
        return res;
    }

    virtual bool exists(int s, int t) {
        return (0 <= s) && (s < this->edge_size()) && (0 <= t) &&
               (t < this->edge_size()) && (E.at(s).at(t) != nullptr);
    }

    virtual edge_status& status(int s, int t) { return E.at(s).at(t)->status; }
    virtual edge_type& edge(int s, int t) { return E.at(s).at(t)->data; }
    virtual int& weight(int s, int t) { return E.at(s).at(t)->weight; }

    virtual void insert(edge_type const& edge_value, int weight, int s, int t) {
        if (exists(s, t)) return;
        E.at(s).at(t) = new Edge<edge_type>(edge_value, weight);
        ++this->_edge_size;
        ++V.at(s).out_degree;
        ++V.at(t).in_degree;
    }
    virtual edge_type remove(int s, int t) {
        edge_type bak = edge(s, t);
        delete E.at(s).at(t);
        E.at(s).at(t) = nullptr;
        --this->_edge_size;
        --V.at(s).out_degree;
        --V.at(t).in_degree;
        return bak;
    }
};

// end of namespace libds
}
#endif /* AdjacencyMatrix_hpp */
