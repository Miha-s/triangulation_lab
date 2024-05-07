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

float
get_interior_angle( const HalfEdgeList& edges_list, HalfEdgeRecord id )
{
    auto prev = edges_list.get_origin( edges_list.get_prev( id ) );
    auto curr = edges_list.get_origin( id );
    auto next = edges_list.get_origin( edges_list.get_next( id ) );

    auto angle = get_angle_in_clockwise( prev, curr, next );
    return angle;
}

VertexType
get_vertex_type( const HalfEdgeList& edges_list, HalfEdgeRecord id )
{
    auto prev = edges_list.get_origin( edges_list.get_prev( id ) );
    auto curr = edges_list.get_origin( id );
    auto next = edges_list.get_origin( edges_list.get_next( id ) );

    auto angle = get_interior_angle(edges_list, id);

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
                auto there_back = edges_list.insert_diagonal( id, binary_tree.get_helper( ej ).id );
                binary_tree.set_helper( ej, there_back.first );
                binary_tree.insert_edge( id );
                binary_tree.set_helper( id, id );
            }
            else if ( type == Merge )
            {
                auto helper = id;
                if ( binary_tree.is_merge_helper( prev_id ) )
                {
                    edges_list.insert_diagonal( id, binary_tree.get_helper( prev_id ).id );
                }
                binary_tree.remove_edge( prev_id );
                auto ej = binary_tree.get_left_edge( id );
                if ( binary_tree.is_merge_helper( ej ) )
                {
                    auto there_back =
                            edges_list.insert_diagonal( id, binary_tree.get_helper( ej ).id );
                    helper = there_back.first;
                }
                binary_tree.set_helper( ej, { EdgesBinaryTree::Helper::Merge, helper } );
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
                        auto there_back =
                                edges_list.insert_diagonal( id, binary_tree.get_helper( ej ).id );
                        id = there_back.first;
                    }
                    binary_tree.set_helper( ej, id );
                }
            }
        }
    }
}

void
triangulate_monotone_polygon( HalfEdgeList& edges_list )
{
    std::vector< HalfEdgeRecord > edges_stack;
    auto sorted_vertices = edges_list.get_sorted_vertices( );
    edges_stack.push_back( edges_list.get_record(sorted_vertices[0]) );
    edges_stack.push_back( edges_list.get_record(sorted_vertices[1]));

    for ( int j = 2; j < sorted_vertices.size()-1; j++ )
    {
        auto vertex = sorted_vertices[ j ];
        auto edge = edges_list.get_record( vertex );
        auto prev = edges_stack.back( );

        auto left_side = edges_list.get_origin( edges_list.get_prev( edge ) ).y > vertex.y;

        if ( edges_list.get_prev( edge ) != edges_stack.back( )
             && edges_list.get_next( edge ) != edges_stack.back( ) )
        {
            for ( int i = 1; i < edges_stack.size( ); ++i )
            {
                auto stack_edge = edges_stack[ i ];
                auto there_back = edges_list.insert_diagonal( edge, stack_edge );
                if ( left_side )
                {
                    edges_stack[ i ] = there_back.second;
                }
                else
                {
                    edge = there_back.first;
                }
            }
            auto stack_edge = edges_stack.back( );
            edges_stack.clear( );
            edges_stack.push_back( stack_edge );
            edges_stack.push_back( edge );
        }
        else
        {
            auto get_next = [ left_side, &edges_list ]( HalfEdgeRecord r )
            {
                if ( left_side )
                {
                    return edges_list.get_prev( r );
                }
                else
                {
                    return edges_list.get_next( r );
                }
            };

            while ( get_interior_angle( edges_list, get_next( edge ) ) < M_PI
                    && edges_stack.size( ) > 1 )
            {
                auto there_back = edges_list.insert_diagonal( edge, get_next( get_next( edge ) ) );
                if ( !left_side )
                {
                    edge = there_back.first;
                }
                edges_stack.pop_back( );
                if ( left_side )
                {
                    edges_stack.pop_back( );
                    edges_stack.push_back( there_back.second );
                }
            }
            edges_stack.push_back( edge );
        }
    }
    for ( int i = 1; i < edges_stack.size( ) - 1; i++ )
    {
        edges_list.insert_diagonal( edges_list.get_record( sorted_vertices.back( ) ),
                                    edges_stack[ i ] );
    }
}
