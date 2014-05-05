#include "entity.hpp"

#include <cmath>

#include "../../engine/animation.hpp"
#include "../../engine/time.hpp"
#include "../../engine/foo.hpp"

Entity::Entity( void ) : m_animation(NULL)
{
    m_speed = 3;
    m_position = sf::Vector2f( 60, 60 );
}

Entity::~Entity( void ) {}

void Entity::addAnimation( AnimationType type, std::string animationFile )
{
    m_animationSet[type] = new Animation(animationFile);
}

void Entity::setAnimation( AnimationType type )
{
    std::map< AnimationType, Animation * >::iterator it = m_animationSet.find(type);
    if( it != m_animationSet.end() ) {
        m_animation = it->second;
    } else {
        m_animation = NULL;
    }
}

sf::Vector2f Entity::getPosition( void ) const
{
    return m_position;
}

void Entity::move( sf::Vector2f direction )
{
    direction = normalize( direction );
    if( fabs(direction.x) != fabs(direction.y) ) {
        if( fabs(direction.x) > fabs(direction.y) ) {
            setAnimation( direction.x > 0 ? RIGHT : LEFT );
        } else {
            setAnimation( direction.y > 0 ? DOWN : UP );
        }
    } else if ( direction.x == 0 ) {
        setAnimation( STAY );
    }

    m_position.x += direction.x * m_speed * 32 * ( Time::deltaTime() / 1000 );
    m_position.y += direction.y * m_speed * 32 * ( Time::deltaTime() / 1000 );
}

void Entity::draw( sf::RenderTarget & target )
{
    if( m_animation ) {
        sf::Sprite * s = m_animation->update();
        s->setPosition( m_position );
        target.draw( *s );
    }
}
