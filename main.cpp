/**
*** Un peu de texte à propos de ce projet :
*** Réalisé par : CHAMBONNET Kevin
***  - Avril 2014 -
***
*** Derniere Modification : 20 Juin 2014
**/

#include "engine/application.hpp"
#include "states/game_select_entity_state.hpp"

int main(int argc, char ** argv)
{
    // --------------------------

    GameDatas * gameDatas = new GameDatas;

    gameDatas->level.load("data/level/level_1.lvl");

    Entity * e = new Entity();
    e->addAnimation(ANI_STAY, "data/animation/thief_stay.ani");
    e->addAnimation(ANI_UP, "data/animation/thief_up.ani");
    e->addAnimation(ANI_DOWN, "data/animation/thief_down.ani");
    e->addAnimation(ANI_LEFT, "data/animation/thief_left.ani");
    e->addAnimation(ANI_RIGHT, "data/animation/thief_right.ani");
    e->setPosition(8, 8);
    e->setTimeElapsed( 5 );
    gameDatas->entities.push_back(e);
    e = new Entity();
    e->addAnimation(ANI_STAY, "data/animation/thief_stay.ani");
    e->addAnimation(ANI_UP, "data/animation/thief_up.ani");
    e->addAnimation(ANI_DOWN, "data/animation/thief_down.ani");
    e->addAnimation(ANI_LEFT, "data/animation/thief_left.ani");
    e->addAnimation(ANI_RIGHT, "data/animation/thief_right.ani");
    e->setPosition(4, 8);
    gameDatas->entities.push_back(e);

    // --------------------------

    Application app;
    app.addState(new Game_SelectEntityState(gameDatas));
    app.start();

    return 0;
}

/** TODO LIST :

    - save a tester

    - entity.hpp : change enum -> const unsigned int

    - add GUI
    - Commenter
    - Constructor improve (init variable, copie)
    - Message d'erreur

**/
