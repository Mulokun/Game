#include "widget.hpp"

#include <iostream>
#include <fstream>

#include "../foo.hpp"

#include "../data_manager.hpp"
#include "../animation.hpp"

Widget::Widget( void )
{
    m_name = "";

    m_animation = NULL;
    m_background = NULL;
    m_text = NULL;

    setPositionAbsolute(0, 0);

    m_show = true;
}

Widget::~Widget( void )
{
    if(m_background) { delete m_background; }
    if(m_animation) { delete m_animation; }
    if(m_text) { delete m_text; }
}

void Widget::setName( std::string name )
{
    m_name = name;
}

std::string Widget::getName( void ) const
{
    return m_name;
}

void Widget::setBackground( sf::Sprite * s )
{
    m_background = s;
}

void Widget::setAnimation( Animation * a )
{
    if(m_animation) { delete m_animation; }
    m_animation = a;
    update();
}

Animation * Widget::getAnimation( void ) const
{
    return m_animation;
}

void Widget::setText( sf::Text * t )
{
    if(m_text) { delete m_text; }
    m_text = t;
    update();
}

sf::Text * Widget::getText( void ) const
{
    return m_text;
}

void Widget::setPositionRelative( RelativePosition p )
{
    m_position = getAbsolutePosition( m_bounds, m_parentBounds, p );
    update();
}

void Widget::setPositionAbsolute( float x, float y )
{
    setPositionAbsolute( sf::Vector2f(x, y) );
}

void Widget::setPositionAbsolute( sf::Vector2f p )
{
    m_position.x = p.x + m_parentBounds.left;
    m_position.y = p.y + m_parentBounds.top;
    update();
}

void Widget::move( float x, float y )
{
    move( sf::Vector2f(x, y) );
}

void Widget::move( sf::Vector2f p )
{
    m_position.x += p.x;
    m_position.y += p.y;
    update();
}

sf::Vector2f Widget::getPosition( void ) const
{
    return m_position;
}

sf::FloatRect Widget::getBounds( void )
{
    return m_bounds;
}


void Widget::update( void )
{
    sf::FloatRect r(0, 0, 0, 0);

    if(m_background)
    {
        r.height = std::max(m_background->getLocalBounds().height, r.height);
        r.width = std::max(m_background->getLocalBounds().width, r.width);
        r.top = std::max(m_background->getLocalBounds().top, r.top);
        r.left = std::max(m_background->getLocalBounds().left, r.left);
    }

    if(m_text)
    {
        r.height = std::max(m_text->getLocalBounds().height, r.height);
        r.width = std::max(m_text->getLocalBounds().width, r.width);
        r.top = std::max(m_text->getLocalBounds().top, r.top);
        r.left = std::max(m_text->getLocalBounds().left, r.left);
    }

    if(m_animation)
    {
        r.height = std::max(m_animation->update()->getLocalBounds().height, r.height);
        r.width = std::max(m_animation->update()->getLocalBounds().width, r.width);
        r.top = std::max(m_animation->update()->getLocalBounds().top, r.top);
        r.left = std::max(m_animation->update()->getLocalBounds().left, r.left);
    }

    sf::Vector2f sf( r.width, r.height );

    m_bounds.width = r.width;
    m_bounds.height = r.height;
    m_bounds.left = m_position.x;
    m_bounds.top = m_position.y;

    if(m_animation)
    {
        int x = getAbsolutePosition( r, m_bounds, CENTER).x;
        int y = getAbsolutePosition( r, m_bounds, MIDDLE).y;
        sf::Vector2f p(x, y);

        m_animation->m_position = p;
    }

    if(m_text)
    {
        int x = getAbsolutePosition( r, m_bounds, CENTER).x;
        int y = getAbsolutePosition( r, m_bounds, MIDDLE).y;
        sf::Vector2f p(x, y);

        m_text->setPosition( p );
    }

    if(m_background)
    {
        int x = getAbsolutePosition( r, m_bounds, CENTER).x;
        int y = getAbsolutePosition( r, m_bounds, MIDDLE).y;
        sf::Vector2f p(x, y);

        m_backgroundPosition = p;
    }
}

void Widget::setShow( bool b )
{
    m_show = b;
}

bool Widget::isShow( void ) const
{
    return m_show;
}

void Widget::setEvent( GameEvent e )
{
    m_event = e;
}

GameEvent Widget::getEvent() const
{
    return m_event;
}

bool Widget::isOver( const sf::Vector2i & p ) const
{
    return isInner( m_bounds, p );
}

bool Widget::isSetelected() const
{
    return m_selected;
}

void Widget::select( bool b )
{
    m_selected = b;
}

GameEvent Widget::active() const
{
    return m_event;
}

void Widget::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    if(m_show)
    {
        if(m_background) {
            m_background->setPosition(m_backgroundPosition);
            target.draw(*m_background);
        }
        if(m_animation) {
            m_animation->draw(target);
        }
        if(m_text) {
            target.draw(*m_text);
        }
    }
}


