#ifndef _GAME_
#define _GAME_


#include <SFML/Graphics.hpp>


#include "state_manager.hpp"


class Application
{

    public :
        Application( void );
        ~Application( void );

        void init( void );
        void addState( State * s );
        void start( void );

    private :

        bool m_focused;
        sf::RenderWindow m_render;

        /// Private Methods :
        void update( void );
        void draw( void );
        void handleEvent( void );
};


#endif // _GAME_

