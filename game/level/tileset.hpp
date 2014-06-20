#ifndef _TILESET_H_
#define _TILESET_H_


#include <string>
#include <SFML/Graphics.hpp>


const unsigned int WALL_R = 0;
const unsigned int WALL_L = 1;
const unsigned int WALL_U = 2;
const unsigned int WALL_D = 3;
const unsigned int WALL_UR1 = 4;
const unsigned int WALL_UL1 = 5;
const unsigned int WALL_DR1 = 6;
const unsigned int WALL_DL1 = 7;
const unsigned int WALL_UR2 = 8;
const unsigned int WALL_UL2 = 9;
const unsigned int WALL_DR2 = 10;
const unsigned int WALL_DL2 = 11;
const unsigned int FLOOR_DEFAULT = 12;
const unsigned int FLOOR_SHADOW = 13;
#define NB_TILE 14

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
        Tile * m_tiles[NB_TILE];

};

#endif // _TILESET_H_
