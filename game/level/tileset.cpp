#include "tileset.hpp"

#include <iostream>
#include <fstream>
#include <cmath>


#include "../data_manager.hpp"

Tileset::Tileset( void ) : m_name(""), m_nameTexture(""), m_texture(NULL) { }
Tileset::~Tileset( void )
{
    for( std::vector<Tile*>::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
    {
        delete (*it);
    }

    m_tiles.clear();
}

bool Tileset::load( const std::string path )
{
    m_name = path;

    for( std::vector<Tile*>::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it )
    {
        delete (*it);
    }

    m_tiles.clear();

    std::ifstream file;
    file.open( path.c_str() );

    if( !file.is_open() )
    {
        std::cerr << "Error : Tileset - Can't open file \"" + path + "\"" << std::endl;
        return false;
    }

    std::string buffer;
    file >> buffer;

    m_nameTexture = buffer;
    m_texture = DataManager::getTexture( buffer );

    bool b = true;
    while( !file.eof() )
    {
        do {
            file >> buffer;

            if(buffer == "+Tile")
            {
                b = false;
            }
        } while( b && !file.eof() );

        if( file.eof() )
        {
            return true;
        }

        sf::Vector2i pos;
        int bloc = 1;
        file >> pos.x >> pos.y >> bloc;

        Tile * t = new Tile;
        t->vertex = new sf::Vertex[4];

        t->vertex[0].position = sf::Vector2f(0, 0);
        t->vertex[1].position = sf::Vector2f(SizeTile, 0);
        t->vertex[2].position = sf::Vector2f(SizeTile, SizeTile);
        t->vertex[3].position = sf::Vector2f(0, SizeTile);

        t->vertex[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
        t->vertex[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
        t->vertex[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
        t->vertex[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);

        if(bloc == 0)
        {
            t->block = false;
        }
        else
        {
            t->block = true;
        }

        m_tiles.push_back(t);

        buffer == "";
    }

    return true;
}

sf::Texture * Tileset::getTexture( void ) const
{
    return m_texture;
}

sf::Vertex * Tileset::getVertex( unsigned int id ) const
{
    sf::Vertex * v = NULL;

    if(id < m_tiles.size())
    {
        v = m_tiles[id]->vertex;
    }

    return v;
}

std::string Tileset::getName( void ) const
{
    return m_name;
}

std::string Tileset::getNameTexture( void ) const
{
    return m_nameTexture;
}

Tile * Tileset::getTile( unsigned int id ) const
{
    if(id < m_tiles.size())
    {
        return m_tiles[id];
    }

    return NULL;
}

bool Tileset::isBlocking( unsigned int id ) const
{
    bool b = true;

    if(id < m_tiles.size())
    {
        b = m_tiles[id]->block;
    }

    return b;
}

