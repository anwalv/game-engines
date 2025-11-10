#include "Player.h"
#include <SFML/Window/Keyboard.hpp>
#include <algorithm>

Player::Player(const std::string& texturePath, const sf::Vector2f& position)
    : Entity(texturePath, position), m_moveSpeed(300.f)
{
    m_shape.setFillColor(sf::Color(255, 0, 0, 100));
    m_shape.setOutlineColor(sf::Color::Red);
}

void Player::update(float dt, const sf::RenderWindow& window)
{
    sf::Vector2f move(0.f, 0.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) move.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) move.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) move.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) move.x += 1.f;

    sf::Vector2f pos = m_sprite.getPosition() + (move * m_moveSpeed * dt);
    sf::Vector2u size = window.getSize();
    sf::FloatRect bounds = m_sprite.getGlobalBounds();

    pos.x = std::max(0.f, std::min(pos.x, (float)size.x - bounds.width));
    pos.y = std::max(0.f, std::min(pos.y, (float)size.y - bounds.height));

    m_sprite.setPosition(pos);
    m_shape.setPosition(pos.x + bounds.width / 2.f, pos.y + bounds.height);
}
