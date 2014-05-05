#ifndef _TILESET_H_
#define _TILESET_H_


#include <string>
#include <SFML/Graphics.hpp>


typedef struct Tile {
    sf::Vertex * vertex;
    bool block;
} Tile;


class Tileset
{

    public :
        Tileset( void );
        ~Tileset( void );

        bool load( const std::string path );

        /// Getters :
        const sf::Texture * getTexture( void ) const;
        const sf::Vertex * getVertex( unsigned int id ) const;
        std::string getName( void ) const;
        std::string getNameTexture( void ) const;
        const Tile * getTile( unsigned int id ) const;

        bool isBlocking( unsigned int id ) const;

        const static unsigned int SizeTile = 32;

    private :
        std::string m_name;
        std::string m_nameTexture;
        sf::Texture * m_texture;
        Tile * m_tiles;

};

#endif // _TILESET_H_
