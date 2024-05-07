#include "TriangulationController.hpp"

#include <Algorithms/ConvexHull.hpp>
#include <Algorithms/HalfEdgeList.hpp>
#include <Algorithms/MonotonePolygon.hpp>
#include <iostream>
std::vector< HalfEdgeList >&
TriangulationController::active_polygons( )
{
    if ( active_mode == Whole )
    {
        return m_whole_polygons;
    }
    else if ( active_mode == Monotone )
    {
        return m_monotone_polygons;
    }
    else if ( active_mode == MonotoneTriangulated )
    {
        return m_monotone_trinagulated_polygons;
    }
    else if ( active_mode == Trinagulated )
    {
        return m_triangulated_polygon;
    }

    return m_whole_polygons;
}

void
TriangulationController::set_outline_polygons_layer(
        std::shared_ptr< PolygonsLayer > polygons_layer )
{
    m_outline_polygons_layer = polygons_layer;
}

void
TriangulationController::set_whole_polygons_layer( std::shared_ptr< PolygonsLayer > polygons_layer )
{
    m_whole_polygons_layer = polygons_layer;
}

void
convert_polygons_to_different_coordinate_system(
        std::vector< std::vector< sf::Vector2f > >& polygons )
{
    for ( auto& polygon : polygons )
    {
        std::for_each( polygon.begin( ),
                       polygon.end( ),
                       []( sf::Vector2f& point ) { point.y *= -1; } );
    }
}

void
TriangulationController::triangulate( std::vector< std::vector< sf::Vector2f > > polygons )
{
    if ( polygons.empty( ) )
    {
        clear( );
        return;
    }

    m_whole_polygons.clear( );
    m_monotone_polygons.clear( );
    m_monotone_trinagulated_polygons.clear( );
    m_triangulated_polygon.clear( );

    convert_polygons_to_different_coordinate_system( polygons );

    std::vector< sf::Vector2f > points;
    for ( auto& polygon : polygons )
    {
        points.insert( points.begin( ), polygon.begin( ), polygon.end( ) );
    }
    auto convex_polygon = convex_hull( points );
    if ( polygons.size( ) == 1 )
    {
        convex_polygon = polygons[ 0 ];
    }
    auto convex_hull_list = HalfEdgeList::build_from( convex_polygon );
    if ( polygons.size( ) != 1 )
        for ( const auto& el : polygons )
        {
            convex_hull_list.insert_hole( HalfEdgeList::build_from( el ) );
        }

    calculate_monotone_polygon( convex_hull_list );
    m_monotone_polygons = convex_hull_list.get_separate_polygons( );
    auto processed_polygons = convex_hull_list.get_separate_polygons( );

    for ( auto& polygon : processed_polygons )
    {
        triangulate_monotone_polygon( polygon );
    }

    m_monotone_trinagulated_polygons = processed_polygons;

    HalfEdgeList whole_polygons;
    for ( const auto& triangulated_polygon : m_monotone_trinagulated_polygons )
    {
        whole_polygons.add_polygon( triangulated_polygon );
    }

    m_whole_polygons.push_back( whole_polygons );
    show_polygons( );
}

void
TriangulationController::show_next( )
{
    m_index++;
    show_polygons( );
}

void
TriangulationController::show_prev( )
{
    m_index--;
    if ( m_index < 0 )
    {
        m_index = active_polygons( ).size( ) - 1;
    }
    show_polygons( );
}

void
TriangulationController::switch_mode( )
{
    if ( active_mode == Whole )
    {
        active_mode = Monotone;
    }
    else if ( active_mode == Monotone )
    {
        active_mode = MonotoneTriangulated;
    }
    else if ( active_mode == MonotoneTriangulated )
    {
        active_mode = Trinagulated;
        m_triangulated_polygon =
                m_monotone_trinagulated_polygons[ m_index ].get_separate_polygons( );
    }
    else if ( active_mode == Trinagulated )
    {
        active_mode = Whole;
    }

    show_polygons( );
}

void
TriangulationController::show_polygons( )
{
    if ( active_polygons( ).size( ) == 0 )
    {
        return;
    }
    m_index %= active_polygons( ).size( );

    clear( );
    std::vector< std::vector< sf::Vector2f > > polygons =
            active_polygons( )[ m_index ].get_polygons( );
    convert_polygons_to_different_coordinate_system( polygons );

    if ( active_mode == Monotone )
    {
        auto triag_polygons = m_monotone_trinagulated_polygons[ m_index ].get_polygons( );
        convert_polygons_to_different_coordinate_system( triag_polygons );

        for ( auto& polygon : triag_polygons )
        {
            m_whole_polygons_layer->add( polygon );
        }
        for ( auto& polygon : polygons )
        {
            m_outline_polygons_layer->add( polygon );
        }
        return;
    }

    for ( auto& polygon : polygons )
    {
        m_whole_polygons_layer->add( polygon );
        m_outline_polygons_layer->add( polygon );
    }
}

void
TriangulationController::clear( )
{
    m_whole_polygons_layer->clear( );
    m_outline_polygons_layer->clear( );
}
