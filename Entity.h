#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Entity
{
public:
    Entity(const std::string& texturePath, const sf::Vector2f& position);
    virtual ~Entity() = default;
    virtual void update(float dt, const sf::RenderWindow& window) {}
    void draw(sf::RenderWindow& window, bool isDebugMode) const;

protected:
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    sf::RectangleShape m_shape;
};
