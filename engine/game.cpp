#include "game.hpp"

#include "state.hpp"
#include "time.hpp"

Game::Game( void ) { init(); }
Game::~Game( void ) {}

void Game::init( void )
{
    m_render.create(sf::VideoMode(240, 160), "Game", sf::Style::Titlebar | sf::Style::Close);
    m_render.setFramerateLimit(60);
    m_render.setKeyRepeatEnabled(false);

    m_zoom = 3;

    m_render.setSize( sf::Vector2u( 240 * m_zoom, 160 * m_zoom ) );

    StateManager::kill();
}

void Game::addState( State * s )
{
    StateManager::addState(s);
}

void Game::start( void )
{
    while (m_render.isOpen() && !StateManager::isEmpty())
    {
        StateManager::setCurrent();

        handleEvent();
        update();
        draw();

        Time::update();
    }
}


void Game::update( void )
{
    StateManager::update();
}

void Game::draw( void )
{
    m_render.clear( sf::Color::White );
    StateManager::draw( m_render );
    m_render.display();
}

void Game::handleEvent( void )
{
    sf::Event event;

    while (m_render.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_render.close();
        }

        StateManager::handleEvent( event );
    }

}
