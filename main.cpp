/**
*** Un peu de texte à propos de ce projet :
*** Réalisé par : CHAMBONNET Kevin
***  - Avril 2014 -
**/

#include "engine/game.hpp"
#include "states/test_state.hpp"

int main(int argc, char ** argv)
{
    Game game;
    game.addState(new TestState());
    game.start();

    return 0;
}

/** TODO LIST :

    - Revoir tileset.hpp/cpp
    - add GUI
    - Commenter
    - Constructor improve (init variable, copie)
    - Message d'erreur

**/
