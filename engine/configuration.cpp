#include "configuration.hpp"


void Configuration::load( std::string path )
{
    Configuration::KEY_UP = sf::Keyboard::Z;
    Configuration::KEY_DOWN = sf::Keyboard::S;
    Configuration::KEY_LEFT = sf::Keyboard::Q;
    Configuration::KEY_RIGHT = sf::Keyboard::D;
    Configuration::KEY_A = sf::Keyboard::J;
    Configuration::KEY_B = sf::Keyboard::I;
    Configuration::KEY_C = sf::Keyboard::O;
    Configuration::KEY_START = sf::Keyboard::Escape;

    Configuration::ZOOM = 1;
}

int Configuration::ZOOM;

sf::Keyboard::Key Configuration::KEY_UP;
sf::Keyboard::Key Configuration::KEY_DOWN;
sf::Keyboard::Key Configuration::KEY_LEFT;
sf::Keyboard::Key Configuration::KEY_RIGHT;
sf::Keyboard::Key Configuration::KEY_A;
sf::Keyboard::Key Configuration::KEY_B;
sf::Keyboard::Key Configuration::KEY_C;
sf::Keyboard::Key Configuration::KEY_START;
