#ifndef _STATE_
#define _STATE_


#include <SFML/Graphics.hpp>
#include <list>

#include "game_event.hpp"


class StateManager;


class State
{

    public :
        State( void ) { };
        virtual ~State( void ) { };

        virtual void init( void ) = 0;
        virtual void draw( sf::RenderTarget & window ) = 0;
        virtual void update( void ) = 0;
        virtual void handleEvent( sf::Event & e ) = 0;
        virtual void treatEvent( GameEvent e ) = 0;

        /// Event du jeu
        void addEvent( GameEvent e ) {
            m_listEvent.push_back( e );
        }

        void processEvent( void ) {
            for(std::list< GameEvent >::iterator i = m_listEvent.begin(); i != m_listEvent.end(); i++) {
                treatEvent(*i);
            }
            m_listEvent.clear();
        }

    private :

        std::list< GameEvent > m_listEvent;
};

#endif // _STATE_
