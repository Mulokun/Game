#include "level.hpp"

#include <iostream>
#include <fstream>

#include "tileset.hpp"


Level::Level( void ) : m_tileset(NULL), m_name(""), m_path(""), m_width(0), m_height(0), m_background_grid(NULL)
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
/*
    m_roof_vertices.setPrimitiveType(sf::Quads);
    m_roof_vertices.resize(m_width * m_height * 4);
*/
    if(!m_background_grid)
    {
        delete m_background_grid;
        m_background_grid = NULL;
    }

    m_background_grid = new bool[m_width * m_height];
    for(unsigned int w = 0; w < m_width; w++) {
        for(unsigned int h = 0; h < m_height; h++) {
            m_background_grid[w + h * m_width] = WALL;
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
        if(t == 'O') {
            setFloor( k % m_width, k / m_width );
        } else {
            setWall( k % m_width, k / m_width );
        }

        k++;
    }

    update();

    return true;
}

bool Level::save( const std::string path )
{
    if(m_path != path)
    {
        m_path.assign(path);
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
            file << (isWall(x, y) ? 'X' : 'O');
        }
    }

    return true;
}

void Level::init( bool * grid, const unsigned int width, const unsigned int height )
{
    m_width = width;
    m_height = height;
    m_background_grid = grid;
    update();
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

void Level::setWall( const unsigned int x, const unsigned int y )
{
    if(isBounded(x, y)) {
        m_background_grid[x + y * m_width] = WALL;
    }
}

void Level::setFloor( const unsigned int x, const unsigned int y )
{
    if(isBounded(x, y)) {
        m_background_grid[x + y * m_width] = FLOOR;
    }
}

bool Level::isWall( sf::Vector2i p ) const
{
    return isWall(p.x, p.y);
}

bool Level::isWall( int x, int y ) const
{
    if(!isBounded(x, y)) { return true; }
    else { return m_background_grid[x + y * m_width]; }
}

bool Level::isBounded( int x, int y ) const
{
    return x + y * m_width >= 0 && x + y * m_width < m_width * m_height;
}

sf::Vector2i Level::getSize( void ) const
{
    return sf::Vector2i( m_width, m_height );
}

void Level::update( void )
{
    m_roof_texture.create( m_width * Tileset::SizeTile, m_height * Tileset::SizeTile );
    m_roof_texture.clear( sf::Color::Transparent );

    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
        {
            const Tile * v = NULL;
            std::vector<const Tile *> roofs;
            sf::Vertex * quad = & m_background_vertices[ ((j * m_width) + i) * 4];

            if( !isWall(i, j) ) // Si c'est un sol
            {
                if( isWall(i, j-1) ) {
                    v = m_tileset->getTile(FLOOR_SHADOW);
                } else {
                    v = m_tileset->getTile(FLOOR_DEFAULT);
                }
            }
            else // Si c'est un mur
            {
                if( !isWall(i+1, j) ) {
                    roofs.push_back( m_tileset->getTile(WALL_L) );
                }
                if( !isWall(i-1, j) ) {
                    roofs.push_back( m_tileset->getTile(WALL_R) );
                }
                if( !isWall(i, j+1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_U) );
                }
                if( !isWall(i, j-1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_D) );
                }

                if( !isWall(i+1, j+1) && isWall(i+1, j) && isWall(i, j+1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_UL1) );
                }
                if( !isWall(i-1, j+1) && isWall(i-1, j) && isWall(i, j+1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_UR1) );
                }
                if( !isWall(i+1, j-1) && isWall(i+1, j) && isWall(i, j-1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_DL1) );
                }
                if( !isWall(i-1, j-1) && isWall(i-1, j) && isWall(i, j-1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_DR1) );
                }

                if( !isWall(i+1, j) && !isWall(i, j+1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_UL2) );
                }
                if( !isWall(i-1, j) && !isWall(i, j+1) ) {
                        roofs.push_back( m_tileset->getTile(WALL_UR2) );
                }
                if( !isWall(i+1, j) && !isWall(i, j-1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_DL2) );
                }
                if( !isWall(i-1, j) && !isWall(i, j-1) ) {
                    roofs.push_back( m_tileset->getTile(WALL_DR2) );
                }
            }


/// ------------------------------------------------------------

            if( v && quad )
            {
                quad[0].position.x = i * 32 + v[0]->position.x;
                quad[0].position.y = j * 32 + v[0]->position.y;
                quad[1].position.x = i * 32 + v[1]->position.x;
                quad[1].position.y = j * 32 + v[1]->position.y;
                quad[2].position.x = i * 32 + v[2]->position.x;
                quad[2].position.y = j * 32 + v[2]->position.y;
                quad[3].position.x = i * 32 + v[3]->position.x;
                quad[3].position.y = j * 32 + v[3]->position.y;

                quad[0].texCoords = v[0]->texCoords;
                quad[1].texCoords = v[1]->texCoords;
                quad[2].texCoords = v[2]->texCoords;
                quad[3].texCoords = v[3]->texCoords;
            }

            for(unsigned int k = 0; k < roofs.size(); ++k) {
                const Tile * t = roofs[k];
                sf::IntRect r( sf::Vector2i(t[0]->texCoords), sf::Vector2i(Tileset::SizeTile, Tileset::SizeTile));

                sf::Sprite s( * m_tileset->getTexture(), r);
                s.setPosition(i * Tileset::SizeTile, j * Tileset::SizeTile);

                m_roof_texture.draw(s);
            }

        }
    }

    m_roof_texture.display();
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


void Level::drawRoof( sf::RenderTarget& target, sf::Vector2i scroll ) const
{
    scroll.x *= 32;
    scroll.y *= 32;
    sf::RenderStates states;
    states.transform.translate( scroll.x, scroll.y );

    sf::Sprite s(m_roof_texture.getTexture());
    s.setPosition(0, 0);

    target.draw(s, states);
}


