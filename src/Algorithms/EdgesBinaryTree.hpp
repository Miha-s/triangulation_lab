#ifndef EDGESBINARYTREE_HPP
#define EDGESBINARYTREE_HPP
#include "HalfEdgeList.hpp"

class EdgesBinaryTree
{
public:
    struct Helper
    {
        enum Type
        {
            Ordinary,
            Merge
        };

        Type type;

        HalfEdgeRecord id;
    };

private:
    const HalfEdgeList& m_edges_list;

    struct EdgesTreeNode
    {
        HalfEdgeRecord id;
        Helper helper;

        bool
        operator==( const EdgesTreeNode& other );

    };

    std::vector< EdgesTreeNode > m_edges_tree;

    std::vector< EdgesTreeNode >::iterator get_first_on_right(HalfEdgeRecord id );

public:
    EdgesBinaryTree( const HalfEdgeList& edges_list );

    void insert_edge( HalfEdgeRecord id );
    void remove_edge( HalfEdgeRecord id );
    void set_helper( HalfEdgeRecord id, Helper helper );
    Helper get_helper( HalfEdgeRecord id );
    bool is_merge_helper( HalfEdgeRecord id );
    void set_helper( HalfEdgeRecord id, HalfEdgeRecord helper );

    HalfEdgeRecord get_left_edge( HalfEdgeRecord id );

};

#endif  // EDGESBINARYTREE_HPP
