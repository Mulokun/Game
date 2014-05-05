#ifndef _STATE_MANAGER_
#define _STATE_MANAGER_

#include <SFML/Graphics.hpp>
#include <stack>

class State;

class StateManager
{

    public :
        static void kill( void );

        static void update( void );
        static void draw( sf::RenderTarget & window );
        static void handleEvent( sf::Event & e );

        static void addState( State * s );
        static void popState( void );
        static State * getCurrent( void );
        static void setCurrent( void );
        static bool isEmpty( void );

    private :
        StateManager( void );
        ~StateManager( void );

        static StateManager * singleton;

        static void deleteState( void );

        State * m_current;
        std::stack<State*> m_stateManaged;
        bool m_pop;

};

#endif // _STATE_MANAGER_
