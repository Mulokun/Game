#ifndef _TILESET_H_
#define _TILESET_H_


#include <string>
#include <SFML/Graphics.hpp>


const int WALL_R = 0;
const int WALL_L = 1;
const int WALL_T = 2;
const int ROOF_TR = 3;
const int ROOF_TL = 4;
const int ROOF_D = 5;
const int ROOF_DR = 6;
const int ROOF_DL = 7;
const int ROOF_U = 8;
const int ROOF_UR = 9;
const int ROOF_UL = 10;
const int FLOOR_DEFAULT = 11;
const int FLOOR_SHADOW = 12;
#define NB_TILE 13

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
