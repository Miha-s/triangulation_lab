#include "MonotonePolygon.hpp"

#include <SFML/System/Vector2.hpp>
#include <cmath>

#include "EdgesBinaryTree.hpp"

enum VertexType
{
    Start,
    End,
    Regular,
    Split,
    Merge
};

float
get_angle_in_clockwise( sf::Vector2f a, sf::Vector2f b, sf::Vector2f c )
{
    double angle1 = atan2( b.y - a.y, b.x - a.x );
    double angle2 = atan2( c.y - b.y, c.x - b.x );

    double angle = angle2 - angle1;
    if ( angle < 0 )
    {
        angle += 2 * M_PI;  // Convert negative angle to positive
    }
    return angle;
}

VertexType
get_vertex_type( const HalfEdgeList& edges_list, HalfEdgeRecord id )
{
    auto prev = edges_list.get_origin( edges_list.get_prev( id ) );
    auto curr = edges_list.get_origin( id );
    auto next = edges_list.get_origin( edges_list.get_next( id ) );
    auto p1 = sf::Vector2f{ curr - prev };
    auto p2 = sf::Vector2f{ next - curr };

    auto angle = get_angle_in_clockwise( prev, curr, next );

    if ( curr > prev && curr > next )
    {
        if ( angle <= M_PI )
        {
            return Start;
        }
        else
        {
            return Split;
        }
    }
    if ( prev > curr && next > curr )
    {
        if ( angle <= M_PI )
        {
            return End;
        }
        else
        {
            return Merge;
        }
    }

    return Regular;
}

bool
interior_to_the_right( const HalfEdgeList& edges_list, HalfEdgeRecord id )
{
    auto prev = edges_list.get_prev( id );
    if ( edges_list.get_origin( prev ).y > edges_list.get_origin( id ).y )
    {
        return true;
    }
    return false;
}
bool
point_on_the_leftt( sf::Vector2f start, sf::Vector2f end, sf::Vector2f point )
{
    return ( end.x - start.x ) * ( point.y - start.y ) - ( end.y - start.y ) * ( point.x - start.x )
           > 0;
}

void
calculate_monotone_polygon( HalfEdgeList& edges_list )
{
    EdgesBinaryTree binary_tree{ edges_list };
    auto vertices = edges_list.get_sorted_vertices( );

    for ( const auto& vi : vertices )
    {
        auto ids = edges_list.get_records( vi );
        for ( auto id : ids )
        {
            auto prev_id = edges_list.get_prev( id );
            auto type = get_vertex_type( edges_list, id );
            if ( type == Start )
            {
                binary_tree.insert_edge( id );
                binary_tree.set_helper( id, id );
            }
            else if ( type == End )
            {
                if ( binary_tree.is_merge_helper( prev_id ) )
                {
                    edges_list.insert_diagonal( id, binary_tree.get_helper( prev_id ).id );
                }
                binary_tree.remove_edge( prev_id );
            }
            else if ( type == Split )
            {
                auto ej = binary_tree.get_left_edge( id );
                auto there_back  = edges_list.insert_diagonal( id, binary_tree.get_helper( ej ).id );
                binary_tree.set_helper( ej, id );
                binary_tree.insert_edge( id );
                binary_tree.set_helper( id, id );
            }
            else if ( type == Merge )
            {
                if ( binary_tree.is_merge_helper( prev_id ) )
                {
                    edges_list.insert_diagonal( id, binary_tree.get_helper( prev_id ).id );
                }
                binary_tree.remove_edge( prev_id );
                auto ej = binary_tree.get_left_edge( id );
                if ( binary_tree.is_merge_helper( ej ) )
                {
                    edges_list.insert_diagonal( id, binary_tree.get_helper( ej ).id );
                }
                binary_tree.set_helper( ej, { EdgesBinaryTree::Helper::Merge, id } );
            }
            else
            {
                if ( interior_to_the_right( edges_list, id ) )
                {
                    if ( binary_tree.is_merge_helper( prev_id ) )
                    {
                        edges_list.insert_diagonal( id, binary_tree.get_helper( prev_id ).id );
                    }
                    binary_tree.remove_edge( prev_id );
                    binary_tree.insert_edge( id );
                    binary_tree.set_helper( id, id );
                }
                else
                {
                    auto ej = binary_tree.get_left_edge( id );
                    if ( binary_tree.is_merge_helper( ej ) )
                    {
                        edges_list.insert_diagonal( id, binary_tree.get_helper( ej ).id );
                    }
                    binary_tree.set_helper( ej, id );
                }
            }
        }
    }
}
