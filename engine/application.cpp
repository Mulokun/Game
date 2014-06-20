#include "application.hpp"

#include "state.hpp"
#include "time.hpp"

Application::Application( void ) { init(); }
Application::~Application( void ) {}

void Application::init( void )
{
    m_render.create(sf::VideoMode(800, 600), "Game", sf::Style::Titlebar | sf::Style::Close);
    m_render.setFramerateLimit(60);
    m_render.setKeyRepeatEnabled(false);

    m_zoom = 1;

    m_render.setSize( sf::Vector2u( 800 * m_zoom, 600 * m_zoom ) );

    StateManager::kill();
}

void Application::addState( State * s )
{
    StateManager::addState(s);
}

void Application::start( void )
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


void Application::update( void )
{
    StateManager::update();
}

void Application::draw( void )
{
    m_render.clear( sf::Color::Black );
    StateManager::draw( m_render );
    m_render.display();
}

void Application::handleEvent( void )
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