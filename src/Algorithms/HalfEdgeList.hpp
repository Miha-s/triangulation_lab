#ifndef HALFEDGELIST_HPP
#define HALFEDGELIST_HPP

#include <SFML/System/Vector2.hpp>
#include <set>
#include <vector>
#include <utility>

using HalfEdgeRecord = int;

bool
operator>( const sf::Vector2f& left, const sf::Vector2f& right );

struct HalfEdgeList
{
private:
    struct HalfEdgeRecordInternal
    {
        HalfEdgeRecordInternal( HalfEdgeRecord id,
                                sf::Vector2f origin,
                                HalfEdgeRecord prev,
                                HalfEdgeRecord next );

        HalfEdgeRecord id;
        sf::Vector2f origin;
        HalfEdgeRecord prev;
        HalfEdgeRecord next;
    };

    std::vector< HalfEdgeRecordInternal > records;
    mutable std::vector< sf::Vector2f > vertices;

    static HalfEdgeRecord generate_id( );
    HalfEdgeRecordInternal& get_record( HalfEdgeRecord id );
    const HalfEdgeRecordInternal& get_record( HalfEdgeRecord id ) const;


public:
    static const HalfEdgeRecord INVALID_ID;

    static HalfEdgeList build_from( const std::vector< sf::Vector2f >& polygon );
    void insert_hole( const HalfEdgeList& hole );
    std::vector< std::vector< sf::Vector2f > > get_polygons( ) const;

    const std::vector< sf::Vector2f >& get_sorted_vertices( ) const;
    HalfEdgeRecord get_next( HalfEdgeRecord id ) const;
    HalfEdgeRecord get_prev( HalfEdgeRecord id ) const;
    sf::Vector2f get_origin( HalfEdgeRecord id ) const;
    std::pair< HalfEdgeRecord, HalfEdgeRecord > insert_diagonal( HalfEdgeRecord from,
                                                                 HalfEdgeRecord to );

    std::vector< HalfEdgeRecord > get_records( const sf::Vector2f& origin ) const;
    std::vector< HalfEdgeList > get_separate_polygons( ) const;
    void add_polygon( const HalfEdgeList& polygon );
    HalfEdgeRecord get_record( const sf::Vector2f& origin ) const;

    void set_next( HalfEdgeRecord id, HalfEdgeRecord next );
    void set_prev( HalfEdgeRecord id, HalfEdgeRecord prev );
    void remove_record(HalfEdgeRecord id);
    HalfEdgeRecord add_record( const sf::Vector2f& origin, HalfEdgeRecord prev );
};

#endif  // HALFEDGELIST_HPP
