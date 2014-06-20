#include "test_state.hpp"

#include "SFML/Audio.hpp"

#include "../engine/foo.hpp"
#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"

#include "../game/level/pathfinding.hpp"


TestState::TestState( void )
{
    init();
}

TestState::~TestState( void ) { }

void TestState::init( void )
{
    initMobilityArrows();
    m_gameDatas = new GameDatas;

    m_gameDatas->level.load("data/level/level_1.lvl");

    Entity * e = new Entity();
    e->addAnimation(STAY, "data/animation/thief_stay.ani");
    e->setPosition(4, 2);
    m_gameDatas->entities.push_back(e);
    m_selected = e;
    m_cursorPosition = sf::Vector2i(4, 2);
    m_mobilityPath.clear();

    m_areaAnimation.load("data/animation/mobility_area.ani");
    setMobilityArea(e);
}

void TestState::draw( sf::RenderTarget & window )
{
    m_gameDatas->level.draw( window );
    m_gameDatas->level.drawRoof( window );

    sf::Sprite * area = m_areaAnimation.update();
    for(std::vector< sf::Vector2i >::iterator it = m_mobilityArea.begin(); it != m_mobilityArea.end(); ++it) {
        area->setPosition( it->x * Tileset::SizeTile, it->y * Tileset::SizeTile );
        window.draw(*area);
    }

    for(unsigned int i = 0; i < m_gameDatas->entities.size(); ++i) {
        Animation * a = m_gameDatas->entities[i]->getAnimation(STAY);
        if(a) {
            sf::Sprite * s = a->update();
            if(s) {
                s->setPosition( m_gameDatas->entities[i]->getPosition().x * Tileset::SizeTile,  m_gameDatas->entities[i]->getPosition().y * Tileset::SizeTile );
                window.draw(*s);
            }
        }
    }


    for(unsigned int i = 1; i < m_mobilityPath.size(); ++i) {
        sf::Sprite * s = NULL;

        sf::Vector2i current = m_mobilityPath[i];
        sf::Vector2i pred = m_mobilityPath[i-1];

        if(i+1 < m_mobilityPath.size()) {
            sf::Vector2i next = m_mobilityPath[i+1];

            if( (pred.x < current.x && pred.y == current.y) && (next.x > current.x && next.y == current.y) ) { s = m_mobilityArrows[ARROW_HORIZONTAL]; }
            else if( (pred.x == current.x && pred.y < current.y) && (next.x == current.x && next.y > current.y) ) { s = m_mobilityArrows[ARROW_VERTICAL]; }
            else if( (pred.x < current.x && pred.y == current.y) && (next.x == current.x && next.y > current.y) ) { s = m_mobilityArrows[ARROW_LEFT_DOWN]; }
            else if( (pred.x < current.x && pred.y == current.y) && (next.x == current.x && next.y < current.y) ) { s = m_mobilityArrows[ARROW_LEFT_UP]; }
            else if( (pred.x > current.x && pred.y == current.y) && (next.x == current.x && next.y > current.y) ) { s = m_mobilityArrows[ARROW_RIGHT_DOWN]; }
            else if( (pred.x > current.x && pred.y == current.y) && (next.x == current.x && next.y < current.y) ) { s = m_mobilityArrows[ARROW_RIGHT_UP]; }
            else if( (next.x < current.x && next.y == current.y) && (pred.x > current.x && pred.y == current.y) ) { s = m_mobilityArrows[ARROW_HORIZONTAL]; }
            else if( (next.x == current.x && next.y < current.y) && (pred.x == current.x && pred.y > current.y) ) { s = m_mobilityArrows[ARROW_VERTICAL]; }
            else if( (next.x < current.x && next.y == current.y) && (pred.x == current.x && pred.y > current.y) ) { s = m_mobilityArrows[ARROW_LEFT_DOWN]; }
            else if( (next.x < current.x && next.y == current.y) && (pred.x == current.x && pred.y < current.y) ) { s = m_mobilityArrows[ARROW_LEFT_UP]; }
            else if( (next.x > current.x && next.y == current.y) && (pred.x == current.x && pred.y > current.y) ) { s = m_mobilityArrows[ARROW_RIGHT_DOWN]; }
            else if( (next.x > current.x && next.y == current.y) && (pred.x == current.x && pred.y < current.y) ) { s = m_mobilityArrows[ARROW_RIGHT_UP]; }
            else { debug("Erreur Arrow Direction."); }
        } else {
            if(pred.x > current.x && pred.y == current.y) { s = m_mobilityArrows[ARROW_END_RIGHT]; }
            else if(pred.x < current.x && pred.y == current.y) { s = m_mobilityArrows[ARROW_END_LEFT]; }
            else if(pred.x == current.x && pred.y > current.y) { s = m_mobilityArrows[ARROW_END_DOWN]; }
            else if(pred.x == current.x && pred.y < current.y) { s = m_mobilityArrows[ARROW_END_UP]; }
            else { debug("Erreur Arrow Direction 2."); }
        }

        if(s) {
            s->setPosition(current.x * Tileset::SizeTile, current.y * Tileset::SizeTile);
            window.draw(*s);
        }
    }


    sf::RectangleShape r;
    r.setSize( sf::Vector2f(30, 30) );
    r.setFillColor( sf::Color::Transparent );
    r.setOutlineThickness(2);
    r.setOutlineColor(sf::Color::Green);
    r.setPosition(m_cursorPosition.x * Tileset::SizeTile, m_cursorPosition.y * Tileset::SizeTile);
    window.draw(r);


}

void TestState::update( void )
{
    /// TODO : Chemin personnalisé
    if( !m_gameDatas->level.isWall(m_cursorPosition) && distanceManhattan(m_cursorPosition, m_selected->getPosition()) <= m_selected->getMobility() ) {
        m_mobilityPath.clear();
        m_mobilityPath = pathfinding(&m_gameDatas->level, m_selected->getPosition(), m_cursorPosition);
    }
}

void TestState::handleEvent( sf::Event & e )
{
    if (e.type == sf::Event::KeyPressed)
    {
        switch(e.key.code) {
            case sf::Keyboard::Escape : {
                StateManager::popState();
            } break;

            case sf::Keyboard::Left : {
                if(m_cursorPosition.x > 0) { m_cursorPosition.x--; }
            } break;
            case sf::Keyboard::Right : {
                if(m_cursorPosition.x < m_gameDatas->level.getSize().x - 1) { m_cursorPosition.x++; }
            } break;
            case sf::Keyboard::Up : {
                if(m_cursorPosition.y > 0) { m_cursorPosition.y--; }
            } break;
            case sf::Keyboard::Down : {
                if(m_cursorPosition.y < m_gameDatas->level.getSize().y - 1) { m_cursorPosition.y++; }
            } break;

            default :
                break;
        }
    }
}




void TestState::setMobilityArea( Entity * e )
{
    m_mobilityArea.clear();

    sf::Vector2i pos = e->getPosition();
    unsigned int radius = e->getMobility();

    for(unsigned int x = std::max(0, pos.x - (int)radius); x <= pos.x + radius; ++x) {
        for(unsigned int y = std::max(0, pos.y - (int)radius); y <= pos.y + radius; ++y) {
            if( !m_gameDatas->level.isWall(x, y) && distanceManhattan(pos, sf::Vector2i(x, y)) <= radius ) {
                m_mobilityArea.push_back( sf::Vector2i(x, y) );
            }
        }
    }
}


void TestState::initMobilityArrows( void )
{
    m_mobilityArrows[ARROW_HORIZONTAL] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*0, 0, 32, 32));
    m_mobilityArrows[ARROW_VERTICAL] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*1, 0, 32, 32));
    m_mobilityArrows[ARROW_RIGHT_DOWN] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*2, 0, 32, 32));
    m_mobilityArrows[ARROW_LEFT_UP] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*3, 0, 32, 32));
    m_mobilityArrows[ARROW_RIGHT_UP] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*4, 0, 32, 32));
    m_mobilityArrows[ARROW_LEFT_DOWN] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*5, 0, 32, 32));
    m_mobilityArrows[ARROW_END_DOWN] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*6, 0, 32, 32));
    m_mobilityArrows[ARROW_END_UP] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*7, 0, 32, 32));
    m_mobilityArrows[ARROW_END_LEFT] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*8, 0, 32, 32));
    m_mobilityArrows[ARROW_END_RIGHT] = DataManager::getSprite("data/other/mobility_arrows.png", sf::FloatRect(32*9, 0, 32, 32));
}


