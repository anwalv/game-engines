#include "Game.h"

Game::Game()
    : m_window(sf::VideoMode(800, 600), "Slovo"),
    m_isPaused(false),
    m_isDebugMode(false)
{
    m_window.setFramerateLimit(60);
    loadLevel();
}

void Game::loadLevel()
{
    m_player = std::make_unique<Player>("sprites/poet.png", sf::Vector2f(100.f, 300.f));
    m_entities.emplace_back("sprites/bird.png", sf::Vector2f(300.f, 200.f));
    m_entities.emplace_back("sprites/shelf.png", sf::Vector2f(600.f, 100.f));
    m_entities.emplace_back("sprites/shelf.png", sf::Vector2f(200.f, 400.f));
}

void Game::run()
{
    while (m_window.isOpen())
    {
        float dt = m_deltaClock.restart().asSeconds();
        if (dt > MAX_DELTA_TIME) dt = MAX_DELTA_TIME;

        processEvents();
        if (!m_isPaused) update(dt);
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed) m_window.close();
        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) m_window.close();
        if (event.type == sf::Event::LostFocus) m_isPaused = true;
        if (event.type == sf::Event::GainedFocus) m_isPaused = false;
        if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::D) m_isDebugMode = !m_isDebugMode;
    }
}

void Game::update(float dt)
{
    m_player->update(dt, m_window);
}

void Game::render()
{
    m_window.clear(sf::Color(30, 30, 30));
    for (const auto& e : m_entities) e.draw(m_window, m_isDebugMode);
    m_player->draw(m_window, m_isDebugMode);
    m_window.display();
}
