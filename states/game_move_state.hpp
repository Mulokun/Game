#ifndef _GAME_MOVE_STATE_
#define _GAME_MOVE_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/game_datas.hpp"


class Game_MoveState : public State
{

    public :
        Game_MoveState( GameDatas * gameDatas, Entity * m_selected, std::vector< sf::Vector2i > path );
        ~Game_MoveState( void );

        void init( void );
        void draw( sf::RenderTarget & window );
        void update( void );
        void handleEvent( sf::Event & e );

    private :

        GameDatas * m_gameDatas;
        Entity * m_selected;
        std::vector< sf::Vector2i > m_path;

};

#endif // _GAME_MOVE_STATE_
