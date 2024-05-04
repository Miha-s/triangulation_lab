#include "UserPolygonsLayer.hpp"


void UserPolygonsLayer::draw(sf::RenderTarget &render_targer)
{
    lock_guard lock(m_mutex);
    for(auto& polygon : m_polygons) {
        render_targer.draw(polygon.data(), polygon.size(), sf::LinesStrip);
    }
}

void UserPolygonsLayer::clear()
{
    lock_guard lock(m_mutex);
    m_polygons.clear();
}

void UserPolygonsLayer::add_polygon(std::vector<sf::Vector2f> points)
{
    std::vector<sf::Vertex> polygon;
    points.push_back(points.front());

    for(auto& point : points) {
        polygon.push_back({point});
        polygon.back().color = sf::Color::Black;
    }

    lock_guard lock(m_mutex);
    m_polygons.push_back(polygon);
}
