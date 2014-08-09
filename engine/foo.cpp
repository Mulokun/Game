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



float distanceEuclidienne( sf::Vector2f p1, sf::Vector2f p2 )
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

float distanceEuclidienne( sf::Vector2i p1, sf::Vector2i p2 )
{
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
}

unsigned int distanceManhattan( sf::Vector2i p1, sf::Vector2i p2 )
{
    return std::abs(p1.x - p2.x) + std::abs(p1.y - p2.y);
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


sf::Vector2f getAbsolutePosition( sf::FloatRect r, sf::FloatRect c, RelativePosition p )
{
    sf::Vector2f v( r.left, r.top );

    switch( p )
    {
        case TOP :
            v.y = c.top;
            break;

        case BOTTOM :
            v.y = c.height - r.height + c.top;
            break;

        case MIDDLE :
            v.y = c.height/2 - r.height/2 + c.top;
            break;

        case LEFT :
            v.x = c.left;
            break;

        case RIGHT :
            v.x = c.width - r.width + c.left;
            break;

        case CENTER :
            v.x = c.width/2 - r.width/2 + c.left;
            break;

        default :
            break;
    }

    return v;
}

bool isInner( sf::FloatRect r, sf::Vector2i p )
{
    return ( p.y > r.top && p.y < r.top + r.height ) && ( p.x > r.left && p.x < r.left + r.width  );
}

