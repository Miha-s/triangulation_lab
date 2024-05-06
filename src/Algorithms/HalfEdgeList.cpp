#include "HalfEdgeList.hpp"

#include <algorithm>

const HalfEdgeRecord HalfEdgeList::INVALID_ID = -1;

bool
lexical_vector_more( const sf::Vector2f& left, const sf::Vector2f& right )
{
    return left.y > right.y || ( left.y == right.y && left.x < right.x );
}

bool
operator>( const sf::Vector2f& left, const sf::Vector2f& right )
{
    return lexical_vector_more( left, right );
}

HalfEdgeRecord
HalfEdgeList::generate_id( )
{
    static HalfEdgeRecord last_id = 0;
    return ++last_id;
}

#include <iostream>

HalfEdgeList::HalfEdgeRecordInternal&
HalfEdgeList::get_record( HalfEdgeRecord id )
{
    auto it = std::find_if( records.begin( ),
                            records.end( ),
                            [ id ]( const HalfEdgeRecordInternal& record )
                            { return record.id == id; } );
    if ( it != records.end( ) )
    {
        return *it;
    }
    std::cout << "INVALID ID" << std::endl;
    static HalfEdgeRecordInternal invalid_record{ -1, { }, 0, 0 };
    return invalid_record;
}

HalfEdgeList
HalfEdgeList::build_from( const std::vector< sf::Vector2f >& polygon )
{
    HalfEdgeList list;
    HalfEdgeRecord prev_id = INVALID_ID;
    auto back = polygon.size( ) - 1;
    prev_id = list.add_record( polygon[ back ], prev_id );
    auto first = prev_id;

    for ( int i = back - 1; i >= 0; i-- )
    {
        prev_id = list.add_record( polygon[ i ], prev_id );
    }

    list.set_next( prev_id, first );

    return list;
}

void
HalfEdgeList::insert_hole( const HalfEdgeList& hole )
{
    const auto& sorted_vertices = get_sorted_vertices( );
    const auto& hole_vertices = hole.get_sorted_vertices( );

    for ( int j = 0; j < hole_vertices.size( ); j++ )
    {
        if ( get_record( hole_vertices[ j ] ) != INVALID_ID )
        {
            auto this_edge = get_record( hole_vertices[ j ] );
            auto hole_edge = hole.get_record( hole_vertices[ j ] );

            while ( hole_edge != INVALID_ID )
            {
                this_edge = get_prev( this_edge );
                hole_edge = hole.get_record( get_origin( this_edge ) );
            }

            auto starting_edge = this_edge;
            auto hole_first = hole.get_record( get_origin( get_next( this_edge ) ) );

            this_edge = get_next( starting_edge );
            this_edge = get_next( this_edge );
            while ( hole.get_record( get_origin( this_edge ) ) != INVALID_ID )
            {
                remove_record( get_prev( this_edge ) );
                this_edge = get_next( this_edge );
            }
            auto last_edge = get_prev( this_edge );

            hole_edge = hole_first;
            this_edge = starting_edge;
            do
            {
                this_edge = add_record( hole.get_origin( hole_edge ), this_edge );

                hole_edge = hole.get_prev( hole_edge );
            } while ( get_origin( last_edge ) != hole.get_origin( hole_edge ) );

            set_next( this_edge, last_edge );

            return;
        }
    }

    // if not intersection was found, then just insert hole
    auto prev_edge = INVALID_ID;
    auto hole_edge = hole.get_record( hole_vertices[ 0 ] );
    auto first = add_record( hole.get_origin( hole_edge ), prev_edge );
    prev_edge = first;
    hole_edge = hole.get_prev( hole_edge );

    for ( int i = 1; i < hole_vertices.size( ); i++ )
    {
        prev_edge = add_record( hole.get_origin( hole_edge ), prev_edge );
        hole_edge = hole.get_prev( hole_edge );
    }

    set_prev( first, prev_edge );
    set_next( prev_edge, first );
}

std::vector< std::vector< sf::Vector2f > >
HalfEdgeList::get_polygons( ) const
{
    std::vector< std::vector< sf::Vector2f > > res;
    auto list_copy = records;
    auto find_next = [ &list_copy ]( HalfEdgeRecord rec )
    {
        return std::find_if( list_copy.begin( ),
                             list_copy.end( ),
                             [ rec ]( const HalfEdgeRecordInternal& record )
                             { return record.id == rec; } );
    };

    while ( !list_copy.empty( ) )
    {
        std::vector< sf::Vector2f > current_polygon;
        auto element = list_copy.begin( );
        while ( element != list_copy.end( ) )
        {
            current_polygon.push_back( element->origin );
            auto tmp = element->next;
            list_copy.erase( element );
            element = find_next( tmp );
        }

        res.push_back( current_polygon );
    }

    return res;
}

const std::vector< sf::Vector2f >&
HalfEdgeList::get_sorted_vertices( ) const
{
    std::sort( vertices.begin( ), vertices.end( ), lexical_vector_more );

    return vertices;
}

HalfEdgeRecord
HalfEdgeList::get_next( HalfEdgeRecord id ) const
{
    return get_record( id ).next;
}

HalfEdgeRecord
HalfEdgeList::get_prev( HalfEdgeRecord id ) const
{
    return get_record( id ).prev;
}

sf::Vector2f
HalfEdgeList::get_origin( HalfEdgeRecord id ) const
{
    return get_record( id ).origin;
}

std::pair< HalfEdgeRecord, HalfEdgeRecord >
HalfEdgeList::insert_diagonal( HalfEdgeRecord id_from, HalfEdgeRecord id_to )
{
    auto id_prev_from = get_prev( id_from );
    auto id_prev_to = get_prev( id_to );

    auto new1 = add_record( get_origin( id_from ), id_prev_from );
    set_next( new1, id_to );

    auto new2 = add_record( get_origin( id_to ), id_prev_to );
    set_next( new2, id_from );

    return { new1, new2 };
}

std::vector<HalfEdgeRecord> HalfEdgeList::get_records(const sf::Vector2f &origin) const
{
    std::vector<HalfEdgeRecord> res;
    for ( const auto& record : records )
    {
        if ( record.origin == origin )
        {
            res.push_back( record.id);
        }
    }

    return res;
}

std::vector< HalfEdgeList >
HalfEdgeList::get_separate_polygons( ) const
{
    std::vector< HalfEdgeList > res;
    auto list_copy = records;
    auto find_next = [ &list_copy ]( HalfEdgeRecord rec )
    {
        return std::find_if( list_copy.begin( ),
                             list_copy.end( ),
                             [ rec ]( const HalfEdgeRecordInternal& record )
                             { return record.id == rec; } );
    };

    while ( !list_copy.empty( ) )
    {
        HalfEdgeList current_polygon;
        auto element = list_copy.begin( );
        auto prev = INVALID_ID;
        auto start = current_polygon.add_record( element->origin, prev );
        prev = start;
        auto tmp = element->next;
        list_copy.erase(element);
        element = find_next( tmp );
        while ( element != list_copy.end( ) )
        {
            prev = current_polygon.add_record( element->origin, prev );
            auto tmp = element->next;
            list_copy.erase( element );
            element = find_next( tmp );
        }

        current_polygon.set_next( prev, start );
        res.push_back( current_polygon );
    }

    return res;
}

HalfEdgeRecord
HalfEdgeList::get_record( const sf::Vector2f& origin ) const
{
    for ( const auto& record : records )
    {
        if ( record.origin == origin )
        {
            return record.id;
        }
    }

    return INVALID_ID;
}

const HalfEdgeList::HalfEdgeRecordInternal&
HalfEdgeList::get_record( HalfEdgeRecord id ) const
{
    return const_cast< HalfEdgeList& >( *this ).get_record( id );
}

void
HalfEdgeList::set_next( HalfEdgeRecord id, HalfEdgeRecord next )
{
    get_record( id ).next = next;
    get_record( next ).prev = id;
}

void
HalfEdgeList::set_prev( HalfEdgeRecord id, HalfEdgeRecord prev )
{
    get_record( id ).prev = prev;
    get_record( prev ).next = id;
}

#include <iostream>
void
HalfEdgeList::remove_record( HalfEdgeRecord id )
{
    get_record( get_prev( id ) ).next = INVALID_ID;
    get_record( get_next( id ) ).prev = INVALID_ID;

    auto it = std::find( vertices.begin( ), vertices.end( ), get_origin( id ) );
    if(it == vertices.end()) {
        std::cout << "END2" << std::endl;
    }
    vertices.erase( it );
    auto it2 = std::find_if( records.begin( ),
                             records.end( ),
                             [ id ]( const HalfEdgeRecordInternal& record )
                             { return record.id == id; } );
    if ( it2 == records.end( ) )
    {
        std::cout << "END3" << std::endl;
    }
    records.erase( it2 );
}

HalfEdgeRecord
HalfEdgeList::add_record( const sf::Vector2f& origin, HalfEdgeRecord prev )
{
    records.emplace_back( generate_id( ), origin, prev, INVALID_ID );
    if ( prev != INVALID_ID )
        get_record( prev ).next = records.back( ).id;

    auto it = std::find( vertices.begin( ), vertices.end( ), origin );
    if ( it == vertices.end( ) )
        vertices.push_back( origin );

    return records.back( ).id;
}

HalfEdgeList::HalfEdgeRecordInternal::HalfEdgeRecordInternal( HalfEdgeRecord id,
                                                              sf::Vector2f origin,
                                                              HalfEdgeRecord prev,
                                                              HalfEdgeRecord next )
    : id{ id }
    , origin{ origin }
    , prev{ prev }
    , next{ next }
{
}
