#include "UserPolygonsLayer.hpp"


void UserPolygonsLayer::draw(sf::RenderTarget &render_targer)
{
    lock_guard lock(m_mutex);
    for(auto& polygon : m_polygons) {
        for(auto& line : polygon) {
            render_targer.draw(line);
        }
    }
}

void UserPolygonsLayer::clear()
{
    lock_guard lock(m_mutex);
    m_polygons.clear();
}

void UserPolygonsLayer::add_polygon(std::vector<sf::Vector2f> points)
{
    std::vector<sfLine> polygon;

    for(int i = 0; i < points.size(); i++) {
        polygon.push_back({points[i], points[(i+1)%points.size()]});
    }

    lock_guard lock(m_mutex);
    m_polygons.push_back(polygon);
}
