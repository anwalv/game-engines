#pragma once
#include "Entity.h"

class Player : public Entity
{
public:
    Player(const std::string& texturePath, const sf::Vector2f& position);
    void update(float dt, const sf::RenderWindow& window) override;

private:
    float m_moveSpeed;
};
