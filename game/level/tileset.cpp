#include "tileset.hpp"

#include <iostream>
#include <fstream>
#include <cmath>


#include "../../engine/data_manager.hpp"

Tileset::Tileset( const std::string path ) : m_name(""), m_nameTexture(""), m_texture(NULL) {
    if(!path.empty()) { load(path); }
}

Tileset::~Tileset( void )
{
    delete [] m_tiles;
}

bool Tileset::load( const std::string path )
{
    m_name = path;


    if(m_tiles) { delete [] m_tiles; }
    m_tiles = new Tile[12];

    m_nameTexture = path;
    m_texture = DataManager::getTexture( path );



    Tile t;
    t[0].position = sf::Vector2f(0, 0);
    t[1].position = sf::Vector2f(SizeTile, 0);
    t[2].position = sf::Vector2f(SizeTile, SizeTile);
    t[3].position = sf::Vector2f(0, SizeTile);


    sf::Vector2i pos(0, 0);
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_RIGHT][0] = t[0];
    m_tiles[WALL_RIGHT][1] = t[1];
    m_tiles[WALL_RIGHT][2] = t[2];
    m_tiles[WALL_RIGHT][3] = t[3];


    pos.x = 1; pos.y = 0;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[FLOOR_SHADOW][0] = t[0];
    m_tiles[FLOOR_SHADOW][1] = t[1];
    m_tiles[FLOOR_SHADOW][2] = t[2];
    m_tiles[FLOOR_SHADOW][3] = t[3];


    pos.x = 2; pos.y = 0;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_LEFT][0] = t[0];
    m_tiles[WALL_LEFT][1] = t[1];
    m_tiles[WALL_LEFT][2] = t[2];
    m_tiles[WALL_LEFT][3] = t[3];

 /// //

    pos.x = 0; pos.y = 1;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_CORNER_TOP_RIGHT][0] = t[0];
    m_tiles[WALL_CORNER_TOP_RIGHT][1] = t[1];
    m_tiles[WALL_CORNER_TOP_RIGHT][2] = t[2];
    m_tiles[WALL_CORNER_TOP_RIGHT][3] = t[3];


    pos.x = 1; pos.y = 1;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_TOP][0] = t[0];
    m_tiles[WALL_TOP][1] = t[1];
    m_tiles[WALL_TOP][2] = t[2];
    m_tiles[WALL_TOP][3] = t[3];


    pos.x = 2; pos.y = 1;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_CORNER_TOP_LEFT][0] = t[0];
    m_tiles[WALL_CORNER_TOP_LEFT][1] = t[1];
    m_tiles[WALL_CORNER_TOP_LEFT][2] = t[2];
    m_tiles[WALL_CORNER_TOP_LEFT][3] = t[3];

/// //

    pos.x = 0; pos.y = 2;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_CORNER_BOTTOM_RIGHT][0] = t[0];
    m_tiles[WALL_CORNER_BOTTOM_RIGHT][1] = t[1];
    m_tiles[WALL_CORNER_BOTTOM_RIGHT][2] = t[2];
    m_tiles[WALL_CORNER_BOTTOM_RIGHT][3] = t[3];


    pos.x = 1; pos.y = 2;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_BOTTOM][0] = t[0];
    m_tiles[WALL_BOTTOM][1] = t[1];
    m_tiles[WALL_BOTTOM][2] = t[2];
    m_tiles[WALL_BOTTOM][3] = t[3];


    pos.x = 2; pos.y = 2;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_CORNER_BOTTOM_LEFT][0] = t[0];
    m_tiles[WALL_CORNER_BOTTOM_LEFT][1] = t[1];
    m_tiles[WALL_CORNER_BOTTOM_LEFT][2] = t[2];
    m_tiles[WALL_CORNER_BOTTOM_LEFT][3] = t[3];

/// //

    pos.x = 0; pos.y = 3;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[FLOOR_DEFAULT][0] = t[0];
    m_tiles[FLOOR_DEFAULT][1] = t[1];
    m_tiles[FLOOR_DEFAULT][2] = t[2];
    m_tiles[FLOOR_DEFAULT][3] = t[3];


    pos.x = 1; pos.y = 3;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[FLOOR_WALL_DOWN][0] = t[0];
    m_tiles[FLOOR_WALL_DOWN][1] = t[1];
    m_tiles[FLOOR_WALL_DOWN][2] = t[2];
    m_tiles[FLOOR_WALL_DOWN][3] = t[3];


    pos.x = 2; pos.y = 3;
    t[0].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2].texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3].texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[ROOF_WALL_DOWN][0] = t[0];
    m_tiles[ROOF_WALL_DOWN][1] = t[1];
    m_tiles[ROOF_WALL_DOWN][2] = t[2];
    m_tiles[ROOF_WALL_DOWN][3] = t[3];


    return true;
}

std::string Tileset::getName( void ) const
{
    return m_name;
}

std::string Tileset::getNameTexture( void ) const
{
    return m_nameTexture;
}

const sf::Texture * Tileset::getTexture( void ) const
{
    return m_texture;
}

const Tile * Tileset::getTile( unsigned int id ) const
{
    if(id < 12 && id >= 0)
    {
        return &m_tiles[id];
    }

    return NULL;
}
