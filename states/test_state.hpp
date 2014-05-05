#ifndef _TEST_STATE_
#define _TEST_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/entity/entity.hpp"


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

        Entity m_hero1;
        Entity m_hero2;
        bool m_bHero2_following;
};

#endif // _TEST_STATE_
