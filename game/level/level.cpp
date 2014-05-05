#include "level.hpp"

#include <iostream>
#include <fstream>

#include "tileset.hpp"


Level::Level( void ) : m_tileset(NULL), m_name(""), m_path(""), m_width(0), m_height(0), m_background_grid(NULL), m_background_vertices(NULL)
{

}

Level::~Level( void )
{

}

bool Level::load( const std::string path )
{
    m_path = path;

    std::ifstream file;
    file.open( path.c_str() );

    if( !file.is_open())
    {
        std::cerr << "Error : Can't open map file \"" + path + "\"" << std::endl;
        return false;
    }

    std::string buffer = "";
    bool b = true;

    do {
        file >> buffer;

        if(buffer == "+Map")
        {
            b = false;
        }
    } while( b && !file.eof() );

    if(file.eof())
    {
        std::cerr << "Error : Map not found in file : \"" + path + "\"" << std::endl;
        return false;
    }

    file >> m_name >> m_width >> m_height >> buffer;

    m_background_vertices.setPrimitiveType(sf::Quads);
    m_background_vertices.resize(m_width * m_height * 4);

    if(!m_background_grid)
    {
        delete m_background_grid;
        m_background_grid = NULL;
    }

    m_background_grid = new unsigned int[m_width * m_height];
    for(unsigned int w = 0; w < m_width; w++)
    {
        for(unsigned int h = 0; h < m_height; h++)
        {
            m_background_grid[w + h * m_width] = 33;
        }
    }

    if(!setTileset( buffer ))
    {
        std::cerr << "Error : Set Tileset \"" + path + "\" in Level" << std::endl;
        return false;
    }

    char t;
    unsigned int k = 0;

    while( k < m_width * m_height && !file.eof() )
    {
        file >> t;
        unsigned int n = t - 33;
        setTile( n, k % m_width, k / m_width );
        k++;
    }

    return true;
}

bool Level::save( const std::string path )
{
    if(m_path != path)
    {
        m_path = path;
    }

    std::ofstream file;
    file.open( path.c_str() );

    if(!file.is_open())
    {
        std::cerr << "Error : Save Level - Can't open file \"" + m_name + "\"" << std::endl;
        return false;
    }

    file << "+Map " << m_name << std::endl << m_width << " " << m_height << " " << m_tileset->getName() << std::endl;

    for(unsigned int y(0); y < m_height; y++)
    {
        for(unsigned int x(0); x < m_width; x++)
        {
            file << static_cast<char>(33 + m_background_grid[x + y * m_width]);
        }
    }

    return true;
}

void Level::setName( const std::string name )
{
    this->m_name = name;
}

bool Level::setTileset( const std::string path )
{
    if(!m_tileset) { m_tileset = new Tileset; }

    return m_tileset->load(path);
}

void Level::setTile( const unsigned int tile_id, const unsigned int x, const unsigned int y )
{
    m_background_grid[x + y * m_width] = tile_id;

    sf::Vertex * v = m_tileset->getVertex( tile_id );
    sf::Vertex * quad = & m_background_vertices[ ((y * m_width) + x) * 4];

    if( !v || !quad )
    {
        std::cerr << "Error : Set Tile - Vertex NULL " << std::endl;
    }
    else
    {
        quad[0].position.x = x * 32 + v[0].position.x;
        quad[0].position.y = y * 32 + v[0].position.y;
        quad[1].position.x = x * 32 + v[1].position.x;
        quad[1].position.y = y * 32 + v[1].position.y;
        quad[2].position.x = x * 32 + v[2].position.x;
        quad[2].position.y = y * 32 + v[2].position.y;
        quad[3].position.x = x * 32 + v[3].position.x;
        quad[3].position.y = y * 32 + v[3].position.y;

        quad[0].texCoords = v[0].texCoords;
        quad[1].texCoords = v[1].texCoords;
        quad[2].texCoords = v[2].texCoords;
        quad[3].texCoords = v[3].texCoords;
    }
}

bool Level::isBlocking( int x, int y ) const
{
    return m_tileset->isBlocking( x + y * m_width );
}

Tile * Level::getTile( int x, int y ) const
{
    return m_tileset->getTile(m_background_grid[x + y * m_width]);
}

sf::Vector2i Level::getSize( void ) const
{
    return sf::Vector2i( m_width, m_height );
}

void Level::update( void )
{
    for (unsigned int i = 0; i < m_width; ++i)
    {
        for (unsigned int j = 0; j < m_height; ++j)
        {
            sf::Vertex * v = m_tileset->getVertex( m_background_grid[i + j * m_width] );
            sf::Vertex * quad = & m_background_vertices[ ((j * m_width) + i) * 4];

            if(v == NULL || quad == NULL)
            {

            }
            else
            {
                quad[0].position.x = i * 32 + v[0].position.x;
                quad[0].position.y = j * 32 + v[0].position.y;
                quad[1].position.x = i * 32 + v[1].position.x;
                quad[1].position.y = j * 32 + v[1].position.y;
                quad[2].position.x = i * 32 + v[2].position.x;
                quad[2].position.y = j * 32 + v[2].position.y;
                quad[3].position.x = i * 32 + v[3].position.x;
                quad[3].position.y = j * 32 + v[3].position.y;

                quad[0].texCoords = v[0].texCoords;
                quad[1].texCoords = v[1].texCoords;
                quad[2].texCoords = v[2].texCoords;
                quad[3].texCoords = v[3].texCoords;
            }
        }
    }
}

void Level::draw( sf::RenderTarget& target, sf::Vector2i scroll ) const
{
    scroll.x *= 32;
    scroll.y *= 32;
    sf::RenderStates states;
    states.transform.translate( scroll.x, scroll.y );

    if( m_tileset && m_tileset->getTexture() )
    {
        states.texture = m_tileset->getTexture();
    }

    target.draw(m_background_vertices, states);
}


