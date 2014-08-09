#ifndef _GAME_MOVE_ANI_STATE_
#define _GAME_MOVE_ANI_STATE_


#include <SFML/Audio.hpp>


#include "../engine/state.hpp"
#include "../engine/animation.hpp"

#include "../game/game_datas.hpp"


class Game_MoveAniState : public State
{

    public :
        Game_MoveAniState( GameDatas * gd, Character * m_selected, std::vector< sf::Vector2i > path );
        virtual ~Game_MoveAniState( void );

        virtual void init( void );
        virtual void draw( sf::RenderTarget & window );
        virtual void update( void );
        virtual void handleEvent( sf::Event & e );
        virtual void treatEvent( GameEvent e );

    private :

        GameDatas * m_gameDatas;
        Character * m_selected;
        std::vector< sf::Vector2i > m_path;

        unsigned int m_it;
        sf::Vector2f m_currentPosition;
        const float m_speed;

};

#endif // _GAME_MOVE_ANI_STATE_
