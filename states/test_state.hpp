#ifndef _TEST_STATE_
#define _TEST_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/entity/entity.hpp"
#include "../game/level/level.hpp"


class TestState : public State
{

    public :
        TestState( void );
        ~TestState( void );

        void init( void );
        void draw( sf::RenderTarget & window );
        void update( void );
        void handleEvent( sf::Event & e );

    private :

        Level m_level;
};

#endif // _TEST_STATE_
