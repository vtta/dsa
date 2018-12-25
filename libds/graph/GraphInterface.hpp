//
//  GraphInterface.hpp
//  libds
//
//  Created by v tta on 11/28/18.
//  Copyright © 2018 vtta. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include "../graph/EdgeInterface.hpp"
#include "../graph/VertexInterface.hpp"
#include "../linear/Vector.hpp"
#include "../linear/Stack.hpp"
#include "../linear/Queue.hpp"

namespace libds {
// beginning of namespace libds

template <typename vertex_type, typename edge_type>
class GraphInterface {
public:
    int         vertex_size() const { return _vertex_size; }
    virtual int insert(vertex_type const& e) = 0;
    virtual vertex_type remove(int)          = 0;
    virtual int         in_degree(int)       = 0;
    virtual int         out_degree(int)      = 0;
    virtual int         first_neighbor(int)  = 0;
    virtual int         next_neighbor(int, int) = 0;

    virtual vertex_type&   vertex(int)   = 0;
    virtual vertex_status& status(int)   = 0;
    virtual int&           d_time(int)   = 0;
    virtual int&           f_time(int)   = 0;
    virtual int&           parent(int)   = 0;
    virtual int&           priority(int) = 0;

    int               edge_size() const { return _edge_size; }
    virtual bool      exists(int, int) = 0;
    virtual void      insert(edge_type const&, int, int, int) = 0;
    virtual edge_type remove(int, int) = 0;

    virtual edge_status& status(int, int) = 0;
    virtual edge_type&   edge(int, int)   = 0;
    virtual int&         weight(int, int) = 0;

    void bfs(int s) {
        reset();
        auto i = s, clock = 0;
        do {
            if (status(i) == UNDISCOVERED) { bfs_single(i, clock); }
        } while (s != (i = (++i) % vertex_size()));
    }

    void                dfs(int);
    void                bcc(int);
    Stack<vertex_type>* t_sort(int);
    void                prim(int);
    void                dijkstra(int);
    template <class PU>
    void pfs(int, PU);

    virtual edge_type& type(int, int) = 0;

protected:
    void bfs_single(int v, int& clock) {
        Queue<int> q;
        status(v) = DISCOVERED;
        q.push(v);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            d_time(v) = ++clock;
            for (auto u = first_neighbor(v); - 1 < u; u = next_neighbor(v, u)) {
                if (status(u) == UNDISCOVERED) {
                    status(u) = DISCOVERED;
                    q.push(u);
                    type(v, u) = TREE;
                    parent(u) = v;

                } else {
                    type(v, u) = CROSS;
                }
                status(v) = VISITED;
            }
        }
    }

private:
    int _vertex_size;
    int _edge_size;
    /// reset every vertex and edge visited
    void reset() {
        for (auto i = 0; i < vertex_size(); ++i) {
            status(i) = UNDISCOVERED;
            d_time(i) = f_time(i) = -1;
            parent(i)             = -1;
            priority(i)           = INT_MAX;
            for (auto j = 0; j < vertex_size(); ++j) {
                if (exists(i, j)) { type(i, j) = UNDETERMINED; }
            }
        }
        return;
    }
};

// end of namespace libds
}
#endif /* GraphInterface_hpp */
