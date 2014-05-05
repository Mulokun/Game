#include "time.hpp"

#include <iostream>
#include "SFML/Graphics.hpp"

Time * Time::m_singleton = NULL;
int Time::s_IPS = 60;

void Time::kill( void )
{
    if(Time::m_singleton) {
        delete Time::m_singleton;
        Time::m_singleton = NULL;
    }
}

void Time::wait( sf::Time timeWait )
{
    sf::sleep(timeWait);
}

void Time::update( void )
{
    if(!Time::m_singleton) { Time::m_singleton = new Time(); }

    Time::m_singleton->m_lastFrame = Time::m_singleton->m_elapsed.getElapsedTime() - Time::m_singleton->m_lastTime;
    Time::m_singleton->m_lastTime = Time::m_singleton->m_elapsed.getElapsedTime();
}

Time::Time( void )
{
    m_lastTime = sf::Time::Zero;
    m_lastFrame = sf::Time::Zero;
}

Time::~Time( void )
{

}


sf::Time Time::elapsed( void )
{
    if(!Time::m_singleton) { Time::m_singleton = new Time(); }

    return Time::m_singleton->m_elapsed.getElapsedTime();
}

float Time::IPS( void )
{
    if(!Time::m_singleton) { Time::m_singleton = new Time(); }

    return Time::m_singleton->m_lastFrame.asSeconds() * s_IPS;
}

float Time::deltaTime( void )
{
    if(!Time::m_singleton) { Time::m_singleton = new Time(); }

    return Time::m_singleton->m_lastFrame.asMilliseconds();
}

void Time::setIPS( int ips )
{
    s_IPS = ips;
}
