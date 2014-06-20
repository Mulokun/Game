#ifndef _FOO_
#define _FOO_


#include <string>
#include "SFML/Graphics.hpp"


void debug( std::string s );
void debug( int i );

std::string itos( int n );

sf::Vector2f normalize( sf::Vector2f v );
sf::Vector2f direction( sf::Vector2f vFrom, sf::Vector2f vTo );

float distanceEuclidienne( sf::Vector2f p1, sf::Vector2f p2 );
float distanceEuclidienne( sf::Vector2i p1, sf::Vector2i p2 );
unsigned int distanceManhattan( sf::Vector2i p1, sf::Vector2i p2 );

sf::Vector2f posLarg(bool sensRotation, sf::Vector2f pos, sf::Vector2f direction, int width);

#endif // _FOO_
