#include "OutlinePolygonsLayer.hpp"


void OutlinePolygonsLayer::draw_polygons(sf::RenderTarget &render_targer)
{
    lock_guard lock(m_mutex);
    for(auto& polygon : m_polygons) {
        for(auto& line : polygon) {
            render_targer.draw(line);
        }
    }
}

void OutlinePolygonsLayer::clear()
{
    lock_guard lock(m_mutex);
    m_polygons.clear();
}

void OutlinePolygonsLayer::add_polygon(std::vector<sf::Vector2f> points)
{
    std::vector<sfLine> polygon;

    for(int i = 0; i < points.size(); i++) {
        auto a = points[i];
        auto b = points[(i+1)%points.size()];
        polygon.push_back({a, b, sf::Color::Green, 2});
    }

    lock_guard lock(m_mutex);
    m_polygons.push_back(polygon);
}
