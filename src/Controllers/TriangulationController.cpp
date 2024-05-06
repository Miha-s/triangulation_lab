#include "TriangulationController.hpp"

#include <Algorithms/ConvexHull.hpp>
#include <Algorithms/HalfEdgeList.hpp>
#include <Algorithms/MonotonePolygon.hpp>

#include <iostream>
void
TriangulationController::set_polygons_layer( std::shared_ptr< PolygonsLayer > polygons_layer )
{
    m_polygons_layer = polygons_layer;
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
        m_polygons_layer->clear( );
        return;
    }

    convert_polygons_to_different_coordinate_system( polygons );
//    polygons = { { { 865, -585 }, { 770, -600 }, { 839, -540 } },
//                 { { 71, -205 }, { 24, -140 }, { 70, -174 } },
//                 { { 233, -40 }, { 204, -63 }, { 207, 22 } } };
    std::vector< sf::Vector2f > points;
    for ( auto& polygon : polygons )
    {
        points.insert( points.begin( ), polygon.begin( ), polygon.end( ) );
    }

    auto convex_polygon = convex_hull( points );

    auto convex_hull_list = HalfEdgeList::build_from( convex_polygon );
    for ( const auto& el : polygons )
    {
        convex_hull_list.insert_hole( HalfEdgeList::build_from( el ) );
    }

//    auto the_polygons = convex_hull_list.get_polygons( );
//    convert_polygons_to_different_coordinate_system( the_polygons );
//    for ( const auto& el : the_polygons )
//    {
//        m_polygons_layer->add( el );
//    }

//    std::vector< sf::Vector2f > polygon{ { 2, -1 }, { 4, -2 }, { 6, 0 },
//                                         { 4, -4 }, { 2, -5 }, { 0, -4 } };

    calculate_monotone_polygon( convex_hull_list );
    auto the_polygons = convex_hull_list.get_separate_polygons( );

    std::vector< std::vector< sf::Vector2f > > res;
    for ( auto& polygon : the_polygons )
    {
        auto tmp = polygon.get_polygons( );
        res.insert( res.end( ), tmp.begin( ), tmp.end( ) );
    }

    convert_polygons_to_different_coordinate_system( res );

    m_polygons_layer->add(res[0]);
//    for(const auto& el : res) {
//        m_polygons_layer->add(el);
//    }
}

void
TriangulationController::clear( )
{
    m_polygons_layer->clear( );
}
