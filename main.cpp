/**
*** Un peu de texte � propos de ce projet :
*** R�alis� par : CHAMBONNET Kevin
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

    - save/load level

    - add GUI
    - Commenter
    - Constructor improve (init variable, copie)
    - Message d'erreur

**/
