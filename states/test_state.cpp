#include "test_state.hpp"

#include "SFML/Audio.hpp"

#include "../engine/foo.hpp"
#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"


TestState::TestState( void )
{
    init();
}

TestState::~TestState( void ) { }

void TestState::init( void )
{
    m_level.load("data/level/level_1.lvl");
}

void TestState::draw( sf::RenderTarget & window )
{
    m_level.draw( window );
    m_level.drawRoof( window );
}

void TestState::update( void )
{

}

void TestState::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
    {
        StateManager::popState();
    }
}
