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

}

bool Tileset::load( const std::string path )
{
    m_name = path;


    m_nameTexture = path;
    m_texture = DataManager::getTexture( path );

    Tile * t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    sf::Vector2i pos(0, 0);
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_UL1] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 1; pos.y = 0;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_UR1] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 0; pos.y = 1;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_DL1] = t;

    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 1; pos.y = 1;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_DR1] = t;

 /// //

    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 2; pos.y = 0;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_DR2] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 3; pos.y = 0;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_DL2] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 2; pos.y = 1;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_UR2] = t;

    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 3; pos.y = 1;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_UL2] = t;

/// //

    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 0; pos.y = 2;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_R] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 1; pos.y = 2;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_L] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 2; pos.y = 2;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_U] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 3; pos.y = 2;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[WALL_D] = t;


/// //

    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 4; pos.y = 0;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[FLOOR_SHADOW] = t;


    t = new Tile[4];
    t[0]->position = sf::Vector2f(0, 0);
    t[1]->position = sf::Vector2f(SizeTile, 0);
    t[2]->position = sf::Vector2f(SizeTile, SizeTile);
    t[3]->position = sf::Vector2f(0, SizeTile);
    pos.x = 4; pos.y = 1;
    t[0]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile);
    t[1]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile);
    t[2]->texCoords = sf::Vector2f(pos.x * SizeTile + SizeTile, pos.y * SizeTile + SizeTile);
    t[3]->texCoords = sf::Vector2f(pos.x * SizeTile, pos.y * SizeTile + SizeTile);
    m_tiles[FLOOR_DEFAULT] = t;


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
    if(id < NB_TILE && id >= 0)
    {
        return m_tiles[id];
    }

    return NULL;
}
