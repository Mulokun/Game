#ifndef _GAME_SELECT_ENTITY_STATE_
#define _GAME_SELECT_ENTITY_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/game_datas.hpp"


class Game_SelectEntityState : public State
{
    public :
        Game_SelectEntityState( GameDatas * gd );
        virtual ~Game_SelectEntityState( void );

        virtual void init( void );
        virtual void draw( sf::RenderTarget & window );
        virtual void update( void );
        virtual void handleEvent( sf::Event & e );

        void selectNextEntity( void );
        bool isEntityReady( void );

    private :

        GameDatas * m_gameDatas;
        Entity * m_next;
};

#endif // _GAME_SELECT_ENTITY_STATE_
