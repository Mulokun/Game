/**
*** Un peu de texte à propos de ce projet :
*** Réalisé par : CHAMBONNET Kevin
***  - Avril 2014 -
***
*** Derniere Modification : 20 Juin 2014
**/

#include "engine/application.hpp"
#include "states/test_state.hpp"

int main(int argc, char ** argv)
{
    Application app;
    app.addState(new TestState());
    app.start();

    return 0;
}

/** TODO LIST :

    - save a tester
    - tester lvl avec un perso

    - entity.hpp : change enum -> const unsigned int

    - add GUI
    - Commenter
    - Constructor improve (init variable, copie)
    - Message d'erreur

**/
