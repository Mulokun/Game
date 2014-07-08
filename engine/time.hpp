#ifndef _TIME_
#define _TIME_


#include "SFML/Graphics.hpp"


class Time
{

    public :
        static void kill( void );

        static void wait( sf::Time time );

        static void update( void );
        static sf::Time elapsed( void );
        static float IPS( void );
        static float currentIPS( void );
        static float frameTime( void );
        static float deltaTime( void );
        static void setIPS( int ips );

    private :
        Time( void );
        ~Time( void );

        static Time * m_singleton;

        sf::Clock m_elapsed;
        sf::Time m_lastTime;
        sf::Time m_lastFrame;
        static int s_IPS;
};

#endif // _TIME_
