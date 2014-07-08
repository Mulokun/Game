#ifndef _CONFIGURATION_
#define _CONFIGURATION_


#include <SFML/Graphics.hpp>


class Configuration
{
    public :

        static int ZOOM;

        static sf::Keyboard::Key KEY_UP;
        static sf::Keyboard::Key KEY_DOWN;
        static sf::Keyboard::Key KEY_LEFT;
        static sf::Keyboard::Key KEY_RIGHT;
        static sf::Keyboard::Key KEY_A;
        static sf::Keyboard::Key KEY_B;
        static sf::Keyboard::Key KEY_C;
        static sf::Keyboard::Key KEY_START;

        static void load( std::string path = "" );
};

#endif // _CONFIGURATION_
