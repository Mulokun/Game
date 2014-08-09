#ifndef _GAME_DATAS_
#define _GAME_DATAS_

#include "../game/character/character.hpp"
#include "../game/level/level.hpp"

class GameDatas
{

    public :

        GameDatas( void );
        ~GameDatas( void );

        void drawAll( sf::RenderTarget & window );
        void drawAllEntities( sf::RenderTarget & window );
        void drawPlayerEntities( sf::RenderTarget & window );
        void drawEnemyEntities( sf::RenderTarget & window );

        Level level;
        std::vector< Character * > playerEntities;
        std::vector< Character * > enemyEntities;

};

#endif // _GAME_DATAS_
