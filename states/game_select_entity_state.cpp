#include "game_select_entity_state.hpp"

#include "game_player_move_state.hpp"
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
    m_gameDatas->drawAll( window );
}

void Game_SelectEntityState::update( void )
{
    if(isEntityReady()) {
        selectNextEntity();
        StateManager::addState( new Game_PlayerMoveState(m_gameDatas, m_next) );
    } else {
        for(unsigned int i = 0; i < m_gameDatas->playerEntities.size(); i++) {
            m_gameDatas->playerEntities[i]->setTimeElapsed(1);
        }
        for(unsigned int i = 0; i < m_gameDatas->enemyEntities.size(); i++) {
            m_gameDatas->enemyEntities[i]->setTimeElapsed(1);
        }
    }
}

void Game_SelectEntityState::handleEvent( sf::Event & e )
{

}

void Game_SelectEntityState::treatEvent( GameEvent e )
{

}

void Game_SelectEntityState::selectNextEntity( void )
{
    m_next = NULL;
    /// TODO : S'il y a plusieurs candidats pour etre next
    for(unsigned int i = 0; i < m_gameDatas->playerEntities.size(); i++) {
        if( m_gameDatas->playerEntities[i]->isReady() ) {
            m_next = m_gameDatas->playerEntities[i];
        }
    }

    for(unsigned int i = 0; i < m_gameDatas->enemyEntities.size(); i++) {
        if( m_gameDatas->enemyEntities[i]->isReady() ) {
            m_next = m_gameDatas->enemyEntities[i];
        }
    }
}

bool Game_SelectEntityState::isEntityReady( void )
{
    for(unsigned int i = 0; i < m_gameDatas->playerEntities.size(); i++) {
        if( m_gameDatas->playerEntities[i]->isReady() ) {
            return true;
        }
    }

    for(unsigned int i = 0; i < m_gameDatas->enemyEntities.size(); i++) {
        if( m_gameDatas->enemyEntities[i]->isReady() ) {
            return true;
        }
    }

    return false;
}
