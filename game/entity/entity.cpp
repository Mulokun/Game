#include "entity.hpp"

#include <cmath>

#include "../../engine/animation.hpp"
#include "../../engine/time.hpp"
#include "../../engine/foo.hpp"

Entity::Entity( void )
{
    m_position = sf::Vector2i( 0, 0 );
    m_mobility = 5;
}

Entity::~Entity( void ) {}

void Entity::addAnimation( AnimationType type, std::string animationFile )
{
    m_animationSet[type] = new Animation(animationFile);
}

Animation * Entity::getAnimation( AnimationType type )
{
    std::map< AnimationType, Animation * >::iterator it = m_animationSet.find(type);
    if( it != m_animationSet.end() ) {
        return it->second;
    } else {
        return NULL;
    }
}


sf::Vector2i Entity::getPosition( void ) const
{
    return m_position;
}

void Entity::setPosition( sf::Vector2i position )
{
    m_position = position;
}

void Entity::setPosition( int x, int y )
{
    setPosition( sf::Vector2i(x, y) );
}

unsigned int Entity::getMobility( void ) const
{
    return m_mobility;
}


void Entity::setTimeElapsed( unsigned int time )
{
    m_timeElapsed += time;

    while( m_timeElapsed > Entity::WaitingTime ) {
        m_timeElapsed -= Entity::WaitingTime;
        if(m_AP < Entity::MaxAP) {
            m_AP++;
        }
    }
}

unsigned int Entity::getTimeRemaining( void ) const
{
    return Entity::WaitingTime - m_timeElapsed;
}

unsigned int Entity::getAP( void ) const
{
    return m_AP;
}
