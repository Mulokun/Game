#include "game_select_entity_state.hpp"

#include "game_move_state.hpp"
#include "../engine/animation.hpp"
#include "../engine/state_manager.hpp"
#include "../engine/foo.hpp"

Game_SelectEntityState::Game_SelectEntityState( GameDatas * gd ) : m_gameDatas(gd)
{

}

Game_SelectEntityState::~Game_SelectEntityState( void )
{

}

void Game_SelectEntityState::init( void )
{

}

void Game_SelectEntityState::draw( sf::RenderTarget & window )
{
    m_gameDatas->level.draw( window );
    m_gameDatas->level.drawRoof( window );

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
}

void Game_SelectEntityState::update( void )
{
    if(isEntityReady()) {
        selectNextEntity();
        StateManager::addState( new Game_MoveState(m_gameDatas, m_next) );
    } else {
        for(unsigned int i = 0; i < m_gameDatas->entities.size(); i++) {
            m_gameDatas->entities[i]->setTimeElapsed(1);
        }
        debug( m_gameDatas->entities[0]->getTimeRemain() );
    }
}

void Game_SelectEntityState::handleEvent( sf::Event & e )
{

}

void Game_SelectEntityState::selectNextEntity( void )
{
    m_next = NULL;
    /// TODO : S'il y a plusieurs candidats pour etre next
    for(unsigned int i = 0; i < m_gameDatas->entities.size(); i++) {
        if( m_gameDatas->entities[i]->isReady() ) {
            m_next = m_gameDatas->entities[i];
        }
    }
}

bool Game_SelectEntityState::isEntityReady( void )
{
    if(m_gameDatas->entities[0]->getTimeRemain() == 1) {
        debug(1);
    }

    for(unsigned int i = 0; i < m_gameDatas->entities.size(); i++) {
        if( m_gameDatas->entities[i]->isReady() ) {
            return true;
        }
    }

    return false;
}
