#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>
#include "Player.h"
#include "Entity.h"

class Game
{
public:
    Game();
    void run();

private:
    void loadLevel();
    void processEvents();
    void update(float dt);
    void render();

private:
    sf::RenderWindow m_window;
    std::unique_ptr<Player> m_player;
    std::vector<Entity> m_entities;
    bool m_isPaused;
    bool m_isDebugMode;
    sf::Clock m_deltaClock;
    const float MAX_DELTA_TIME = 0.05f;
};
