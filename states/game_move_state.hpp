#ifndef _GAME_MOVE_STATE_
#define _GAME_MOVE_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"
#include "../engine/configuration.hpp"

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

const sf::Time CURSOR_TIME_AFTER_PRESS = sf::milliseconds(400);
const sf::Time CURSOR_TIME_CONTINUOUS = sf::milliseconds(50);


class Game_MoveState : public State
{

    public :
        Game_MoveState( GameDatas * gd, Entity * selected );
        virtual ~Game_MoveState( void );

        virtual void init( void );
        virtual void draw( sf::RenderTarget & window );
        virtual void update( void );
        virtual void handleEvent( sf::Event & e );

    private :

        GameDatas * m_gameDatas;
        Entity * m_selected;
        sf::Vector2i m_oldPosition;

        sf::Vector2i m_cursorPosition;
        sf::Time m_cursorNextAction;
        void setCursorMove( sf::Vector2i cursorCusor );

        void setMobilityArea( Entity * e );
        std::vector< sf::Vector2i > m_mobilityArea;
        Animation m_mobilityAreaAnimation;
        void initMobilityArrows( void );
        sf::Sprite * m_mobilityArrows[NB_ARROWS];
        std::vector< sf::Vector2i > m_mobilityPath;


};

#endif // _GAME_MOVE_STATE_
