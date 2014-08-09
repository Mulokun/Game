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
    srand( time(NULL) );

    // --------------------------

    GameDatas * gameDatas = new GameDatas;

    gameDatas->level.load("data/level/level_1.lvl");

    Character * e = NULL;

    e = new Character();

    e->addAnimation(ANI_STAY, "data/animation/king_stay.ani");
    e->addAnimation(ANI_UP, "data/animation/king_up.ani");
    e->addAnimation(ANI_DOWN, "data/animation/king_down.ani");
    e->addAnimation(ANI_LEFT, "data/animation/king_left.ani");
    e->addAnimation(ANI_RIGHT, "data/animation/king_right.ani");
    e->setPosition(8, 3);
    e->setTimeElapsed( 53 );
    gameDatas->enemyEntities.push_back(e);

    e = new Character();
    e->addAnimation(ANI_STAY, "data/animation/thief_stay.ani");
    e->addAnimation(ANI_UP, "data/animation/thief_up.ani");
    e->addAnimation(ANI_DOWN, "data/animation/thief_down.ani");
    e->addAnimation(ANI_LEFT, "data/animation/thief_left.ani");
    e->addAnimation(ANI_RIGHT, "data/animation/thief_right.ani");
    e->setPosition(8, 8);
    e->setTimeElapsed( 5 );
    gameDatas->playerEntities.push_back(e);

    e = new Character();
    e->addAnimation(ANI_STAY, "data/animation/thief_stay.ani");
    e->addAnimation(ANI_UP, "data/animation/thief_up.ani");
    e->addAnimation(ANI_DOWN, "data/animation/thief_down.ani");
    e->addAnimation(ANI_LEFT, "data/animation/thief_left.ani");
    e->addAnimation(ANI_RIGHT, "data/animation/thief_right.ani");
    e->setPosition(4, 8);
    gameDatas->playerEntities.push_back(e);

    /*
    std::cout << "HP : " << e->getCurrentHP() << std::endl;
    std::cout << "------" << std::endl;
    std::cout << "Stat ---- ( " << Character::statSymbol(e->getStatLevel()) << " ) : " << std::endl;
    std::cout << "Height : " << Character::statSymbol(e->getStatHeight()) << std::endl;
    std::cout << "Weigth : " << Character::statSymbol(e->getStatWeight()) << std::endl;
    std::cout << "Muscle : " << Character::statSymbol(e->getStatMuscle()) << std::endl;
    std::cout << "Technic : " << Character::statSymbol(e->getStatTechnic()) << std::endl;
    std::cout << "Mind : " << Character::statSymbol(e->getStatMind()) << std::endl;
    std::cout << "------" << std::endl;
    std::cout << "Base Damage : " << e->getBaseDamage() << std::endl;
    std::cout << "Chance Hit : " << e->getHitChance() << std::endl;
    std::cout << "Chance Avoid : " << e->getAvoidChance() << std::endl;
    std::cout << std::endl;
    */

    // --------------------------

    Application app;
    app.addState(new Game_SelectEntityState(gameDatas));
    app.start();

    return 0;
}

