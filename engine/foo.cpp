#include "foo.hpp"

#include <iostream>
#include <sstream>
#include <cmath>

void debug( std::string s )
{
    std::cout << s << std::endl;
}

void debug( int i )
{
    std::cout << i << std::endl;
}

std::string itos( int n )
{
    std::ostringstream oss;
    oss << n;
    return oss.str();
}

sf::Vector2f normalize( sf::Vector2f v )
{
    double n(sqrt( v.x*v.x + v.y*v.y ));

    if(n != 0) {
        v.x = v.x/n;
        v.y = v.y/n;
    }
    return v;
}

sf::Vector2f direction( sf::Vector2f vFrom, sf::Vector2f vTo )
{
    sf::Vector2f dir;
    dir.x = vTo.x - vFrom.x;
    dir.y = vTo.y - vFrom.y;

    return dir;
}



float distance( sf::Vector2f p1, sf::Vector2f p2 )
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float distance( sf::Vector2i p1, sf::Vector2i p2 )
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}


sf::Vector2f posLarg(bool sensRotation, sf::Vector2f pos, sf::Vector2f direction, int width)
{
    float c(1), d;
    sf::Vector2f temp, dir;

    dir.x = direction.x - pos.x;
    dir.y = direction.y - pos.y;

    d = ( sqrt( dir.x * dir.x + dir.y * dir.y ) );

    if (d != 0)
    {
        c = width / d;
    }

    dir.x = dir.x * c;
    dir.y = dir.y * c;

    if (sensRotation == true)
    {
        /* Sens Inverse */
        /*  Y <- -X
            X <- Y */
        pos.y -= dir.x;
        pos.x += dir.y;
    }
    else
    {
        /* Sens Horraire */
        /*  X <- -Y
            Y <- X */
        pos.x -= dir.y;
        pos.y += dir.x;
    }

    return pos;
}