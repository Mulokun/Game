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
    m_hero1.addAnimation(STAY, "data/animation/thief_stay.ani");
    m_hero1.addAnimation(UP, "data/animation/thief_up.ani");
    m_hero1.addAnimation(DOWN, "data/animation/thief_down.ani");
    m_hero1.addAnimation(LEFT, "data/animation/thief_left.ani");
    m_hero1.addAnimation(RIGHT, "data/animation/thief_right.ani");

    m_hero2.addAnimation(STAY, "data/animation/mage_stay.ani");
    m_hero2.addAnimation(UP, "data/animation/mage_up.ani");
    m_hero2.addAnimation(DOWN, "data/animation/mage_down.ani");
    m_hero2.addAnimation(LEFT, "data/animation/mage_left.ani");
    m_hero2.addAnimation(RIGHT, "data/animation/mage_right.ani");
    m_bHero2_following = false;
}

void TestState::draw( sf::RenderTarget & window )
{
    m_hero1.draw( window );
    m_hero2.draw( window );
}

void TestState::update( void )
{
    /// Follow the 1st Hero
    float d = distance( m_hero1.getPosition(), m_hero2.getPosition() );
    if( d > 36 || ( d > 32 && m_bHero2_following ) ) {
        m_hero2.move( direction( m_hero2.getPosition(), m_hero1.getPosition() ) );
        m_bHero2_following = true;
    } else {
        m_hero2.move( sf::Vector2f( 0, 0 ) );
        m_bHero2_following = false;
    }
    /// TODO : Made other SPRITE with 4 stay position (UP/DOWN/LEFT/RIGHT)

    sf::Vector2f direction( 0, 0 );

    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Z ) ) { direction.y = -1; }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) ) { direction.y = 1; }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) ) { direction.x = -1; }
    if( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) ) { direction.x = 1; }

    m_hero1.move( direction );
}

void TestState::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
    {
        StateManager::popState();
    }
}
