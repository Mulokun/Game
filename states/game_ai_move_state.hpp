#ifndef _GAME_AI_MOVE_STATE_
#define _GAME_AI_MOVE_STATE_


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/game_datas.hpp"


class Game_AIMoveState : public State
{
    public :
        Game_AIMoveState( GameDatas * gd, Character * selected );
        virtual ~Game_AIMoveState( void );

        virtual void init( void );
        virtual void draw( sf::RenderTarget & window );
        virtual void update( void );
        virtual void handleEvent( sf::Event & e );
        virtual void treatEvent( GameEvent e );

    private :

        GameDatas * m_gameDatas;
        Character * m_selected;
};

#endif // _GAME_AI_MOVE_STATE_
