#ifndef _TEST_STATE_
#define _TEST_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/game_datas.hpp"


const unsigned int ARROW_VERTICAL = 0;
const unsigned int ARROW_HORIZONTAL = 1;
const unsigned int ARROW_RIGHT_UP = 2;
const unsigned int ARROW_RIGHT_DOWN = 3;
const unsigned int ARROW_LEFT_UP = 4;
const unsigned int ARROW_LEFT_DOWN = 5;
const unsigned int ARROW_END_UP = 6;
const unsigned int ARROW_END_DOWN = 7;
const unsigned int ARROW_END_LEFT = 8;
const unsigned int ARROW_END_RIGHT = 9;
#define NB_ARROWS 10


class TestState : public State
{

    public :
        TestState( void );
        ~TestState( void );

        virtual void init( void );
        virtual void draw( sf::RenderTarget & window );
        virtual void update( void );
        virtual void handleEvent( sf::Event & e );

    private :

        sf::Vector2i m_cursorPosition;

        void setMobilityArea( Entity * e );
        std::vector< sf::Vector2i > m_mobilityArea;
        Animation m_areaAnimation;
        void initMobilityArrows( void );
        sf::Sprite * m_mobilityArrows[NB_ARROWS];
        std::vector< sf::Vector2i > m_mobilityPath;

        Entity * m_selected;
        GameDatas * m_gameDatas;

};

#endif // _TEST_STATE_
