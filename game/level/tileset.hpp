#ifndef _TILESET_H_
#define _TILESET_H_


#include <string>
#include <SFML/Graphics.hpp>


const int WALL_RIGHT = 0;
const int WALL_CORNER_BOTTOM_LEFT = 1;
const int WALL_LEFT = 2;
const int WALL_CORNER_TOP_RIGHT = 3;
const int WALL_TOP = 4;
const int WALL_CORNER_TOP_LEFT = 5;
const int WALL_CORNER_BOTTOM_RIGHT = 6;
const int WALL_BOTTOM = 7;
const int FLOOR_SHADOW = 8;
const int FLOOR_DEFAULT = 9;
const int FLOOR_WALL_DOWN = 10;
const int ROOF_WALL = 11;
const int WALL_TINY_CORNER_LEFT = 12;
const int WALL_TINY_CORNER_RIGHT = 13;
const int DEFAULT_WALL = 14;

typedef sf::Vertex Tile[4];


class Tileset
{

    public :
        Tileset( const std::string path = "" );
        ~Tileset( void );

        bool load( const std::string path );

        /// Getters :
        std::string getName( void ) const;
        std::string getNameTexture( void ) const;
        const sf::Texture * getTexture( void ) const;
        const Tile * getTile( unsigned int id ) const;

        const static unsigned int SizeTile = 32;

    private :
        std::string m_name;
        std::string m_nameTexture;
        sf::Texture * m_texture;
        Tile * m_tiles[15];

};

#endif // _TILESET_H_
