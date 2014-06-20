#ifndef _GAME_DATAS_
#define _GAME_DATAS_

#include "../game/entity/entity.hpp"
#include "../game/level/level.hpp"

class GameDatas
{

    public :

        GameDatas( void );
        ~GameDatas( void );


        Level level;
        std::vector< Entity * > entities;

};

#endif // _GAME_DATAS_
