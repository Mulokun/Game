#ifndef _GAME_
#define _GAME_


#include <SFML/Graphics.hpp>


#include "state_manager.hpp"


class Game
{

    public :
        Game( void );
        ~Game( void );

        void init( void );
        void addState( State * s );
        void start( void );

    private :

        int m_zoom;
        sf::RenderWindow m_render;

        /// Private Methods :
        void update( void );
        void draw( void );
        void handleEvent( void );
};


#endif // _GAME_

