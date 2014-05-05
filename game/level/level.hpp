#ifndef _LEVEL_H_
#define _LEVEL_H_


#include <string>
#include "SFML/Graphics.hpp"


#include "tileset.hpp"


class Level
{

    public :
        Level( void );
        ~Level( void );

        bool load( const std::string path );
        bool save( const std::string path ) const;
        void init( bool * grid, const unsigned int width, const unsigned int height );

        void setName( const std::string name );
        bool setTileset( const std::string path );
        void setTile( const unsigned int tile_id, const unsigned int x, const unsigned int y );

        bool isBlocking( int x, int y ) const;
        Tile * getTile( int x, int y ) const;
        sf::Vector2i getSize( void ) const;

        void update( void ); // Init. les VertexArray en fonction des grilles
        void draw( sf::RenderTarget& target, sf::Vector2i scroll ) const;

    private :
        Tileset * m_tileset;
        std::string m_name; // Name of the level
        std::string m_path;

        unsigned int m_width;
        unsigned int m_height;

        unsigned int * m_background_grid; // Floor + Wall
        sf::VertexArray m_background_vertices; // Floor + Wall

        /// LATER :
        //unsigned int * m_decoration_grid;
        //sf::VertexArray m_decoration_vertex;

};

#endif // _LEVEL_H_
