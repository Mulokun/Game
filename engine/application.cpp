#include "application.hpp"

#include "state.hpp"
#include "time.hpp"
#include "configuration.hpp"

Application::Application( void ) { init(); }
Application::~Application( void ) {}

void Application::init( void )
{
    Configuration::load();

    m_render.create(sf::VideoMode(800, 600), "Game", sf::Style::Titlebar | sf::Style::Close);
    m_render.setFramerateLimit(60);
    m_render.setKeyRepeatEnabled(false);
    m_focused = true;

    m_render.setSize( sf::Vector2u( 800 * Configuration::ZOOM, 600 * Configuration::ZOOM ) );

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
    if(m_focused) {
        StateManager::update();
    }
}

void Application::draw( void )
{
    if(m_focused) {
        m_render.clear( sf::Color::Black );
        StateManager::draw( m_render );
        m_render.display();
    }
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

        if (event.type == sf::Event::GainedFocus)
        {
            m_focused = true;
        }

        if (event.type == sf::Event::LostFocus)
        {
            m_focused = false;
        }

        if(m_focused) {
            StateManager::handleEvent( event );
        }
    }


}
