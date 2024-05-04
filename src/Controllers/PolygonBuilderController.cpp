#include "PolygonBuilderController.hpp"

static constexpr int MAX_POINT_COUNT = 4;

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
PolygonBuilderController::add_point( sf::Vector2f point )
{
    m_current_points.push_back( point );
    m_polygon_addition_l->add_point( point );

    if ( m_current_points.size( ) < MAX_POINT_COUNT )
    {
        return;
    }

    m_user_polygons.push_back( m_current_points );
    m_user_polygons_l->add_polygon( m_current_points );
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
