#include "PolygonBuilderController.hpp"

void
PolygonBuilderController::set_polygon_layer( PolygonsLayerPtr user_polygons_l )
{
    m_user_polygons_l = user_polygons_l;
}

void
PolygonBuilderController::set_polygon_addition_layer( ShapeAdditionLayerPtr polygon_addition_l )
{
    m_polygon_addition_l = polygon_addition_l;
}

void
PolygonBuilderController::set_number_of_edges( int n )
{
    m_number_of_edges = n;
}

void
PolygonBuilderController::clear( )
{
    m_user_polygons.clear( );
    m_current_points.clear( );
    m_polygon_addition_l->clear( );
    m_user_polygons_l->clear( );
}

void
PolygonBuilderController::add_point( sf::Vector2f point )
{
    m_current_points.push_back( point );
    m_polygon_addition_l->add_point( point );

    if ( m_current_points.size( ) < m_number_of_edges )
    {
        return;
    }

    m_user_polygons.push_back( m_current_points );
    m_user_polygons_l->add_polygon( m_current_points );
    m_current_points.clear( );
    m_polygon_addition_l->clear( );
}

void
PolygonBuilderController::add_polygon( std::vector< sf::Vector2f > polygon )
{
    m_user_polygons.push_back( polygon );
    m_user_polygons_l->add_polygon( polygon );
    m_current_points.clear( );
    m_polygon_addition_l->clear( );
}

PolygonBuilderController::Result
PolygonBuilderController::get_result( )
{
    auto user_polygons = std::move( m_user_polygons );
    m_polygon_addition_l->clear( );
    m_current_points.clear( );
    return user_polygons;
}
