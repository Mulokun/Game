#ifndef _GAME_PLAYER_ACTION_STATE_
#define _GAME_PLAYER_ACTION_STATE_


#include "../engine/state.hpp"
#include "../engine/ui/ui.hpp"

#include "../game/game_datas.hpp"


class Game_PlayerActionState : public State
{
    public :
        Game_PlayerActionState( GameDatas * gd, Character * selected );
        virtual ~Game_PlayerActionState( void );

        virtual void init( void );
        virtual void draw( sf::RenderTarget & window );
        virtual void update( void );
        virtual void handleEvent( sf::Event & e );
        virtual void treatEvent( GameEvent e );

    private :

        GameDatas * m_gameDatas;
        Character * m_selected;

        UI * m_ui;
        Widget * m_actionSelected;
        sf::Time m_cursorNextAction;

};

#endif // _GAME_PLAYER_ACTION_STATE_
