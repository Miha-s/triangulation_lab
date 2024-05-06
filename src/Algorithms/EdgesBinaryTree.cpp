#include "EdgesBinaryTree.hpp"
#include <algorithm>

bool
point_on_the_left( sf::Vector2f start, sf::Vector2f end, sf::Vector2f point )
{
    return ( end.x - start.x ) * ( point.y - start.y ) - ( end.y - start.y ) * ( point.x - start.x )
           > 0;
}

std::vector< EdgesBinaryTree::EdgesTreeNode >::iterator
EdgesBinaryTree::get_first_on_right( HalfEdgeRecord id )
{
    auto it = m_edges_tree.begin( );
    auto point = m_edges_list.get_origin( id );
    while ( it != m_edges_tree.end( ) )
    {
        auto start = m_edges_list.get_origin( it->id );
        auto end = m_edges_list.get_origin( m_edges_list.get_next( it->id ) );
        if ( point == start )
        {
            point = m_edges_list.get_origin( m_edges_list.get_next( id ) );
        }
        if ( !point_on_the_left( start, end, point ) )
        {
            break;
        }
        it++;
    }

    return it;
}

EdgesBinaryTree::EdgesBinaryTree( const HalfEdgeList& edges_list )
    : m_edges_list( edges_list )
{
}

void
EdgesBinaryTree::insert_edge( HalfEdgeRecord id )
{

    auto it = get_first_on_right( id );
    m_edges_tree.insert( it, { id, { Helper::Ordinary, {} } } );
}
#include <iostream>
void
EdgesBinaryTree::remove_edge( HalfEdgeRecord id )
{
    auto it = std::find( m_edges_tree.begin( ), m_edges_tree.end( ), EdgesTreeNode{ id, {} } );
    if(it == m_edges_tree.end()) {
        std::cout << "END" << std::endl;
    }
    m_edges_tree.erase( it );
}

void
EdgesBinaryTree::set_helper( HalfEdgeRecord id, Helper helper )
{
    auto it = std::find( m_edges_tree.begin( ), m_edges_tree.end( ), EdgesTreeNode{ id, {} } );
    it->helper = helper;
}

EdgesBinaryTree::Helper
EdgesBinaryTree::get_helper( HalfEdgeRecord id )
{
    auto it = std::find( m_edges_tree.begin( ), m_edges_tree.end( ), EdgesTreeNode{ id, {} } );
    return it->helper;
}

bool
EdgesBinaryTree::is_merge_helper( HalfEdgeRecord id )
{
    auto it = std::find( m_edges_tree.begin( ), m_edges_tree.end( ), EdgesTreeNode{ id, {} } );
    return it->helper.type == Helper::Merge;
}

void
EdgesBinaryTree::set_helper( HalfEdgeRecord id, HalfEdgeRecord helper )
{
    set_helper( id, Helper{ Helper::Ordinary, helper } );
}

HalfEdgeRecord
EdgesBinaryTree::get_left_edge( HalfEdgeRecord id )
{
    auto it = get_first_on_right( id );
    if(it == m_edges_tree.begin()) {
        std::cout << "Begin" << std::endl;
        return it->id;
    }
    return std::prev( it )->id;
}

bool
EdgesBinaryTree::EdgesTreeNode::operator==( const EdgesTreeNode& other )
{
    return id == other.id;
}
