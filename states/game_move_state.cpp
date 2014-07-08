#include "game_move_state.hpp"

#include "SFML/Audio.hpp"

#include "../engine/foo.hpp"
#include "../engine/time.hpp"
#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/data_manager.hpp"

#include "../game/level/pathfinding.hpp"

#include "game_move_ani_state.hpp"


Game_MoveState::Game_MoveState( GameDatas * gd, Entity * selected ) : m_gameDatas(gd), m_selected(selected)
{
    init();
}

Game_MoveState::~Game_MoveState( void ) { }

void Game_MoveState::init( void )
{
    m_oldPosition = m_selected->getPosition();
    m_cursorPosition = m_oldPosition;

    initMobilityArrows();
    m_mobilityPath.clear();

    m_mobilityAreaAnimation.load("data/animation/mobility_area.ani");
    setMobilityArea(m_selected);
}

void Game_MoveState::draw( sf::RenderTarget & window )
{
    m_gameDatas->level.draw( window );
    m_gameDatas->level.drawRoof( window );

    sf::Sprite * area = m_mobilityAreaAnimation.update();
    for(std::vector< sf::Vector2i >::iterator it = m_mobilityArea.begin(); it != m_mobilityArea.end(); ++it) {
        area->setPosition( it->x * Tileset::SizeTile, it->y * Tileset::SizeTile );
        window.draw(*area);
    }

    for(unsigned int i = 0; i < m_gameDatas->entities.size(); ++i) {
        Animation * a = m_gameDatas->entities[i]->getAnimation(ANI_STAY);
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

void Game_MoveState::update( void )
{
    /// TODO : supprimer, ici c'est juste pour un test
    /// Plus tard, ce sera init() qui sera appele
    if(m_selected->getPosition() != m_oldPosition) {
        setMobilityArea(m_selected);
    }

    if( m_cursorNextAction <= Time::elapsed() ) {
        sf::Vector2i cursorMove(0, 0);
        if(sf::Keyboard::isKeyPressed(Configuration::KEY_UP)) { cursorMove.y += -1; }
        if(sf::Keyboard::isKeyPressed(Configuration::KEY_DOWN)) { cursorMove.y += 1; }
        if(sf::Keyboard::isKeyPressed(Configuration::KEY_LEFT)) { cursorMove.x += -1; }
        if(sf::Keyboard::isKeyPressed(Configuration::KEY_RIGHT)) { cursorMove.x += 1; }

        sf::Vector2i newCursorPosition( m_cursorPosition.x + cursorMove.x, m_cursorPosition.y + cursorMove.y );
        if( !((distanceManhattan(m_cursorPosition, m_selected->getPosition()) <= m_selected->getMobility()) && (distanceManhattan(newCursorPosition, m_selected->getPosition()) > m_selected->getMobility()) ) ) {
            setCursorMove(cursorMove);
        }
    }

    /// TODO : Chemin personnalisé
    if( !m_gameDatas->level.isWall(m_cursorPosition) && distanceManhattan(m_cursorPosition, m_selected->getPosition()) <= m_selected->getMobility() ) {
        m_mobilityPath.clear();
        m_mobilityPath = pathfinding(&m_gameDatas->level, m_selected->getPosition(), m_cursorPosition);
    }
}

void Game_MoveState::handleEvent( sf::Event & e )
{
    if( e.type == sf::Event::KeyReleased )
    {
        m_cursorNextAction = Time::elapsed() + CURSOR_TIME_AFTER_PRESS;;
    }

    if(e.type == sf::Event::KeyPressed)
    {
        if(e.key.code == Configuration::KEY_START) {
            StateManager::popState();
        }

        if(e.key.code == Configuration::KEY_UP) {
            m_cursorNextAction = sf::Time::Zero;
            setCursorMove( sf::Vector2i(0, -1) );
            m_cursorNextAction = Time::elapsed() + CURSOR_TIME_AFTER_PRESS;
        }
        if(e.key.code == Configuration::KEY_DOWN) {
            m_cursorNextAction = sf::Time::Zero;
            setCursorMove( sf::Vector2i(0, 1) );
            m_cursorNextAction = Time::elapsed() + CURSOR_TIME_AFTER_PRESS;
        }
        if(e.key.code == Configuration::KEY_LEFT) {
            m_cursorNextAction = sf::Time::Zero;
            setCursorMove( sf::Vector2i(-1, 0) );
               m_cursorNextAction = Time::elapsed() + CURSOR_TIME_AFTER_PRESS;
        }
        if(e.key.code == Configuration::KEY_RIGHT) {
            m_cursorNextAction = sf::Time::Zero;
            setCursorMove( sf::Vector2i(1, 0) );
            m_cursorNextAction = Time::elapsed() + CURSOR_TIME_AFTER_PRESS;
        }

        if(e.key.code == Configuration::KEY_A) {
            if(!m_gameDatas->level.isWall(m_cursorPosition) && distanceManhattan(m_selected->getPosition(), m_cursorPosition) <= m_selected->getMobility()) {
                m_selected->useAP(1);
                m_selected->endTurn();
                /// TODO : endTurn ne devra plus etre la (c'est que pour des testes)
                StateManager::addState(new Game_MoveAniState(m_gameDatas, m_selected, m_mobilityPath));
            }
        }
    }
}




void Game_MoveState::setMobilityArea( Entity * e )
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


void Game_MoveState::initMobilityArrows( void )
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

void Game_MoveState::setCursorMove( sf::Vector2i cursorMove )
{
    if( (cursorMove.x != 0 || cursorMove.y != 0) )
    {
        m_cursorPosition.x += cursorMove.x;
        m_cursorPosition.y += cursorMove.y;
        if(m_cursorPosition.x >= m_gameDatas->level.getSize().x) { m_cursorPosition.x = m_gameDatas->level.getSize().x - 1; }
        if(m_cursorPosition.y >= m_gameDatas->level.getSize().y) { m_cursorPosition.y = m_gameDatas->level.getSize().y - 1; }
        if(m_cursorPosition.x < 0) { m_cursorPosition.x = 0; }
        if(m_cursorPosition.y < 0) { m_cursorPosition.y = 0; }

        m_cursorNextAction = Time::elapsed() + CURSOR_TIME_CONTINUOUS;
    }
}


